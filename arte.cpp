#include "arte.h"
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QDebug>

Arte::Arte(QGraphicsScene* scene)
{
    m_scene = scene;
    arteP = new cuestionario();
    arteP->insertarArte();

    loadSculptureStages(scene);
    loadQuestions(scene);
    loadItems(scene);
    walls(scene);
}

void Arte::loadSculptureStages(QGraphicsScene* scene)
{

    sculptureStages = {
        ":/Deco/scuplture_1.png",
        ":/Deco/scuplture_2.png",
        ":/Deco/scuplture_3.png",
        ":/Deco/scuplture_4.png",
        ":/Deco/scuplture_5.png"
    };

    sculptureItem = new QGraphicsPixmapItem(QPixmap(sculptureStages[0]));
    sculptureItem->setScale(0.5);
    sculptureItem->setZValue(10);
    sculptureItem->setPos(495, 310);
    scene->addItem(sculptureItem);
}

void Arte::loadQuestions(QGraphicsScene* scene)
{
    if (arteP->arteQueue.isEmpty()) return;

    currentQuestion = arteP->arteQueue.head();

    // Question
    question = new QGraphicsTextItem(currentQuestion.pregunta
                                     + "\na)" + currentQuestion.opciones[0]
                                     + "\nb)" + currentQuestion.opciones[1]
                                     + "\nc)" + currentQuestion.opciones[2]
                                     + "\nd)" + currentQuestion.opciones[3]);
    question->setDefaultTextColor(Qt::white);
    question->setFont(QFont("Arial", 10, QFont::Bold));
    question->setTextWidth(200);
    question->setPos(400, 80);
    scene->addItem(question);

    // Options
    option1 = scene->addText("(A)");
    option1->setFont(QFont("Arial", 14, QFont::Bold));
    option1->setDefaultTextColor(Qt::white);
    option1->setPos(65, 185);

    option2 = scene->addText("(B)");
    option2->setDefaultTextColor(Qt::white);
    option2->setFont(QFont("Arial", 14, QFont::Bold));
    option2->setPos(240, 185);

    option3 = scene->addText("(C)");
    option3->setDefaultTextColor(Qt::white);
    option3->setFont(QFont("Arial", 14, QFont::Bold));
    option3->setPos(715, 185);

    option4 = scene->addText("(D)");
    option4->setDefaultTextColor(Qt::white);
    option4->setFont(QFont("Arial", 14, QFont::Bold));
    option4->setPos(895, 185);
}

void Arte::walls(QGraphicsScene *scene)
{
    QGraphicsRectItem* wall_center = new QGraphicsRectItem(0, 0, 1000, 305);
    wall_center->setPos(0, -100);
    wall_center->setBrush(Qt::NoBrush);
    wall_center->setPen(Qt::NoPen);
    wall_center->setData(0,"wall");

    scene->addItem(wall_center);

    QGraphicsRectItem* wall_left = new QGraphicsRectItem(0, 0, 100, 50);
    wall_left->setPos(60, 360);
    wall_left->setBrush(Qt::NoBrush);
    wall_left->setPen(Qt::NoPen);
    wall_left->setData(0,"wall");

    scene->addItem(wall_left);

    QGraphicsRectItem* stand = new QGraphicsRectItem(0, 0, 1, 1);
    stand->setPos(517, 370);
    stand->setBrush(Qt::NoBrush);
    stand->setPen(Qt::NoPen);
    stand->setData(0,"wall");

    scene->addItem(stand);

    QGraphicsRectItem* wall_right = new QGraphicsRectItem(0, 0, 100, 50);
    wall_right->setPos(856, 360);
    wall_right->setBrush(Qt::NoBrush);
    wall_right->setPen(Qt::NoPen);
    wall_right->setData(0,"wall");

    scene->addItem(wall_right);

}

void Arte::loadItems(QGraphicsScene *scene)
{
    // === object 1 ===
    object1 = scene->addRect(44, 244, 50, 20, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    object1->setData(0, "object");
    object1->setData(3, 0);

    auto label1 = scene->addText("Press E to choose");
    label1->setDefaultTextColor(Qt::white);
    label1->setZValue(10);
    label1->setVisible(false);
    object1->setData(1, QVariant::fromValue<void*>(label1));

    // === object 2 ===
    object2 = scene->addRect(248, 244, 50, 20, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    object2->setData(0, "object");
    object2->setData(3, 1);

    auto label2 = scene->addText("Press E to choose!");
    label2->setDefaultTextColor(Qt::white);
    label2->setZValue(10);
    label2->setVisible(false);
    object2->setData(1, QVariant::fromValue<void*>(label2));

    // === object 3 ===
    object3 = scene->addRect(720, 244, 50, 20, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    object3->setData(0, "object");
    object3->setData(3, 2);

    auto label3 = scene->addText("Press E to choose!");
    label3->setDefaultTextColor(Qt::white);
    label3->setZValue(10);
    label3->setVisible(false);
    object3->setData(1, QVariant::fromValue<void*>(label3));

    // === object 4 ===
    object4 = scene->addRect(908, 244, 50, 20, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    object4->setData(0, "object");
    object4->setData(3, 3);

    auto label4 = scene->addText("Press E to choose!");
    label4->setDefaultTextColor(Qt::white);
    label4->setZValue(10);
    label4->setVisible(false);
    object4->setData(1, QVariant::fromValue<void*>(label4));
}

void Arte::nextStage()
{
    if (currentStage < sculptureStages.size() - 1) {
        currentStage++;
        sculptureItem->setPixmap(QPixmap(sculptureStages[currentStage]));
    }
}


void Arte::checkAnswer(int selectedOption)
{
    qDebug() << "entered checkAnswer";

    if (arteP->arteQueue.isEmpty()) return;

    if (selectedOption == currentQuestion.opcionCorrecta) {
        qDebug() << "good correct";
        showTemporaryMessage(":/Deco/arte_correcto.jpg");
        objectsCorrect++;
        nextStage();
    } else {
        qDebug() << "bad correct";
        showTemporaryMessage(":/Deco/arte_incorrecto.jpg");
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

    arteP->quitarPregunta(arteP->arteQueue);

    if (!arteP->arteQueue.isEmpty()) {
        loadQuestions(m_scene);
    } else {
        emit minigameFinished();
        qDebug() << "correct : " << this->objectsCorrect << " - " << this->wonTheGame();
        if (wonTheGame()){
            showTemporaryMessage(":/Deco/arte_aprobado.jpg");
        }else{
            showTemporaryMessage(":/Deco/arte_reprobado.jpg");
        }
    }
}

bool Arte::wonTheGame(){
    if (this->objectsCorrect == 5){
        return true;
    }
    return false;
}

bool Arte::finishedGame()
{
    return currentStage >= sculptureStages.size() - 1;
}

void Arte::showTemporaryMessage(const QString& imagePath)
{
    QGraphicsPixmapItem* img = new QGraphicsPixmapItem(QPixmap(imagePath));
    img->setScale(0.4);
    img->setZValue(1000);
    img->setPos(380, 260);
    m_scene->addItem(img);

    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect;
    img->setGraphicsEffect(effect);

    QPropertyAnimation* anim = new QPropertyAnimation(effect, "opacity");
    anim->setDuration(2000);
    anim->setStartValue(1.0);
    anim->setEndValue(0.0);

    QObject::connect(anim, &QPropertyAnimation::finished, [this, img, effect]() {
        m_scene->removeItem(img);
        delete effect;
        delete img;
    });

    anim->start(QAbstractAnimation::DeleteWhenStopped);
}
