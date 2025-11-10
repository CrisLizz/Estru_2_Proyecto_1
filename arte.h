#ifndef ARTE_H
#define ARTE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QGraphicsRectItem>

#include "cuestionario.h"

class Arte : public QObject
{
    Q_OBJECT
public:
    explicit Arte(QGraphicsScene* scene);

    void loadSculptureStages(QGraphicsScene* scene);
    void loadQuestions(QGraphicsScene* scene);

    void walls(QGraphicsScene* scene);
    void loadItems(QGraphicsScene* scene);
    void nextStage();          // Advance sculpture
    bool finishedGame();       // All stages complete
    void checkAnswer(int selectedOption);

    bool wonTheGame();

    int objectsCorrect = 0;

    QGraphicsRectItem* object1;
    QGraphicsRectItem* object2;
    QGraphicsRectItem* object3;
    QGraphicsRectItem* object4;

    void showTemporaryMessage(const QString& imagePath);

private:
    QGraphicsScene* m_scene;
    QGraphicsPixmapItem* sculptureItem = nullptr;
    QVector<QString> sculptureStages; // stores image paths

    int currentStage = 0;

    QGraphicsTextItem* question = nullptr;
    QGraphicsTextItem* option1 = nullptr;
    QGraphicsTextItem* option2 = nullptr;
    QGraphicsTextItem* option3 = nullptr;
    QGraphicsTextItem* option4 = nullptr;

    cuestionario* arteP;
    cuestionario::Preguntas currentQuestion;

signals:
    void minigameFinished();
};

#endif // ARTE_H
