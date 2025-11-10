#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QJsonObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>


class Player {
public:
    QString name;
    int score;

    Player(const QString &n = "", int s = 0) : name(n), score(s) {}

    // Serialize to JSON
    QJsonObject toJson() const {
        QJsonObject obj;
        obj["name"] = name;
        obj["score"] = score;
        return obj;
    }

    // Deserialize from JSON
    static Player fromJson(const QJsonObject &obj) {
        Player p;
        p.name = obj["name"].toString();
        p.score = obj["score"].toInt();
        return p;
    }

    QList<Player> loadPlayers(const QString &fileName) {
        QList<Player> players;
        QFile file(fileName);
        if(file.exists()) {
            if(file.open(QIODevice::ReadOnly)) {
                QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
                QJsonArray arr = doc.array();
                for(const auto &v : arr)
                    players.append(Player::fromJson(v.toObject()));
                file.close();
            } else {
                qDebug() << "Could not open" << fileName << "for reading.";
            }
        } else {
            qDebug() << fileName << "does not exist. Starting with empty player list.";
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

    // Update the player's score and save immediately
    void updateScore(int newScore, const QString &fileName) {
        // Load all players
        QList<Player> players = loadPlayers(fileName);
        bool found = false;

        // Look for this player
        for (Player &p : players) {
            if (p.name == name) {
                p.score += newScore;  // update score in list
                found = true;
                break;
            }
        }

        // If player not found, add them
        if (!found) {
            Player p(name, newScore);
            players.append(p);
        }

        // Save updated list
        savePlayers(players, fileName);

        // Update this instance as well
        score += newScore;
    }

};

#endif // PLAYER_H
