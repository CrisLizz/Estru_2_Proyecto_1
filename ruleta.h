#ifndef RULETA_H
#define RULETA_H

#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsScene>
#include <QLabel>
#include <QObject>
#include <QList>

class Ruleta : public QObject
{
    Q_OBJECT
public:
    explicit Ruleta(QObject *parent = nullptr);
    QGraphicsPixmapItem* getDisplayItem() const { return displayItem; }

    QTimer* timer;

    //options
    QPixmap* art;
    QPixmap* science;
    QPixmap* history;
    QPixmap* politics;

    QList<QPixmap> frames;

    QGraphicsPixmapItem* displayItem;

    int currentIndex = 0;

    void startRoulette();
    void deleteElement();
    void stopRoulette();

    bool spunRoulette = false;

    void resetSpun();

    bool getSpunRoulette();

    void resetteRoulette();

    enum Topic { Art, Science, History, Politics };
    Topic currentTopic;
    QList<Topic> topics;
    Topic getCurrentTopic() const { return currentTopic; }

signals:
    void rouletteStopped(Topic topic);

private slots:
    void nextFrame();

signals:
};

#endif // RULETA_H
