#include "player.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>

QList<Player> loadPlayers(const QString &fileName) {
    QList<Player> players;
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        QJsonArray arr = doc.array();
        for(const auto &v : arr)
            players.append(Player::fromJson(v.toObject()));
        file.close();
    } else {
        qDebug() << "Could not open" << fileName << "for reading.";
    }
    return players;
}

void savePlayers(const QList<Player> &players, const QString &fileName) {
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly)) {
        QJsonArray arr;
        for(const Player &p : players)
            arr.append(p.toJson());
        QJsonDocument doc(arr);
        file.write(doc.toJson());
        file.close();
    } else {
        qDebug() << "Could not open" << fileName << "for writing.";
    }
}
