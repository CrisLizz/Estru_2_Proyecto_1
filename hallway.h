#ifndef HALLWAY_H
#define HALLWAY_H

#include <QGraphicsTextItem>
#include <QPushButton>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QLabel>
#include "menu.h"

#include "ruleta.h"
#include "descartes_lab.h"
#include "hearts.h"
#include "ciencia.h"
#include "politics.h"
#include "history.h"
#include "kant_class.h"
#include "arte.h"
#include "batalla.h"
#include "protagonista.h"
#include "mapa.h"
#include "inventory.h"
#include "player.h"

class hallway : public QWidget
{
    Q_OBJECT
public:
    explicit hallway(const Player &p, QWidget* parent = nullptr);

    void loadLobby();


protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

    void walls();
    void scenery();
    void setProtagonist();
    void triggers(int index);
    void playRoulette();

private slots:
    void openDoors(Ruleta::Topic topic);

private:
    QGraphicsScene* scene;
    QGraphicsView* view;

    Player currentPlayer;

    //call classes - props + protag
    Protagonista* protag;
    Ruleta* roulette;
    hearts* lifes;
    mapa* map;
    Inventory* inv = nullptr;

    //classes - minigames related
    Ciencia* ciencia;
    Politics* poli;
    History* history;
    Arte* arte;

    bool finishedGamed [2] = {false,false};

    //nivel 3
    Batalla* battle;

    //nivel 4
    Kant_class* kantC;
    descartes_lab* labD;
    //arte

    int ancho, alto;

    //bool - call function
    bool cienciaCalled;
    void minigameCiencia(); //done

    bool artCalled;
    void minigameArte(); //done

    bool politicsCalled;
    void minigamePolitica(); //done

    bool historyCalled;
    void minigameHistoria(); // done

    //missing narration - still missing - map done - narration missing
    void removeItems();

    void chooseTeam(); // - done
    void intermission(); // - done

    //minigame lvl 3
    bool battleWindow;
    void Batalla_window(); // missing idk tecniclly done

    //lvl 4 missing
    bool kantCalled;
    void kant(); // started

    bool desWindow();

    bool DescartesCalled;
    void descartes(); // started
    void kant_descartes(); // done

    void toMenu(); // done

    QPushButton* show_map;
    void callMap(); //maybe? idk

    void walls_intermision();
    void closeClasses();

    //puertas
    QGraphicsPixmapItem* right_door_close;
    QGraphicsPixmapItem* left_door_close;
    QGraphicsPixmapItem* right_door_down;
    QGraphicsPixmapItem* left_door_down;
    QGraphicsPixmapItem* board;
    QGraphicsPixmapItem* door;

    QGraphicsRectItem* roulette_T;
    QGraphicsTextItem* roulette_TL;

    void loadDoor();

public slots:


signals:
    void endGame();
};


#endif // HALLWAY_H
