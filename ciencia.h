#ifndef CIENCIA_H
#define CIENCIA_H

#include <QLabel>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QWidget>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QPointer>

#include "cuestionario.h"

class Ciencia : public QObject
{
    Q_OBJECT
public:
    explicit Ciencia(QGraphicsScene* scene);

    QGraphicsTextItem* question;
    QGraphicsTextItem* option1;
    QGraphicsTextItem* option2;
    QGraphicsTextItem* option3;
    QGraphicsTextItem* option4;

    QGraphicsScene* m_scene;

    QGraphicsTextItem* timer_label;
    QTimer* timer = nullptr;
    int remainingTime = 0;

    QGraphicsRectItem* door1;
    QGraphicsRectItem* door2;
    QGraphicsRectItem* door3;
    QGraphicsRectItem* door4;
    QGraphicsItem* exit;

    cuestionario* cienciaP;

    void loadDoors(QGraphicsScene* scene);
    void loadQuestions(QGraphicsScene* scene);
    void wall(QGraphicsScene* scene);

    //doors check
    void chooseDoor();

    cuestionario::Preguntas currentQuestion;
    int m_doorsCorrect = 0;

    void correctDoor(int selectedDoor);

    bool wonTheGame();

    void showTemporaryMessage(const QString& text);

    void startTimer();

public slots:
    void updateTimer();
    void handleTimeout();

signals:

    void minigameFinished();
};

#endif // CIENCIA_H
