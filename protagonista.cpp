#include "protagonista.h"
#include <QMessageBox>

Protagonista::Protagonista(QObject *parent)
    : QObject{parent}
{
    timer = new QTimer();

    filas = 0;
    columnas = 0;

    walkDerecha = new QPixmap(":/Protagonista/Walk.png");
    walkIzq = new QPixmap(":/Protagonista/Walk_izq.png");
    idle = new QPixmap(":/Protagonista/Idle.png");
    attack_izq = new QPixmap(":/Protagonista/Attack_racionalista.png");
    attack_der = new QPixmap(":/Protagonista/Attack_racionalista.png");
    corazones = new QPixmap(":/Protagonista/hearts_above.png");
    this->dead = new QPixmap(":/Protagonista/emp_protag_death.png");


    sprite = idle;

    connect(timer,&QTimer::timeout,this,&Protagonista::Animacion);

    ancho = 128;
    alto = 128;

    velocidadX = 0;
    velocidadY = 0;

    timer->start(80);
}

void Protagonista::setPuntos(int newPuntos)
{
    puntos += newPuntos;
}

bool Protagonista::getEmpirista() const
{
    return empirista;
}

void Protagonista::resetearProtag()
{
    walkDerecha = new QPixmap(":/Protagonista/Walk.png");
    walkIzq = new QPixmap(":/Protagonista/Walk_izq.png");
    idle = new QPixmap(":/Protagonista/Idle.png");

    sprite = idle;

    update(-ancho/2, -alto/2, ancho, alto);
}

void Protagonista::changeTeam(int i)
{
    if (i == 1) {
        walkDerecha = new QPixmap(":/Protagonista/racionalista.png");
        walkIzq = new QPixmap(":/Protagonista/racionalista_izq.png");
        idle = new QPixmap(":/Protagonista/racionalista_idle.png");
        attack_der = new QPixmap(":/Protagonista/Attack_racionalista.png");
        attack_izq = new QPixmap(":/Protagonista/Attack_empirista_izq.png");
        this->dead = new QPixmap(":/Protagonista/rac_protag_death.png");

        empirista = false;
        team = "racionalista";

    } else if (i == 2) {
        walkDerecha = new QPixmap(":/Protagonista/empirista.png");
        walkIzq = new QPixmap(":/Protagonista/empirista_izq.png");
        idle = new QPixmap(":/Protagonista/empirista_idle.png");
        attack_der = new QPixmap(":/Protagonista/Attack_empirista.png");
        attack_izq = new QPixmap(":/Protagonista/Attack_racionalista_izq.png");
        this->dead = new QPixmap(":/Protagonista/emp_protag_death.png");
        empirista = true;
        team = empirista;
    }

    sprite = idle;

    update(-ancho/2, -alto/2, ancho, alto);
}

void Protagonista::attack()
{
    if (isAttacking) return;
    isAttacking = true;

    sprite = (velocidadX >= 0) ? attack_der : attack_izq;

    columnas = 0; // reset only at the start of attack

    // --- hit logic ---
    QRectF attackArea = boundingRect();
    if (velocidadX >= 0) attackArea.translate(50, 0);
    else attackArea.translate(-50, 0);

    QList<QGraphicsItem*> hits = scene()->items(mapToScene(attackArea).boundingRect());
    for (auto item : hits) {
        QString type = item->data(0).toString();
        if (type == "enemy" || type == "breakable") {
            qDebug() << "Hit!" << type;
        }
    }

    // --- return to idle after attack animation duration ---
    QTimer::singleShot(6*80, [this]() { // 6 frames * 80ms
        sprite = idle;
        isAttacking = false;
        columnas = 0;
        update(-ancho/2, -alto/2, ancho, alto);
    });
}

void Protagonista::Animacion()
{
    // Only animate if sprite is set
    if (!sprite) return;

    int maxColumnas = 0;

    if (sprite == walkDerecha || sprite == walkIzq)
        maxColumnas = 1536; // 12 frames * 128px
    else if (sprite == idle)
        maxColumnas = 758;  // idle sprite width
    else if (sprite == attack_der || sprite == attack_izq)
        maxColumnas = 768; // 6 frames * 128px (adjust to your sheet)

    columnas += 128;
    if (columnas >= maxColumnas)
        columnas = 0;

    Caminar(); // handles movement

    update(-ancho/2, -alto/2, ancho, alto);
}

