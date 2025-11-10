#ifndef DESCARTES_LAB_H
#define DESCARTES_LAB_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QPushButton>

#include "cuestionario.h"
#include "npcs.h"


class descartes_lab : public QObject
{
    Q_OBJECT
public:
    explicit descartes_lab(QGraphicsScene* scene);
    void walls(QGraphicsScene* scene);

    void loadHints(QGraphicsScene* scene);

    void loadMesssages(int hint);

    void loadDescartes(QGraphicsScene* scene);

    void loadQuestions(QGraphicsScene* scene);

    void onKantTalk();

    void checkKantAnswer(int index);
    void nextKantQuestion();

    bool wonDescart = false;
private:
    void showTemporaryMessage(const QString& imagePath);

    QGraphicsTextItem* hintsCounter = nullptr;
    int correctAnswers = 0;

    int hintsFound = 0;
    int totalHints = 4;
    int currentIndex = 0;

    bool hintsCollected[4] = { false, false, false, false};

    bool kantDone = false;
    bool kantTalked = false;
    bool allHintsFound = false;

    QGraphicsTextItem* question = nullptr;
    QGraphicsScene* scene;

    QVector<QPushButton*> optionButtons;

    //hints
    QGraphicsRectItem* object1;
    QGraphicsRectItem* object2;
    QGraphicsRectItem* object3;
    QGraphicsRectItem* object4;
    QGraphicsRectItem* object5;

    cuestionario* descartesP;
    cuestionario::Preguntas currentQuestion;

    //kant
    QGraphicsRectItem* KantTrigger;
    Npcs* npcDescartes;

    //- options -
    QPushButton* option1;
    QPushButton* option2;
    QPushButton* option3;
    QPushButton* option4;

    //idk

signals:
    void minigameFinished();
};
#endif // DESCARTES_LAB_H
