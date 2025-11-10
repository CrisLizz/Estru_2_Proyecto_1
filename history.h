#ifndef HISTORY_H
#define HISTORY_H

#include <QGraphicsScene>
#include <QObject>
#include "cuestionario.h"

class History : public QObject
{
    Q_OBJECT
public:
    explicit History(QGraphicsScene* scene);

    // Text
    QGraphicsTextItem* question;
    QGraphicsTextItem* option1;
    QGraphicsTextItem* option2;
    QGraphicsTextItem* option3;
    QGraphicsTextItem* option4;

    QGraphicsScene* m_scene;

    // Books (to pick up)
    QGraphicsRectItem* book1;
    QGraphicsRectItem* book2;
    QGraphicsRectItem* book3;
    QGraphicsRectItem* book4;

    // NPC (already in the background)
    QGraphicsRectItem* npc;
    QGraphicsItem* bubble_text;

    // Exit (optional)
    QGraphicsItem* exit;

    // Question data
    cuestionario* historiaP;
    cuestionario::Preguntas currentQuestion;

    // Game logic
    int m_booksCorrect = 0;
    bool carryingBook = false;
    int carriedBookID = -1;

    // Setup
    void loadBookshelves(QGraphicsScene* scene);
    void loadQuestions(QGraphicsScene* scene);
    void wall(QGraphicsScene* scene);

    // Interaction logic
    void pickUpBook(int bookID);
    void returnBookToNPC();
    void correctBook(int selectedBook);
    bool wonTheGame();

    void showTemporaryMessage(const QString& text);
    void showPixelMessage(const QString& title, const QString& text);

public slots:
    void handleWin();

signals:
    void minigameFinished();
};

#endif // HISTORY_H
