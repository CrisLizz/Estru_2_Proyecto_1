#include "hearts.h"

hearts::hearts(QObject *parent)
    : QObject(parent), QGraphicsItem()
{
    altura = 256;
    anchura = 256;

    columnas = 0;
    filas = 0;

    maxlives = 4;

    corazones = new QPixmap(":/Protagonista/hearts.png");
}

QRectF hearts::boundingRect() const
{
    return QRectF(-anchura/4, -altura/4, anchura/4, altura/4);
}

void hearts::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-anchura/4, -altura/4, *corazones, columnas, 0, anchura, altura);
}

void hearts::showLife(int lives)
{
    lives = qBound(0, lives, maxlives);

    columnas = lives * 256;

    update();
}
