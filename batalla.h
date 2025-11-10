
#ifndef BATALLA_H
#define BATALLA_H

#include <QtMultimedia/QMediaPlayer>
#include <QUrl>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QTimer>
#include "protagonista.h"
#include "npcs.h"
#include <QAudioOutput>
#include "cuestionario.h"
#include <QAbstractButton>
#include <QPushButton>


class Batalla : public QObject
    {
        Q_OBJECT
    public:
        explicit Batalla(QGraphicsScene* scene, bool team, Protagonista* protag);

        void chooseAnswer(int key);
        void endBattle();
        bool cantMove = true;
        bool battleEnded = false;

    private:
        QMediaPlayer* player;
        QAudioOutput* audio;
        bool attackInProgress = false;
        QGraphicsScene* m_scene;
        Protagonista* protagonista;
        Npcs* npc;
        cuestionario* battle;
        QGraphicsTextItem* question = nullptr;
        cuestionario::Preguntas currentQuestion;
        bool playerTurn = true;


        void loadQuestion();
        void answerQuestion(bool isPlayer, int choice);
        void removeCurrentQuestion();
        void npcAnswer();
        void attack(bool correct, bool isPlayer);
        void dead();
        void showTemporaryMessage(const QString& imagePath);
        void wall(QGraphicsScene* scene);
        void loadNpc(bool team);
        void showStyledMessage(const QString& title, const QString& text, const QString& team);

        //---    WIN MUSIC AND WIN THINGS    ---
        void playWinnerMusic(const QString& path);
        void GanoRacionalista();

        void GanoEmpirista();
        void Empate();

    signals:
        void minigameFinished();
        void returnToLobby();
    };

#endif // BATALLA_H
