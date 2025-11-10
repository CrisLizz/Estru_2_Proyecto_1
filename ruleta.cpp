#include "ruleta.h"
#include <QRandomGenerator>
#include <QPropertyAnimation>
#include <QDebug>

Ruleta::Ruleta(QObject *parent)
    : QObject{parent},
    currentIndex(0)
{

    art     = new QPixmap(":/Deco/art_t.png");
    science = new QPixmap(":/Deco/ciencia_t.png");
    history = new QPixmap(":/Deco/historia_t.png");
    politics= new QPixmap(":/Deco/politica_t.png");

    frames = {*art, *science, *history, *politics};
    topics = { Art, Science, History, Politics };

    displayItem = new QGraphicsPixmapItem(frames.first());
    displayItem->setPos(400, 300);
    displayItem->setScale(0.6);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Ruleta::nextFrame);
}

// Start the roulette spinning
void Ruleta::startRoulette()
{
    if (frames.isEmpty() || spunRoulette == true) return;

    int interval = 80 + QRandomGenerator::global()->bounded(4) * 10;
    timer->start(interval);

    int totalDuration = 2000 + QRandomGenerator::global()->bounded(2001);

    QTimer::singleShot(totalDuration, this, [this]() {
        stopRoulette();
    });
}

void Ruleta::nextFrame()
{
    if (frames.isEmpty()) return;

    currentIndex = (currentIndex + 1) % frames.size();
    displayItem->setPixmap(frames[currentIndex]);
}

void Ruleta::stopRoulette()
{
    timer->stop();
    if (frames.isEmpty()) return;

    currentTopic = topics[currentIndex];

    displayItem->setPixmap(frames[currentIndex]);

    qDebug() << "Roulette stopped on topic:" << currentTopic;
    qDebug() << "Remaining frames:" << frames.size();

    emit rouletteStopped(currentTopic);

    frames.removeAt(currentIndex);
    topics.removeAt(currentIndex);

    if (currentIndex >= frames.size()) currentIndex = 0;

    spunRoulette = true;
}

void Ruleta::resetSpun()
{
    spunRoulette = false;
}

bool Ruleta::getSpunRoulette()
{
    return spunRoulette;
}

void Ruleta::resetteRoulette()
{
    frames = {*art, *science, *history, *politics};
    topics = { Art, Science, History, Politics };
}