void Protagonista::moverDerecha()
{
    velocidadX = 12;
    sprite = walkDerecha;
}

void Protagonista::moverIzquierda()
{
    velocidadX = -12;
    sprite = walkIzq;
}

void Protagonista::moverArriba()
{
    velocidadY = -12;
    sprite = walkDerecha;
}

void Protagonista::moverAbajo()
{
    velocidadY = 12;
    sprite = walkIzq;
}

void Protagonista::Detener()
{
    velocidadX = 0;
    velocidadY = 0;
    sprite = idle;
}

void Protagonista::Caminar()
{
    if (!scene()) return;

    qreal newX = x() + velocidadX;
    qreal newY = y() + velocidadY;

    QRectF bounds = scene()->sceneRect();
    QRectF spriteRect = boundingRect();

    if (newX - spriteRect.width()/2 < bounds.left())  newX = bounds.left() + spriteRect.width()/2;
    if (newY - spriteRect.height()/2 < bounds.top())  newY = bounds.top() + spriteRect.height()/2;
    if (newX + spriteRect.width()/2 > bounds.right()) newX = bounds.right() - spriteRect.width()/2;
    if (newY + spriteRect.height()/2 > bounds.bottom()) newY = bounds.bottom() - spriteRect.height()/2;

    setPos(newX, newY);

    QList<QGraphicsItem*> collisions = collidingItems();
    bool inTrigger = false;

    for (auto item : collisions) {
        QString type = item->data(0).toString();

        if (type == "wall") {
            setPos(x() - velocidadX, y() - velocidadY);
            break;
        }
        else if (type == "object" || type == "trigger"|| type == "team"
                   || type == "npc" || type == "table"
                   || type == "roulette" || type == "door" || type == "book") {
            inTrigger = true;

            QGraphicsTextItem* label =
                static_cast<QGraphicsTextItem*>(item->data(1).value<void*>());

            if (label && label->scene() == scene()) {
                label->setVisible(true);
                label->setPos(x() - label->boundingRect().width() / 2, y() - 50);
            }
        }
    }

    //SIN TRIGGER
    if (!inTrigger) {
        for (QGraphicsItem* i : scene()->items()) {
            if (i->data(0).toString() == "book" || i->data(0).toString() == "trigger"
                || i->data(0).toString() == "object" || i->data(0).toString() == "door"
                || i->data(0).toString() == "roulette" || i->data(0).toString() == "team"
                || i->data(0).toString() == "npc" || i->data(0).toString() == "table") {

                QGraphicsTextItem* label = static_cast<QGraphicsTextItem*>(i->data(1).value<void*>());
                if (label) label->setVisible(false);
            }
        }
    }
}

void Protagonista::addLifes()
{
    this->lifes++;
}

void Protagonista::death()
{

    sprite = dead;
    columnas = 0;
    ancho = 195;   // width per frame (975 / 5)
    alto = 137;    // height per frame

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

void Protagonista::takeLifes()
{
    this->lifes--;
}

int Protagonista::getLifes()
{
    return this->lifes;
}

QRectF Protagonista::boundingRect() const
{
    return QRectF(-ancho/2,-alto/2,ancho,alto);
}

void Protagonista::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // --- Draw main sprite ---
    painter->drawPixmap(-ancho / 2, -alto / 2, *sprite, columnas, 0, ancho, alto);

    // --- Optional: draw corazones above head (only in battle mode) ---
    if (showHeartsAbove && corazones) {
        int totalFrames = 5;
        int frameWidth = corazones->width() / totalFrames;
        int frameHeight = corazones->height();

        // lifes = 4 → frame 0 (full), lifes = 0 → frame 4 (empty)
        int frameIndex = qBound(0, 4 - lifes, 4);

        // Smaller and higher hearts (like NPC)
        int scaledWidth = frameWidth * 0.7;
        int scaledHeight = frameHeight * 0.7;

        int x = -scaledWidth / 2;
        int y = -alto / 2 - 55;  // slightly higher above head

        painter->drawPixmap(x, y, scaledWidth, scaledHeight,
                            *corazones,
                            frameIndex * frameWidth, 0,
                            frameWidth, frameHeight);
    }
}


void Protagonista::debugPosition() {
    QPointF p = this->pos();
    qDebug() << "[DEBUG] Protagonista at" << p;
}

void Protagonista::setShowHeartsAbove(bool show)
{
    showHeartsAbove = show;
    update();
}
