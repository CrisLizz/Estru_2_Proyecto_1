#include "politics.h"
#include <QMessageBox>
#include <QGraphicsView>
#include <QRandomGenerator>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

Politics::Politics(QGraphicsScene* scene)
{
    m_scene = scene;
    politicsQ = new cuestionario();
    politicsQ->insertarPolitica();

    loadQuestion();
    loadButtons();
    wall(m_scene);

    setupTimer();
    setupVelocities();

}

void Politics::setupTimer()
{
    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Politics::updateFloatingButtons);
    moveTimer->start(20);
}

// ---------------------------------------------------
void Politics::setupVelocities()
{
    int buttonCount = optionButtons.size();
    buttonVelocities.resize(buttonCount);

    for (int i = 0; i < buttonCount; ++i) {
        double vx, vy;
        do {

            vx = QRandomGenerator::global()->bounded(-30, 31) / 10.0;
            vy = QRandomGenerator::global()->bounded(-30, 31) / 10.0;
        } while (vx == 0 || vy == 0 || std::hypot(vx, vy) < 1.5);

        buttonVelocities[i] = QPointF(vx, vy);
        qDebug() << "Button" << i << "velocity:" << vx << vy;
    }
}


void Politics::wall(QGraphicsScene *scene)
{
    QGraphicsRectItem* wall_center = new QGraphicsRectItem(0, 0, 1000, 305);
    wall_center->setPos(0, -100);
    wall_center->setBrush(Qt::NoBrush);
    wall_center->setPen(Qt::NoPen);
    wall_center->setData(0,"wall");

    scene->addItem(wall_center);

    QGraphicsRectItem* chairs = new QGraphicsRectItem(0, 0, 260, 1);
    chairs->setPos(390, 354);
    chairs->setBrush(Qt::NoBrush);
    chairs->setPen(Qt::NoPen);
    chairs->setData(0,"wall");

    scene->addItem(chairs);
}

// ---------------------------------------------------
void Politics::loadButtons()
{
    // Remove any previous buttons first
    for (QPushButton* btn : optionButtons) {
        if (btn) {
            btn->hide();
            btn->deleteLater();
        }
    }
    optionButtons.clear();

    if (politicsQ->politicaQueue.isEmpty()) return;
    currentQuestion = politicsQ->politicaQueue.head();

    int optionCount = currentQuestion.opciones.size();

    if (optionCount == 0) return; // defensive

    optionButtons.resize(optionCount);

    for (int i = 0; i < optionCount; ++i) {
        QPushButton* btn = new QPushButton();
        optionButtons[i] = btn;

        QString style = "QPushButton {"
                        "border: none;"                                  // no border
                        "background-image: url(:/Deco/bubble_text.png);"   // background image
                        "background-repeat: no-repeat;"
                        "background-position: center;"
                        "color: black;"                                  // font color
                        "font: bold 14px 'Arial';"                       // font style & size
                        "}";

        btn->setStyleSheet(style);
        btn->setFixedSize(280, 77);
        btn->setText(currentQuestion.opciones[i]);

        if (!m_scene->views().isEmpty() && m_scene->views().first())
            btn->setParent(m_scene->views().first()->viewport());

        btn->move(100 + i * 150, 400);
        btn->show();

        connect(btn, &QPushButton::clicked, this, &Politics::handleAnswer);
    }

    this->setupVelocities();
}


// ---------------------------------------------------
void Politics::loadQuestion()
{
    if (politicsQ->politicaQueue.isEmpty()) return;

    currentQuestion = politicsQ->politicaQueue.head();

    question = new QGraphicsTextItem(currentQuestion.pregunta);
    question->setDefaultTextColor(Qt::white);
    question->setFont(QFont("Arial", 9.5, QFont::Bold));
    question->setPos(450, 110);
    question->setTextWidth(120);
    m_scene->addItem(question);
}

// ---------------------------------------------------
void Politics::handleAnswer()
{
    QPushButton* senderButton = qobject_cast<QPushButton*>(sender());
    if (!senderButton) return;

    int clickedIndex = optionButtons.indexOf(senderButton);
    if (clickedIndex == -1) return;

    if (clickedIndex == currentQuestion.opcionCorrecta) {
        m_correctAnswers++;
        showTemporaryMessage(":/Deco/respuesta_correcta.jpg");
    } else {
        showTemporaryMessage(":/Deco/respuesta_incorrecta.jpg");
    }

    // Remove question and load next one
    m_scene->removeItem(question);
    delete question;
    question = nullptr;

    // Remove all buttons safely
    for (QPushButton* btn : optionButtons) {
        if (btn) {
            btn->hide();
            btn->setParent(nullptr);
            delete btn;
        }
    }

    optionButtons.clear();

    // Remove question from queue
    politicsQ->quitarPregunta(politicsQ->politicaQueue);

    // Load next question if available
    if (!politicsQ->politicaQueue.isEmpty()) {
        loadQuestion();
        loadButtons();
    } else {
        if (moveTimer) {
            moveTimer->stop();
            delete moveTimer;
            moveTimer = nullptr;
        }

        emit gameFinished();

        if (wonTheGame())
            showTemporaryMessage(":/Deco/politica_aprobada.jpg");
        else
            showTemporaryMessage(":/Deco/politica_reprobada.jpg");
    }
}

// ---------------------------------------------------
void Politics::updateFloatingButtons()
{
    if (optionButtons.isEmpty()) return;

    const int topMargin = 80;

    for (int i = 0; i < optionButtons.size(); ++i) {
        QPushButton* btn = optionButtons[i];
        if (!btn || !btn->isVisible()) continue;

        QPointF pos = btn->pos();
        QPointF vel = buttonVelocities[i];

        pos += vel;

        int maxX = m_scene->width() - btn->width();
        int maxY = m_scene->height() - btn->height();

        if (pos.x() <= 0 || pos.x() >= maxX)
            vel.setX(-vel.x());
        if (pos.y() <= topMargin || pos.y() >= maxY)
            vel.setY(-vel.y());

        pos.setX(qBound(0.0, pos.x(), (double)maxX));
        pos.setY(qBound((double)topMargin, pos.y(), (double)maxY));

        btn->move(pos.toPoint());
        buttonVelocities[i] = vel;
    }
}

// ---------------------------------------------------
bool Politics::wonTheGame()
{
    return (m_correctAnswers >= 5);
}


void Politics::showTemporaryMessage(const QString& imagePath)
{
    QGraphicsPixmapItem* img = new QGraphicsPixmapItem(QPixmap(imagePath));
    img->setScale(0.3);
    img->setZValue(1000);
    img->setPos(384,196);
    m_scene->addItem(img);

    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect;
    img->setGraphicsEffect(effect);

    QPropertyAnimation* anim = new QPropertyAnimation(effect, "opacity");
    anim->setDuration(2500);
    anim->setStartValue(1.0);
    anim->setEndValue(0.0);

    QObject::connect(anim, &QPropertyAnimation::finished, [this, img, effect]() {
        m_scene->removeItem(img);
        delete effect;
        delete img;
    });

    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

