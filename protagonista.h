#ifndef PROTAGONISTA_H
#define PROTAGONISTA_H

#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsScene>
#include <QObject>
#include <string>
using namespace std;

class Protagonista : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    explicit Protagonista(QObject *parent = nullptr);

    QTimer* timer;

    //THINGS THAT WOULD BE IN THE PLAYERS DATABASE

    //health
    int lifes = 0;

    int puntos = 0;

    //topics
    enum banda {Racionalista, Empirista};

    bool empirista = false;
    bool showHeartsAbove = false;
    void setShowHeartsAbove(bool show);

    //Animaciones
    QPixmap* idle;
    QPixmap* walkDerecha;
    QPixmap* walkIzq;
    QPixmap* sprite;
    QPixmap* attack_izq;
    QPixmap* attack_der;
    QPixmap* corazones;
    string team;

    //death thingy
    QPixmap* hurt;
    QPixmap* dead;

    float filas, columnas;

    float ancho, alto;

    void changeTeam(int i);

    float velocidadX, velocidadY;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    //void debugs
    void debugPosition();

    bool getEmpirista() const;

    void resetearProtag();

    void setPuntos(int newPuntos);

private:
    bool isAttacking = false;

signals:

public slots:
    void Animacion();

    void moverDerecha();

    void moverIzquierda();

    void moverArriba();

    void moverAbajo();

    void Detener();

    void Caminar();

    void attack();

    void addLifes();

    void death();

    void takeLifes();

    int getLifes();
};

#endif // PROTAGONISTA_H
