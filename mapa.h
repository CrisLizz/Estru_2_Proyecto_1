#ifndef MAPA_H
#define MAPA_H

#include <QWidget>

#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsView>

class mapa : public QWidget
{
    Q_OBJECT
public:
    explicit mapa(QWidget *parent = nullptr);

    QGraphicsScene* scene;
    QGraphicsView* view;

signals:
};

#endif // MAPA_H
