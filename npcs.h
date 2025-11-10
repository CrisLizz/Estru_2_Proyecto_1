#ifndef NPCS_H
#define NPCS_H

#include <QPixmap>
#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPainter>
#include <string>
#include <QGraphicsScene>
using namespace std;

class Npcs : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    explicit Npcs(QObject *parent = nullptr);

    // Timer for animation
    QTimer* timer;

    // Health
    int lifes = 1; // max 4 hearts (5th frame = empty)

    // Animation sprites
    QPixmap* idle;
    QPixmap* walkDerecha;
    QPixmap* walkIzq;
    QPixmap* sprite;
    QPixmap* attack_izq;
    QPixmap* attack_der;
    QPixmap* hurt;
    QPixmap* dead;
    QPixmap* corazones; // hearts sprite sheet (5 frames)
    string team;

    // Sprite sheet info
    float filas, columnas;
    float ancho, alto;

    // Movement
    float velocidadX, velocidadY;

    // --- Methods ---
    void changeTeam(int teamID);
    void debugPosition();

    void ChangeToKantDesc(string npc);

    bool showHearts = true;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

public slots:
    void Animacion();
    void moverIzquierda();
    void moverDerecha();
    void Detener();
    void Caminar();
    void attack();
    void death();
    void addLifes();
    void takeLifes();
    int getLifes();

private:
    bool isAttacking = false;
};

#endif // NPCS_H
