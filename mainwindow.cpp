#include "mainwindow.h"
#include <QGuiApplication>
#include <QScreen>
#include <QMessageBox>
#include <iostream>
using namespace std;


MainWindow::MainWindow(const Player &p, QWidget* parent)
    : QMainWindow(parent), currentPlayer(p)
{
    ancho = 1000;
    alto  = 600;

    this->setFixedSize(ancho, alto);

    scene = new QGraphicsScene(0, 0, ancho, alto, this);

    QPixmap background(":/Fondos/school_Front.jpg");

    scene->setSceneRect(0, 0, 1000, 600);
    scene->setBackgroundBrush(background.scaled(scene->sceneRect().size().toSize(),
                                                Qt::IgnoreAspectRatio,
                                                Qt::SmoothTransformation));

    QGraphicsView* view = new QGraphicsView(scene, this);

    view->setFocusPolicy(Qt::NoFocus);
    setCentralWidget(view);

    this->setFocusPolicy(Qt::StrongFocus);
    this->setFocus();

    //invisible walls
    QGraphicsRectItem* wall = new QGraphicsRectItem(0, 0, 400, 650);
    wall->setPos(0, -200);
    wall->setBrush(Qt::NoBrush);
    wall->setPen(Qt::NoPen);
    wall->setData(0,"wall");

    scene->addItem(wall);

    //wall left
    QGraphicsRectItem* wall_left = new QGraphicsRectItem(0, 0, 400, 650);
    wall_left->setPos(600, -200);
    wall_left->setBrush(Qt::NoBrush);
    wall_left->setPen(Qt::NoPen);
    wall_left->setData(0,"wall");

    scene->addItem(wall_left);

    //wall center
    QGraphicsRectItem* wall_center = new QGraphicsRectItem(0, 0, 400, 600);
    wall_center->setPos(450, -200);
    wall_center->setBrush(Qt::NoBrush);
    wall_center->setPen(Qt::NoPen);
    wall_center->setData(0,"wall");
    scene->addItem(wall_center);

    //TRIGGER THINGY
    QGraphicsRectItem* triggerZone = new QGraphicsRectItem(470, 430, 50, 50);
    triggerZone->setBrush(Qt::NoBrush);
    triggerZone->setPen(QPen(Qt::NoPen));
    triggerZone->setData(0, "trigger");

    //POP-UP message for the trigger thingy
    QGraphicsTextItem* label = new QGraphicsTextItem("Press A to enter");
    label->setDefaultTextColor(Qt::white);
    label->setZValue(10);
    label->setVisible(false);

    //---- modify font later ? perhaps

    triggerZone->setData(1, QVariant::fromValue<void*>(label));

    scene->addItem(triggerZone);
    scene->addItem(label);

    // Protagonista
    protag = new Protagonista();
    scene->addItem(protag);
    protag->setPos(0, 550);

    VideoWindow* video = new VideoWindow(); // parent = main window
    video->setWindowModality(Qt::ApplicationModal); // blocks input to main window
    video->show();


    //GET RID OF BAR THINGY
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

MainWindow::~MainWindow() {}


//----- KEY EVENTS -------
void MainWindow::keyPressEvent(QKeyEvent* event)
{
    switch (event->key()) {
    case Qt::Key_A: {

        QList<QGraphicsItem*> collisions = protag->collidingItems();
        for (auto item : collisions) {
            if (item->data(0).toString() == "trigger") {
                hallway* hall = new hallway(currentPlayer);
                hall->show();
                this->close();
            }
        }
        break;
    }

    case Qt::Key_Left:
        protag->moverIzquierda();
        break;
    case Qt::Key_Right:
        protag->moverDerecha();
        break;
    case Qt::Key_Up:
        protag->moverArriba();
        break;
    case Qt::Key_Down:
        protag->moverAbajo();
        break;
    default:
        break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    switch(event->key())
    {
    case Qt::Key_Right:
    case Qt::Key_Left:
    case Qt::Key_Up:
    case Qt::Key_Down:
        protag->Detener();
        break;
    default: QMainWindow::keyReleaseEvent(event);
    }
}
