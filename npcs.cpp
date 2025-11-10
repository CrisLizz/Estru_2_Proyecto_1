#include "npcs.h"
#include <QGraphicsTextItem>
#include <QDebug>
#include <QTimer>

Npcs::Npcs(QObject *parent)
    : QObject{parent}
{
    timer = new QTimer(this);

    filas = 0;
    columnas = 0;

    // Default (neutral)
    walkIzq = new QPixmap(":/Protagonista/Walk_izq.png");
    walkDerecha = new QPixmap(":/Protagonista/Walk_der.png");
    idle = new QPixmap(":/Protagonista/Idle.png");
    attack_izq = new QPixmap(":/Protagonista/Attack_racionalista.png");
    attack_der = new QPixmap(":/Protagonista/Attack_racionalista.png");
    this->dead = new QPixmap(":/Npcs/rac_npc_death.png");
    sprite = idle;

    ancho = 128;
    alto = 128;

    velocidadX = 0;
    velocidadY = 0;

    // Heart sprite sheet (5 frames horizontally)
    corazones = new QPixmap(":/Npcs/hearts_npc.png");

    connect(timer, &QTimer::timeout, this, &Npcs::Animacion);
    timer->start(80);
}

void Npcs::changeTeam(int teamID)
{
    // Change sprites depending on team
    if (teamID == 1) { // Racionalista
        walkIzq = new QPixmap(":/Npcs/rac_walk_npc.png");
        walkDerecha = new QPixmap(":/Npcs/rac_walk_npc_der.png");
        idle = new QPixmap(":/Npcs/rac_idle_npc.png");
        attack_izq = new QPixmap(":/Npcs/rac_attack_npc.png");
        attack_der = new QPixmap(":/Npcs/rac_attack_npc_der.png");
        this->dead = new QPixmap(":/Npcs/rac_npc_death.png");
        team = "racionalista";
    }
    else if (teamID == 2) { // Empirista
        walkIzq = new QPixmap(":/Npcs/emp_walk_npc.png");
        walkDerecha = new QPixmap(":/Npcs/emp_walk_npc_der.png");
        idle = new QPixmap(":/Npcs/emp_idle_npc.png");
        attack_izq = new QPixmap(":/Npcs/emp_attack_npc.png");
        attack_der = new QPixmap(":/Npcs/emp_attack_npc_der.png");
        this->dead = new QPixmap(":/Npcs/emp_death_npc.png");
        team = "empirista";
    }

    sprite = idle;
    update();
}

void Npcs::attack()
{
    if (isAttacking) return;
    isAttacking = true;

    sprite = attack_izq;
    columnas = 0;

    // Hitbox logic (optional)
    QRectF attackArea = boundingRect();
    attackArea.translate(-50, 0);
    QList<QGraphicsItem*> hits = scene()->items(mapToScene(attackArea).boundingRect());
    for (auto item : hits) {
        QString type = item->data(0).toString();
        if (type == "enemy" || type == "breakable")
            qDebug() << "Hit!" << type;
    }

    // Return to idle after animation
    QTimer::singleShot(6 * 80, [this]() {
        sprite = idle;
        isAttacking = false;
        columnas = 0;
        update(-ancho/2, -alto/2, ancho, alto);
    });
}

void Npcs::Animacion()
{
    if (!sprite) return;

    int maxColumnas = 0;

    if (sprite == walkDerecha || sprite == walkIzq)
        maxColumnas = 1536; // 12 frames
    else if (sprite == idle)
        maxColumnas = 768;  // adjust if your idle sheet differs
    else if (sprite == attack_der || sprite == attack_izq)
        maxColumnas = 768; // 6 frames * 128px

    columnas += 128;
    if (columnas >= maxColumnas)
        columnas = 0;

    Caminar();
    update(-ancho/2, -alto/2, ancho, alto);
}

void Npcs::moverIzquierda()
{
    velocidadX = -12;
    sprite = walkIzq;
}

void Npcs::moverDerecha()
{
    velocidadX = 12;
    sprite = walkDerecha;
}

void Npcs::Detener()
{
    velocidadX = 0;
    velocidadY = 0;
    sprite = idle;
}

void Npcs::Caminar()
{
    if (!scene()) return;

    qreal newX = x() + velocidadX;

    QRectF bounds = scene()->sceneRect();
    QRectF spriteRect = boundingRect();

    // Keep NPC within scene limits
    if (newX - spriteRect.width()/2 < bounds.left())
        newX = bounds.left() + spriteRect.width()/2;
    if (newX + spriteRect.width()/2 > bounds.right())
        newX = bounds.right() - spriteRect.width()/2;

    setPos(newX, y());
}
void Npcs::death()
{
    sprite = dead;
    columnas = 0;
    ancho = 195;   // width per frame (975 / 5)
    alto = 130;    // height per frame

    int frameCount = 5;
    int frameDuration = 120; // ms per frame (adjust for speed)

    // Stop any movement or walking animation
    velocidadX = 0;
    velocidadY = 0;
    this->setScale(0.6);
    timer->stop();

    // Animate 5-frame death sequence
    for (int i = 0; i < frameCount; ++i) {
        QTimer::singleShot(i * frameDuration, [this, i]() {
            columnas = i * ancho;
            update(-ancho/2, -alto/2, ancho, alto);
        });
    }

    // Optional: stay on last frame or fade out
    QTimer::singleShot(frameCount * frameDuration, [this]() {
        columnas = (5 - 1) * ancho; // stay on last frame
        update(-ancho/2, -alto/2, ancho, alto);
    });
}


void Npcs::debugPosition()
{
    qDebug() << "NPC Position:" << pos();
}

void Npcs::ChangeToKantDesc(string npc)
{
    showHearts = false;

    if (npc == "Kant"){
        idle = new QPixmap(":/Npcs/Kant.png");
    }
    else if (npc == "Descartes"){
        idle = new QPixmap(":/Npcs/Descartes.png");
    }

    sprite = idle;
    update(-ancho/2, -alto/2, ancho, alto);

    this->setScale(1.3);
}

QRectF Npcs::boundingRect() const
{
    return QRectF(-ancho / 2, -alto / 2, ancho, alto);
}
void Npcs::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // --- Draw main sprite ---
    painter->drawPixmap(-ancho / 2, -alto / 2, *sprite, columnas, 0, ancho, alto);

    // --- Draw corazones above ---
    if (showHearts) {
        int totalFrames = 5;
        int frameWidth = corazones->width() / totalFrames;
        int frameHeight = corazones->height();

        // lifes = 4 → frame 0, lifes = 0 → frame 4
        int frameIndex = qBound(0, 4 - lifes, 4);

        // Make hearts smaller (scale 70%)
        int scaledWidth = frameWidth * 0.7;
        int scaledHeight = frameHeight * 0.7;

        // Position them higher above the head
        int x = -scaledWidth / 2;
        int y = -alto / 2 - 55;  // raised higher (was -40)

        painter->drawPixmap(x, y, scaledWidth, scaledHeight,
                            *corazones,
                            frameIndex * frameWidth, 0,
                            frameWidth, frameHeight);
    }
}


void Npcs::addLifes()
{
    lifes++;
    if (lifes > 4) lifes = 4;
    update();
}

void Npcs::takeLifes()
{
    lifes--;
    if (lifes < 0) lifes = 0;
    update();
}

int Npcs::getLifes()
{
    return lifes;
}
