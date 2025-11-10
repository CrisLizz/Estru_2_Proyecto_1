#ifndef KANT_CLASS_H
#define KANT_CLASS_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QPushButton>

#include "npcs.h"
#include "cuestionario.h"

class Kant_class : public QObject
{
    Q_OBJECT
public:
    explicit Kant_class(QGraphicsScene* scene);

    void walls(QGraphicsScene* scene);

    void loadHints(QGraphicsScene* scene);

    void loadMesssages(int hint);

    void loadKant(QGraphicsScene* scene);

    void loadQuestions(QGraphicsScene* scene);

    void onKantTalk();

    void checkKantAnswer(int index);
    void nextKantQuestion();

    bool wonKant = false;

private:
    void showTemporaryMessage(const QString& imagePath);

    QGraphicsTextItem* hintsCounter = nullptr;
    int correctAnswers = 0;

    int hintsFound = 0;
    int totalHints = 6;
    int currentIndex = 0;

    bool hintsCollected[6] = { false, false, false, false, false, false };


    bool kantDone = false;
    bool kantTalked = false;
    bool allHintsFound = false;

    QGraphicsTextItem* question = nullptr;
    QGraphicsScene* scene;
    // QGraphicsView* view;

    QVector<QPushButton*> optionButtons;

    //hints
    QGraphicsRectItem* object1;
    QGraphicsRectItem* object2;
    QGraphicsRectItem* object3;
    QGraphicsRectItem* object4;
    QGraphicsRectItem* object5;
    QGraphicsRectItem* object6;

    cuestionario* kantP;
    cuestionario::Preguntas currentQuestion;

    //kant
    QGraphicsRectItem* KantTrigger;
    Npcs* npcKant;

    //- options -
    QPushButton* option1;
    QPushButton* option2;
    QPushButton* option3;
    QPushButton* option4;

    //idk

signals:
    void minigameFinished();
};

#endif // KANT_CLASS_H
