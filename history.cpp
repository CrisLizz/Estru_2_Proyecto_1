#include "history.h"
#include <QMessageBox>
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QDebug>

History::History(QGraphicsScene* scene)
{
    this->m_scene = scene;

    historiaP = new cuestionario();
    historiaP->insertarHistoria();

    wall(scene);
    loadBookshelves(scene);
    loadQuestions(scene);

}

void History::wall(QGraphicsScene *scene)
{
    // Decorative or blocking walls
    QGraphicsRectItem* wall_center = new QGraphicsRectItem(0, 0, 1000, 255);
    wall_center->setPos(0, -100);
    wall_center->setBrush(Qt::NoBrush);
    wall_center->setPen(Qt::NoPen);
    wall_center->setData(0,"wall");
    scene->addItem(wall_center);

    QGraphicsRectItem* bookshelf_left = new QGraphicsRectItem(0, 0, 150, 70);
    bookshelf_left->setPos(0, 346);
    bookshelf_left->setBrush(Qt::NoBrush);
    bookshelf_left->setPen(Qt::NoPen);
    bookshelf_left->setData(0,"wall");

    scene->addItem(bookshelf_left);

    QGraphicsRectItem* bookshelf_right = new QGraphicsRectItem(0, 0, 150, 70);
    bookshelf_right->setPos(850, 346);
    bookshelf_right->setBrush(Qt::NoBrush);
    bookshelf_right->setPen(Qt::NoPen);
    bookshelf_right->setData(0,"wall");

    scene->addItem(bookshelf_right);

    QGraphicsRectItem* right = new QGraphicsRectItem(0, 0, 200, 1);
    right->setPos(84, 424);
    right->setBrush(Qt::NoBrush);
    right->setPen(Qt::NoPen);
    right->setData(0,"wall");

    scene->addItem(right);

    QGraphicsRectItem* left = new QGraphicsRectItem(0, 0, 200, 1);
    left->setPos(724, 424);
    left->setBrush(Qt::NoBrush);
    left->setPen(Qt::NoPen);
    left->setData(0,"wall");

    scene->addItem(left);
}

void History::loadBookshelves(QGraphicsScene *scene)
{
    // Four books the player can grab (represent answer options)
    book1 = scene->addRect(64, 190, 200, 50, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    book1->setData(0, "book");
    book1->setData(3, 0);

    book2 = scene->addRect(64, 460, 200, 50, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    book2->setData(0, "book");
    book2->setData(3, 1);

    book3 = scene->addRect(736, 460, 200, 50, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    book3->setData(0, "book");
    book3->setData(3, 2);

    book4 = scene->addRect(736, 190, 200, 50, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    book4->setData(0, "book");
    book4->setData(3, 3);

    npc = new QGraphicsRectItem(0, 0, 50, 50);
    npc->setPos(344, 184);
    npc->setBrush(Qt::NoBrush);
    npc->setPen(Qt::NoPen);
    npc->setData(0,"npc");

    scene->addItem(npc);

}

void History::loadQuestions(QGraphicsScene* scene)
{
    if (historiaP->historiaQueue.isEmpty()) return;

    currentQuestion = historiaP->historiaQueue.head();

    //Bubble Thing
    bubble_text = scene->addPixmap(QPixmap(":/Deco/speech_text.png"));
    bubble_text->setPos(340, 110);
    bubble_text->setScale(1.2);


    // --- Question text ---
    question = new QGraphicsTextItem(currentQuestion.pregunta);
    question->setDefaultTextColor(Qt::black);
    QFont qFont("Arial", 9, QFont::Bold);
    question->setFont(qFont);
    question->setTextWidth(210);
    question->setPos(360, 114);
    scene->addItem(question);

    // --- Option labels under books ---
    option1 = scene->addText("a) " + currentQuestion.opciones[0]);
    option1->setFont(qFont);
    option1->setDefaultTextColor(Qt::white);
    option1->setPos(20, 85);

    option2 = scene->addText("b) " + currentQuestion.opciones[1]);
    option2->setFont(qFont);
    option2->setDefaultTextColor(Qt::white);
    option2->setPos(20, 370);

    option3 = scene->addText("c) " + currentQuestion.opciones[2]);
    option3->setFont(qFont);
    option3->setDefaultTextColor(Qt::white);
    option3->setPos(840, 370);

    option4 = scene->addText("d) " + currentQuestion.opciones[3]);
    option4->setFont(qFont);
    option4->setDefaultTextColor(Qt::white);
    option4->setPos(840, 85);
}
void History::showPixelMessage(const QString& title, const QString& text)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.setText(text);
    msgBox.setStandardButtons(QMessageBox::Ok);

    // Pixel-style font (install a retro/pixel font on your system)
    QFont pixelFont("Press Start 2P", 10);
    msgBox.setFont(pixelFont);

    // Pixel-style colors
    msgBox.setStyleSheet(
        "QMessageBox {"
        "  background-color: #222222;"
        "  border: 4px solid #ffffff;"
        "}"
        "QLabel {"
        "  color: #00ff00;"
        "}"
        "QPushButton {"
        "  background-color: #444444;"
        "  border: 2px solid #ffffff;"
        "  color: #00ff00;"
        "  min-width: 80px;"
        "  min-height: 30px;"
        "}"
        "QPushButton:pressed {"
        "  background-color: #00ff00;"
        "  color: #000000;"
        "}"
        );

    msgBox.exec();
}

void History::pickUpBook(int bookID)
{
    if (carryingBook) {
        showTemporaryMessage(":/Deco/agarro_libro.jpg");
        return;
    }

    carryingBook = true;
    carriedBookID = bookID;

    qDebug() << "Picked up book" << bookID;
    showTemporaryMessage(":/Deco/si_libro.jpg");
}

void History::returnBookToNPC()
{
    if (!carryingBook) {
        showTemporaryMessage(":/Deco/no_libro.jpg");
        return;
    }

    correctBook(carriedBookID);
    carryingBook = false;
    carriedBookID = -1;
}

void History::correctBook(int selectedBook)
{
    if (historiaP->historiaQueue.isEmpty()) return;

    if (selectedBook == currentQuestion.opcionCorrecta) {
        m_booksCorrect++;
        showTemporaryMessage(":/Deco/Libro_Correcto.jpg");
    } else {
        showTemporaryMessage(":/Deco/Libro_Incorrecto.jpg");
    }

    // Remove question from queue
    historiaP->quitarPregunta(historiaP->historiaQueue);

    // Clear old question from scene
    m_scene->removeItem(question);
    m_scene->removeItem(option1);
    m_scene->removeItem(option2);
    m_scene->removeItem(option3);
    m_scene->removeItem(option4);
    m_scene->removeItem(bubble_text);

    delete bubble_text;
    delete question;
    delete option1;
    delete option2;
    delete option3;
    delete option4;

    question = option1 = option2 = option3 = option4 = nullptr;

    // Load next question or finish
    if (!historiaP->historiaQueue.isEmpty()) {
        loadQuestions(m_scene);
    } else {
        emit minigameFinished();

        if (wonTheGame())
            showTemporaryMessage(":/Deco/historia_aprobada.jpg");
        else
            showTemporaryMessage(":/Deco/historia_reprobada.jpg");
    }
}

bool History::wonTheGame()
{
    return (m_booksCorrect >= 5);
}

void History::handleWin()
{
    QMessageBox::information(nullptr, "You Won!", "You completed the history challenge!");
}


void History::showTemporaryMessage(const QString& imagePath)
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
