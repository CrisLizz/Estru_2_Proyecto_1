#include "descartes_lab.h"
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QMessageBox>

descartes_lab::descartes_lab(QGraphicsScene* scene){

    this->scene = scene;
    descartesP = new cuestionario();
    descartesP->insertarDescartes();

    walls(scene);
    loadDescartes(scene);
    loadHints(scene);

}

void descartes_lab::walls(QGraphicsScene *scene)
{
    //wall
    QGraphicsRectItem* wall_center = new QGraphicsRectItem(0, 0, 1000, 250);
    wall_center->setPos(0, -100);
    wall_center->setBrush(Qt::NoBrush);
    wall_center->setPen(Qt::NoPen);
    wall_center->setData(0,"wall");

    scene->addItem(wall_center);

    //table_wall
    QGraphicsRectItem* wall_bottom = new QGraphicsRectItem(0, 0, 100, 150);
    wall_bottom->setPos(445,464);
    wall_bottom->setBrush(Qt::NoBrush);
    wall_bottom->setPen(Qt::NoPen);
    wall_bottom->setData(0,"wall");

    scene->addItem(wall_bottom);

    //table 1
    QGraphicsRectItem* table1 = new QGraphicsRectItem(0, 0, 150, 150);
    table1->setPos(20,464);
    table1->setBrush(Qt::NoBrush);
    table1->setPen(Qt::NoPen);
    table1->setData(0,"wall");

    scene->addItem(table1);

    //table 2
    QGraphicsRectItem* table2 = new QGraphicsRectItem(0, 0, 150, 150);
    table2->setPos(835,444);
    table2->setBrush(Qt::NoBrush);
    table2->setPen(Qt::NoPen);
    table2->setData(0,"wall");

    scene->addItem(table2);

    //table 3
    QGraphicsRectItem* table3 = new QGraphicsRectItem(0, 0, 150, 100);
    table3->setPos(850,110);
    table3->setBrush(Qt::NoBrush);
    table3->setPen(Qt::NoPen);
    table3->setData(0,"wall");

    scene->addItem(table3);

    //table 3
    QGraphicsRectItem* Descartes = new QGraphicsRectItem(0, 0, 1, 1);
    Descartes->setPos(30,224);
    Descartes->setBrush(Qt::NoBrush);
    Descartes->setPen(Qt::NoPen);
    Descartes->setData(0,"wall");

    scene->addItem(Descartes);

}


