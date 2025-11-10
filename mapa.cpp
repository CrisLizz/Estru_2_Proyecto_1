#include "mapa.h"
#include <QGraphicsPixmapItem>

mapa::mapa(QWidget *parent)
    : QWidget(parent)
{
    // set a fixed size for the widget
    int ancho = 600;
    int alto = 300;
    this->setFixedSize(ancho, alto);

    // create the scene
    scene = new QGraphicsScene(0, 0, ancho, alto, this);

    // load and set background image
    QPixmap background(":/Fondos/Mapa.png");
    scene->setBackgroundBrush(background.scaled(ancho, alto, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    // create the view
    view = new QGraphicsView(scene, this);
    view->setGeometry(0, 0, ancho, alto);

    // remove scrollbars and borders
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFrameStyle(QFrame::NoFrame);

    // make sure it fits properly
    view->setRenderHint(QPainter::SmoothPixmapTransform);
    view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
}
