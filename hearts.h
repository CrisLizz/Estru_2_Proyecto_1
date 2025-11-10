#ifndef HEARTS_H
#define HEARTS_H

#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsScene>
#include <QObject>

class hearts : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit hearts(QObject *parent = nullptr);

    float anchura, altura;

    float filas, columnas;

    QPixmap* corazones;

    int maxlives;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:

    void showLife(int lives);

signals:
};

#endif // HEARTS_H