void descartes_lab::loadHints(QGraphicsScene *scene)
{
    // === Book 1 - Imperativo Hipotético ===
    object1 = scene->addRect(445,454, 100, 150, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    object1->setData(0, "table");
    object1->setData(3, 0); // imperativo hipotético

    auto label1 = scene->addText("Press E to investigate");
    label1->setDefaultTextColor(Qt::white);
    label1->setZValue(10);
    label1->setVisible(false);
    object1->setData(1, QVariant::fromValue<void*>(label1));

    // === Book 2 - Epistemología ===
    object2 = scene->addRect(80,454, 100, 150, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    object2->setData(0, "table");
    object2->setData(3, 1); // crítica de la razón pura (epistemología)

    auto label2 = scene->addText("Press E to investigate!");
    label2->setDefaultTextColor(Qt::white);
    label2->setZValue(10);
    label2->setVisible(false);
    object2->setData(1, QVariant::fromValue<void*>(label2));

    // === Pizarra - Sapere aude ===
    object3 = scene->addRect(835,424, 100, 150, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    object3->setData(0, "table");
    object3->setData(3, 2); // lema de la ilustración

    auto label3 = scene->addText("Press E to investigate!");
    label3->setDefaultTextColor(Qt::white);
    label3->setZValue(10);
    label3->setVisible(false);
    object3->setData(1, QVariant::fromValue<void*>(label3));

    // === Sistema Solar - Giro Copernicano ===
    object4 = scene->addRect(850,110, 100, 150, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    object4->setData(0, "table");
    object4->setData(3, 3); // giro copernicano

    auto label4 = scene->addText("Press E to investigate!");
    label4->setDefaultTextColor(Qt::white);
    label4->setZValue(10);
    label4->setVisible(false);
    object4->setData(1, QVariant::fromValue<void*>(label4));

}

void descartes_lab::loadMesssages(int hint)
{
    if (hint < 0 || hint >= totalHints) return;

    QString message;
    switch (hint) {
    case 0:
        message = "Primera regla: **Evidencia**\n"
                  "No aceptar nada como verdadero si no es evidente a la razón.";
        break;
    case 1:
        message = "Segunda regla: **Análisis**\n"
                  "Dividir cada dificultad en tantas partes como sea posible.";
        break;
    case 2:
        message = "Tercera regla: **Síntesis**\n"
                  "Conducir los pensamientos desde lo más simple hasta lo más complejo.";
        break;
    case 3:
        message = "Cuarta regla: **Enumeración**\n"
                  "Hacer revisiones completas para no omitir nada.";
        break;
    default:
        message = "No hay pista disponible.";
        break;
    }

    QMessageBox msgBox;
    msgBox.setWindowTitle("💡 Hint encontrado");
    msgBox.setText(message);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();

    if (!hintsCollected[hint]) {
        hintsCollected[hint] = true;
        hintsFound++;

        // Update hints counter on screen
        if (!hintsCounter) {
            hintsCounter = new QGraphicsTextItem();
            hintsCounter->setDefaultTextColor(Qt::black);
            hintsCounter->setFont(QFont("Segoe UI", 16, QFont::Bold));
            hintsCounter->setPos(10, 50); // top-left corner
            hintsCounter->setZValue(50);
            scene->addItem(hintsCounter);
        }
        hintsCounter->setPlainText(QString("Pistas: %1/%2").arg(hintsFound).arg(totalHints));

        qDebug() << "Hint found:" << hintsFound << "/" << totalHints;

        if (hintsFound >= totalHints) {
            allHintsFound = true;
            QMessageBox::information(nullptr, "✅ Todas las pistas encontradas",
                                     "Has encontrado todas las pistas. ¡Habla con Descartes para resolver el caso!");
        }
    }
}

//descartes 64,224
void descartes_lab::loadDescartes(QGraphicsScene *scene)
{
    npcDescartes = new Npcs();
    npcDescartes->ChangeToKantDesc("Descartes");
    npcDescartes->setPos(64,224);
    npcDescartes->setZValue(0);

    scene->addItem(npcDescartes);

    //load itemTalk 924,500
    KantTrigger = scene->addRect(10,224, 50, 20, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    KantTrigger->setData(0, "npc");
    KantTrigger->setData(4, 0);

    auto KantTrigger_lb = scene->addText("Press E to to talk to Descartes!");
    KantTrigger_lb->setDefaultTextColor(Qt::black);
    KantTrigger_lb->setZValue(10);
    KantTrigger_lb->setVisible(false);
    KantTrigger->setData(1, QVariant::fromValue<void*>(KantTrigger_lb));
}

void descartes_lab::loadQuestions(QGraphicsScene* scene)
{
    if (!scene) return; // defensive


    qDebug() << "enter";
    // Remove previous question text
    if (question) {
        scene->removeItem(question);
        delete question;
        question = nullptr;
    }

    // Get next question
    if (descartesP->DescartesQueue.isEmpty()) return;
    currentQuestion = descartesP->DescartesQueue.head();

    // Background panel
    QGraphicsRectItem* background = new QGraphicsRectItem(0, 0, 420, 180);
    background->setPos(320, 40);
    background->setBrush(QColor(50, 50, 80, 220));
    background->setPen(QPen(QColor(200, 200, 220), 3));
    background->setZValue(10);
    scene->addItem(background);

    qDebug() << "Build";

    // Question text
    question = new QGraphicsTextItem();
    QString html = QString(
                       "<div style='font-family:\"Segoe UI\"; font-size:12pt; color:#FFD700; font-weight:bold;'>%1</div>"
                       "<div style='font-family:\"Segoe UI\"; font-size:10pt; color:white; margin-top:5px;'>"
                       "1) %2<br>2) %3<br>3) %4<br>4) %5</div>")
                       .arg(currentQuestion.pregunta,
                            currentQuestion.opciones[0],
                            currentQuestion.opciones[1],
                            currentQuestion.opciones[2],
                            currentQuestion.opciones[3]);
    question->setHtml(html);
    question->setTextWidth(400);
    question->setPos(330, 50);
    question->setZValue(20);
    scene->addItem(question);

    // Create buttons as QWidget children of viewport
    if (!scene->views().isEmpty() && scene->views().first()) {
        QWidget* viewport = scene->views().first()->viewport();

        optionButtons.resize(4);
        int x = 340, y = 260;

        for (int i = 0; i < 4; ++i) {
            QPushButton* btn = new QPushButton(currentQuestion.opciones[i], viewport);
            btn->setGeometry(x, y + i * 40, 380, 30);
            btn->setStyleSheet(
                "background-color:#333;"
                "color:white;"
                "border:1px solid #AAA;"
                "border-radius:6px;"
                );
            btn->show();

            connect(btn, &QPushButton::clicked, [this, i]() {
                checkKantAnswer(i);
            });

            optionButtons[i] = btn;
        }
    }
}


void descartes_lab::onKantTalk()
{
    if (!allHintsFound) {
        QMessageBox::information(nullptr, "🔒 Pistas incompletas",
                                 "Aún no has encontrado todas las pistas. Busca más antes de hablar con Descartes.");
        return;
    }

    if (!kantTalked) {
        kantTalked = true;
        QMessageBox::information(nullptr, "🧠 Descartes",
                                 "Has reunido todas las pistas. Descartes te hará algunas preguntas...");
        loadQuestions(scene);
    }
}

void descartes_lab::checkKantAnswer(int index)
{
    if (descartesP->DescartesQueue.isEmpty()) return;

    auto current = descartesP->DescartesQueue.head();

    if (index == current.opcionCorrecta) {
        correctAnswers++;
        showTemporaryMessage(":/Deco/arte_correcto.jpg");
    } else {
        showTemporaryMessage(":/Deco/arte_incorrecto.jpg");
    }

    descartesP->DescartesQueue.dequeue();

    for (QPushButton* btn : optionButtons) {
        if (btn) {
            btn->hide();
            btn->setParent(nullptr);
            delete btn;
        }
    }

    optionButtons.clear();

    if (descartesP->DescartesQueue.isEmpty()) {
        // Show final result
        if (correctAnswers == 5){
            this->wonDescart = true;
        }
        QString finalMsg = QString("🎓 Cuestionario terminado!\nRespuestas correctas: %1/%2")
                               .arg(correctAnswers)
                               .arg(5);
        QMessageBox::information(nullptr, "Resultado final", finalMsg);
        kantDone = true;
        minigameFinished();
        return;
    }

    loadQuestions(scene);
}

void descartes_lab::showTemporaryMessage(const QString& imagePath)
{
    QGraphicsPixmapItem* img = new QGraphicsPixmapItem(QPixmap(imagePath));
    img->setScale(0.4);
    img->setPos(420, 220);
    img->setZValue(9999);
    scene->addItem(img);

    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect;
    img->setGraphicsEffect(effect);

    QPropertyAnimation* anim = new QPropertyAnimation(effect, "opacity");
    anim->setDuration(2000);
    anim->setStartValue(1.0);
    anim->setEndValue(0.0);

    QObject::connect(anim, &QPropertyAnimation::finished, [this, img, effect]() {
        scene->removeItem(img);
        delete effect;
        delete img;
    });

    anim->start(QAbstractAnimation::DeleteWhenStopped);
}



