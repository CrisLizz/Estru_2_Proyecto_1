#include "ciencia.h"
#include <QMessageBox>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

Ciencia::Ciencia(QGraphicsScene* scene) {
    m_scene = scene;

    cienciaP = new cuestionario();
    cienciaP->insertarCiencia();

    loadDoors(scene);
    wall(scene);
    loadQuestions(scene);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Ciencia::updateTimer);

    startTimer();
}
void Ciencia::loadDoors(QGraphicsScene *scene)
{
    // === DOOR 1 ===
    door1 = scene->addRect(64, 150, 50, 20, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    door1->setData(0, "door");
    door1->setData(3, 0);

    auto label1 = scene->addText("Press E to choose door A!");
    label1->setDefaultTextColor(Qt::white);
    label1->setZValue(10);
    label1->setVisible(false);
    door1->setData(1, QVariant::fromValue<void*>(label1));

    // === DOOR 2 ===
    door2 = scene->addRect(276, 150, 50, 20, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    door2->setData(0, "door");
    door2->setData(3, 1);

    auto label2 = scene->addText("Press E to choose door B!");
    label2->setDefaultTextColor(Qt::white);
    label2->setZValue(10);
    label2->setVisible(false);
    door2->setData(1, QVariant::fromValue<void*>(label2));

    // === DOOR 3 ===
    door3 = scene->addRect(676, 150, 50, 20, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    door3->setData(0, "door");
    door3->setData(3, 2);

    auto label3 = scene->addText("Press E to choose door C!");
    label3->setDefaultTextColor(Qt::white);
    label3->setZValue(10);
    label3->setVisible(false);
    door3->setData(1, QVariant::fromValue<void*>(label3));

    // === DOOR 4 ===
    door4 = scene->addRect(896, 150, 50, 20, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    door4->setData(0, "door");
    door4->setData(3, 3);

    auto label4 = scene->addText("Press E to choose door D!");
    label4->setDefaultTextColor(Qt::white);
    label4->setZValue(10);
    label4->setVisible(false);
    door4->setData(1, QVariant::fromValue<void*>(label4));
}

void Ciencia::wall(QGraphicsScene* scene)
{
    QGraphicsRectItem* wall_center = new QGraphicsRectItem(0, 0, 1000, 255);
    wall_center->setPos(0, -100);
    wall_center->setBrush(Qt::NoBrush);
    wall_center->setPen(Qt::NoPen);
    wall_center->setData(0,"wall");

    scene->addItem(wall_center);
}

void Ciencia::loadQuestions(QGraphicsScene* scene)
{

    if (cienciaP->cienciaQueue.isEmpty()) return;

    // Take the first question
    currentQuestion = cienciaP->cienciaQueue.head();

    //--- TIMER LABEL ----
    timer_label = new QGraphicsTextItem("Timer: " + QString::number(remainingTime));
    timer_label->setDefaultTextColor(Qt::black);
    timer_label->setFont(QFont("Arial", 14, QFont::Bold));
    timer_label->setPos(500, 10);
    scene->addItem(timer_label);

    // Question
    question = new QGraphicsTextItem(currentQuestion.pregunta);
    question->setDefaultTextColor(Qt::white);
    QFont qFont("Arial", 9.5, QFont::Bold);
    question->setFont(qFont);
    question->setTextWidth(150);
    question->setPos(436, 124);
    scene->addItem(question);

    // Option 1
    option1 = new QGraphicsTextItem("a) " + currentQuestion.opciones[0]);
    option1->setDefaultTextColor(Qt::white);
    option1->setFont(QFont("Arial", 9.5, QFont::Bold));
    option1->setPos(40, 100);
    scene->addItem(option1);

    // Option 2
    option2 = new QGraphicsTextItem("b) " + currentQuestion.opciones[1]);
    option2->setDefaultTextColor(Qt::white);
    option2->setFont(QFont("Arial", 9.5, QFont::Bold));
    option2->setPos(246, 100);
    scene->addItem(option2);

    // Option 3
    option3 = new QGraphicsTextItem("c) " + currentQuestion.opciones[2]);
    option3->setDefaultTextColor(Qt::white);
    option3->setFont(QFont("Arial", 9.5, QFont::Bold));
    option3->setPos(626, 100);
    scene->addItem(option3);

    // Option 4
    option4 = new QGraphicsTextItem( "d) "+ currentQuestion.opciones[3]);
    option4->setDefaultTextColor(Qt::white);
    option4->setFont(QFont("Arial", 9.5, QFont::Bold));
    option4->setPos(826, 100);
    scene->addItem(option4);
}

void Ciencia::startTimer()
{
    if (!cienciaP || cienciaP->cienciaQueue.isEmpty()) return;

    if (timer && timer->isActive())
        timer->stop();

    remainingTime = 15;

    timer_label->setPlainText("Timer: " + QString::number(remainingTime));
    timer_label->setVisible(true);

    timer->start(1000);
}

void Ciencia::updateTimer()
{
    if (!timer_label || cienciaP->cienciaQueue.isEmpty()) return;

    remainingTime--;
    timer_label->setPlainText("Timer: " + QString::number(remainingTime));

    if (remainingTime <= 0) {
        if (timer) timer->stop();
        handleTimeout();
    }
}


void Ciencia::handleTimeout()
{
    if (cienciaP->cienciaQueue.isEmpty()) return;

    // Stop timer first
    if (timer) timer->stop();

    if (timer_label) {
        m_scene->removeItem(timer_label);
        delete timer_label; timer_label = nullptr;
    }
    if (question) {
        m_scene->removeItem(question);
        delete question; question = nullptr;
    }
    if (option1) {
        m_scene->removeItem(option1); delete option1;
        option1 = nullptr;
    }
    if (option2) {
        m_scene->removeItem(option2); delete option2;
        option2 = nullptr;
    }
    if (option3) {
        m_scene->removeItem(option3); delete option3;
        option3 = nullptr;
    }
    if (option4) {
        m_scene->removeItem(option4); delete option4;
        option4 = nullptr;
    }

    // Remove from queue
    cienciaP->quitarPregunta(cienciaP->cienciaQueue);

    // Load next question
    if (!cienciaP->cienciaQueue.isEmpty()) {
        loadQuestions(m_scene);
        startTimer();
    }
    else{
        emit this->minigameFinished();

        if (wonTheGame()){
            showTemporaryMessage(":/Deco/ciencia_aprobado.jpg");
        }else{
            showTemporaryMessage(":/Deco/ciencia_reprobado.jpg");
        }
    }
}

void Ciencia::correctDoor(int doorID)
{
    qDebug() << "entered correctDoor";

    if (cienciaP->cienciaQueue.isEmpty()) return;

    if (doorID == currentQuestion.opcionCorrecta) {
        m_doorsCorrect++;
        qDebug() << "good correct";

        showTemporaryMessage(":/Deco/puerta_correcta.jpg");
    } else {
        qDebug() << "bad correctDoor";

        showTemporaryMessage(":/Deco/puerta_incorrecta.jpg");
    }
    qDebug() << "entered handle";

    handleTimeout();
}

bool Ciencia::wonTheGame(){
    if (m_doorsCorrect == 5){
        return true;
    }
    return false;
}

void Ciencia::showTemporaryMessage(const QString& imagePath)
{
    QGraphicsPixmapItem* img = new QGraphicsPixmapItem(QPixmap(imagePath));
    img->setScale(0.3);
    img->setZValue(1000);
    img->setPos(390,244);
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
