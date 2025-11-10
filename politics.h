#ifndef POLITICS_H
#define POLITICS_H

#include <QObject>
#include <QGraphicsScene>
#include <QPushButton>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QPropertyAnimation>
#include "cuestionario.h"

class Politics : public QObject
{
    Q_OBJECT
public:
    explicit Politics(QGraphicsScene* scene);

    QGraphicsScene* m_scene;

    // Question
    QGraphicsTextItem* question;

    // Floating buttons
    QPushButton* option1;
    QPushButton* option2;
    QPushButton* option3;
    QPushButton* option4;

    // Question data
    cuestionario* politicsQ;
    cuestionario::Preguntas currentQuestion;
    int m_correctAnswers = 0;

    // Functions
    void loadButtons();
    void loadQuestion();
    void moveButtonsRandomly();

    void wall(QGraphicsScene *scene);
    void setupTimer();
    void setupVelocities();

    bool wonTheGame();

    void showTemporaryMessage(const QString& text);


private:
    QTimer* moveTimer;
    QVector<QPushButton*> optionButtons;
    QVector<QPointF> buttonVelocities;

signals:
    void gameFinished();

private slots:
    void handleAnswer();
    void updateFloatingButtons();
};

#endif // POLITICS_H

