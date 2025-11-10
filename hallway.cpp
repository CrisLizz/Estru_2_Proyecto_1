#include "hallway.h"
#include <QMessageBox>

hallway::hallway(const Player &p, QWidget* parent)
    : QWidget(parent), currentPlayer(p)
{
    cienciaCalled = false;
    politicsCalled = false;
    historyCalled = false;
    artCalled = false;
    battleWindow = false;
    kantCalled = false;
    DescartesCalled = false;

    scenery();

    walls();

    setProtagonist();

    //triggers(1);

    playRoulette();

    //so as not to deactivate key_commands
    view->setFocusPolicy(Qt::NoFocus);
    this->setFocusPolicy(Qt::StrongFocus);
    this->setFocus();

    inv = new Inventory(nullptr);
    inv->setAttribute(Qt::WA_DeleteOnClose, false);
    inv->setWindowFlag(Qt::Window, true);
    inv->setWindowTitle("Inventario");
    inv->setWindowModality(Qt::NonModal);


    connect(roulette, &Ruleta::rouletteStopped, this, &hallway::openDoors);

    //GET RID OF BAR
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

void hallway::keyPressEvent(QKeyEvent* event)
{
    QList<QGraphicsItem*> collisions = protag->collidingItems();

    // --- E key ---
    if (event->key() == Qt::Key_E) {
        qDebug() << "key e pressed\n";
        if (cienciaCalled) {
            qDebug() << "cience called\n";

            for (auto item : collisions) {
                qDebug() << "Item type:" << item->data(0).toString();
                if (item->data(0).toString() == "door") {
                    int doorID = item->data(3).toInt();
                    qDebug() << "Calling correctDoor with doorID" << doorID;
                    ciencia->correctDoor(doorID);
                    break;
                }
            }
        }
        else if (historyCalled) {
            QList<QGraphicsItem*> collisions = protag->collidingItems();
            for (auto item : collisions) {
                if (item->data(0) == "book") {
                    int id = item->data(3).toInt();
                    history->pickUpBook(id);
                }
                else if (item->data(0) == "npc") {
                    history->returnBookToNPC();
                }
            }
        }
        else if (artCalled) {
            for (auto item : collisions) {
                qDebug() << "Item type:" << item->data(0).toString();
                if (item->data(0).toString() == "object") {
                    int objectID = item->data(3).toInt();
                    qDebug() << "Calling correctDoor with doorID" << objectID;
                    arte->checkAnswer(objectID);
                    break;
                }
            }
        }
        // 🧠 === KANT INTERACTION ===
        else if (kantCalled) {
            for (auto item : collisions) {
                if (item->data(0).toString() == "npc") {
                    // Make sure it's Kant's trigger
                    kantC->onKantTalk();
                    break;
                }
                else if (item->data(0) == "object") {
                    int hintID = item->data(3).toInt();
                    kantC->loadMesssages(hintID);
                }
            }
        }
        else if (DescartesCalled){
            for (auto item : collisions) {
                if (item->data(0).toString() == "npc") {
                    labD->onKantTalk();
                    break;
                }
                else if (item->data(0) == "table") {
                    int hintID = item->data(3).toInt();
                    labD->loadMesssages(hintID);
                }
            }
        }
        // 🎯 Default (roulette etc.)
        else {
            for (auto item : collisions) {
                if (item->data(0).toString() == "roulette") {
                    roulette->startRoulette();
                    break;
                }
            }
        }
    }

    // --- A key ---
    else if (event->key() == Qt::Key_A) {
        for (auto item : collisions) {
            if (item->data(0).toString() == "trigger") {
                int id = item->data(2).toInt();
                switch (id) {
                case 1: minigameArte(); break;
                case 2: minigameCiencia(); break;
                case 3: minigameHistoria(); break;
                case 4: minigamePolitica(); break;
                case 5: intermission(); break;
                case 6: this->descartes(); break;
                case 7: this->kant(); break;
                }
                break;
            }
            else if (item->data(0).toString() == "team") {
                int id = item->data(2).toInt();
                switch (id) {
                case 1:
                    inv->completarNodo("Racionalista");
                    protag->changeTeam(id);
                    break;
                case 2:
                    inv->completarNodo("Empirista");
                    protag->changeTeam(id);
                    break;
                default:
                    qDebug() << "Unknown team id:" << id;
                    break;
                }

                // call battle
                this->Batalla_window();
            }

        }
    }

    // === Battle Keys ===
    if (battleWindow) {
        qDebug() << "entered battleWindow";

        if (battle->cantMove) {
            // Only allow answer keys if cantMove is true
            switch (event->key()) {
            case Qt::Key_1: battle->chooseAnswer(0); break;
            case Qt::Key_2: battle->chooseAnswer(1); break;
            case Qt::Key_3: battle->chooseAnswer(2); break;
            case Qt::Key_4: battle->chooseAnswer(3); break;
            default: return; // ignore all other keys
            }
            return;
        }
        QWidget::keyPressEvent(event);
    }

    else if (event->key() == Qt::Key_M) {
        map = new mapa();
        map->setWindowModality(Qt::ApplicationModal);
        map->show();
    }
    else if (event->key() == Qt::Key_I) {
        if (inv->isVisible()) {
            inv->hide();
        } else {
            inv->show();
            inv->raise();
            inv->activateWindow();
        }
    }


    // --- Movement ---
    else if (event->key() == Qt::Key_Left)  protag->moverIzquierda();
    else if (event->key() == Qt::Key_Right) protag->moverDerecha();
    else if (event->key() == Qt::Key_Up)    protag->moverArriba();
    else if (event->key() == Qt::Key_Down)  protag->moverAbajo();
    else if (event->key() == Qt::Key_1)     protag->debugPosition();
}


void hallway::keyReleaseEvent(QKeyEvent* event)
{
    switch(event->key())
    {
    case Qt::Key_Right:
    case Qt::Key_Left:
    case Qt::Key_Up:
    case Qt::Key_Down:
        protag->Detener();
        break;
    default: QWidget::keyReleaseEvent(event);
    }
}

void hallway::walls()
{
    //wall left
    QGraphicsRectItem* wall_left = new QGraphicsRectItem(0, 0, 110, 10);
    wall_left->setPos(40, 380);
    wall_left->setBrush(Qt::NoBrush);
    wall_left->setPen(Qt::NoPen);
    wall_left->setData(0,"wall");

    scene->addItem(wall_left);

    //wall_center
    QGraphicsRectItem* wall_center = new QGraphicsRectItem(0, 0, 1000, 225);
    wall_center->setPos(0, -100);
    wall_center->setBrush(Qt::NoBrush);
    wall_center->setPen(Qt::NoPen);
    wall_center->setData(0,"wall");

    scene->addItem(wall_center);

    //wall right
    QGraphicsRectItem* wall_right = new QGraphicsRectItem(0, 0, 110, 10);
    wall_right->setPos(840, 380);
    wall_right->setBrush(Qt::NoBrush);
    wall_right->setPen(Qt::NoPen);
    wall_right->setData(0,"wall");

    scene->addItem(wall_right);

    QGraphicsRectItem* plant1 = new QGraphicsRectItem(0, 0, 2, 2);
    plant1->setPos(330, 498);
    plant1->setBrush(Qt::NoBrush);
    plant1->setPen(Qt::NoPen);
    plant1->setData(0,"wall");

    scene->addItem(plant1);

    QGraphicsRectItem* plant2 = new QGraphicsRectItem(0, 0, 2, 2);
    plant2->setPos(640, 498);
    plant2->setBrush(Qt::NoBrush);
    plant2->setPen(Qt::NoPen);
    plant2->setData(0,"wall");

    scene->addItem(plant2);
}

void hallway::scenery()
{
    ancho = 1000;
    alto = 600;
    setFixedSize(ancho, alto);

    QPixmap background(":/Fondos/looby_v5.jpg");

    scene = new QGraphicsScene(0, 0, ancho, alto, this);

    scene->setSceneRect(0, 0, 1000, 600);
    scene->setBackgroundBrush(background.scaled(scene->sceneRect().size().toSize(),
                                                Qt::IgnoreAspectRatio,
                                                Qt::SmoothTransformation));


    view = new QGraphicsView(scene, this);
    view->setGeometry(0, 0, ancho, alto);

    this->setFocusPolicy(Qt::StrongFocus);
    this->setFocus();

    view->setRenderHint(QPainter::SmoothPixmapTransform);
    view->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    board = new QGraphicsPixmapItem(QPixmap(":/Deco/board.png"));
    board->setPos(360, 55);
    scene->addItem(board);

    //roulette
    roulette = new Ruleta();
    roulette->getDisplayItem()->setPos(395,110);
    scene->addItem(roulette->getDisplayItem());

    //install the doors
    right_door_close = new QGraphicsPixmapItem(QPixmap(":/Deco/right_door_close.png"));
    left_door_close = new QGraphicsPixmapItem(QPixmap(":/Deco/left_door_close.png"));

    right_door_down = new QGraphicsPixmapItem(QPixmap(":/Deco/right_door_close.png"));
    left_door_down = new QGraphicsPixmapItem(QPixmap(":/Deco/left_door_close.png"));

    //left
    left_door_close->setPos(1,280);
    left_door_close->setScale(1.5);

    left_door_down->setPos(1,500);
    left_door_down->setScale(1.5);

    //right
    right_door_close->setPos(940,280);
    right_door_close->setScale(1.5);

    right_door_down->setPos(940,500);
    right_door_down->setScale(1.5);

    scene->addItem(right_door_close);

    scene->addItem(right_door_down);

    scene->addItem(left_door_close);
    scene->addItem(left_door_down);


}

void hallway::setProtagonist()
{
    lifes = new hearts();
    scene->addItem(lifes);
    lifes->setPos(840,0);

    protag = new Protagonista();
    protag->setZValue(1);
    scene->addItem(protag);
    protag->setPos(ancho/2, 520);

    lifes->showLife(protag->getLifes());

}

void hallway::triggers(int index)
{
    int x = 0;
    int y = 0;

    switch(index){
    case 1:
        x = 10;
        y = 200;
        break;
    case 2:
        x = 950;
        y = 200;
        break;
    case 3:
        x = 10;
        y = 460;
        break;
    case 4:
        x = 950;
        y = 460;
        break;
    }

    if (index != 0){
    QGraphicsRectItem* triggerZone = new QGraphicsRectItem(x, y, 50, 90);
    triggerZone->setBrush(Qt::NoBrush);
    triggerZone->setPen(QPen(Qt::NoPen));
    triggerZone->setData(0, "trigger");

    //POP-UP message for the trigger thingy
    QGraphicsTextItem* trigger_label = new QGraphicsTextItem("Press A to enter!");
    trigger_label->setDefaultTextColor(Qt::white);
    trigger_label->setZValue(10);
    trigger_label->setVisible(false);

    triggerZone->setData(1, QVariant::fromValue<void*>(trigger_label));
    triggerZone->setData(2, index);

    scene->addItem(triggerZone);
    scene->addItem(trigger_label);
    }
}

void hallway::playRoulette(){
    //-------- ROULETTE ---------------

    qDebug() << "roulette called well the QGraphicsItm";

    if (roulette->spunRoulette != true){
        roulette_T = new QGraphicsRectItem(470, 50, 50, 90);
        roulette_T->setBrush(Qt::NoBrush);
        roulette_T->setPen(QPen(Qt::NoPen));
        roulette_T->setData(0, "roulette");

        //POP-UP message for the trigger thingy
        roulette_TL = new QGraphicsTextItem("Press E to spin!");
        roulette_TL->setDefaultTextColor(Qt::white);
        roulette_TL->setZValue(10);
        roulette_TL->setVisible(false);

        roulette_T->setData(1, QVariant::fromValue<void*>(roulette_TL));
        roulette_T->setData(2,3);

        scene->addItem(roulette_T);
        scene->addItem(roulette_TL);
    }
}

void hallway::loadDoor(){
    //440,196 for the door

    door = new QGraphicsPixmapItem(QPixmap(":/Deco/open_door.png"));
    door->setPos(430, 110);
    door->setScale(0.5);
    door->setZValue(-1);
    scene->addItem(door);

    QGraphicsRectItem* mainDoor = new QGraphicsRectItem(470, 50, 50, 90);
    mainDoor->setBrush(Qt::NoBrush);
    mainDoor->setPen(QPen(Qt::NoPen));
    mainDoor->setData(0, "trigger");

    //POP-UP message for the trigger thingy
    QGraphicsTextItem* mainDoorLB = new QGraphicsTextItem("Press A to enter!");
    mainDoorLB->setDefaultTextColor(Qt::white);
    mainDoorLB->setZValue(10);
    mainDoorLB->setVisible(false);

    mainDoor->setData(1, QVariant::fromValue<void*>(mainDoorLB));
    mainDoor->setData(2,5);

    scene->addItem(mainDoor);
    scene->addItem(mainDoorLB);

}

void hallway::openDoors(Ruleta::Topic topic)
{
    int index = 0;
    switch(topic) {
    case Ruleta::Art:
        left_door_close->setPixmap(QPixmap(":/Deco/left_door_open.png"));
        left_door_close->setScale(1.5);
        index = 1;

        break;
    case Ruleta::Science:
        right_door_close->setPixmap(QPixmap(":/Deco/right_door_open.png"));
        right_door_close->setScale(1.5);
        index = 2;

        break;
    case Ruleta::History:
        left_door_down->setPixmap(QPixmap(":/Deco/left_door_open.png"));
        left_door_down->setScale(1.5);
        index = 3;

        break;
    case Ruleta::Politics:
        right_door_down->setPixmap(QPixmap(":/Deco/right_door_open.png"));
        right_door_down->setScale(1.5);
        index = 4;
        break;
    }

    triggers(index);
}

//remover
void hallway::removeItems(){
    if (!scene) return;

    QList<QGraphicsItem*> allItems = scene->items();

    for (auto item : allItems) {

        if (item == roulette->getDisplayItem() || item == board)
        {
            item->setVisible(false);
            continue;
        }

        if (item == protag || item == lifes) continue;

        scene->removeItem(item);
        delete item;
    }
}

void hallway::chooseTeam()
{
    //racionalista
    QGraphicsRectItem* racionalista = new QGraphicsRectItem(356, 130, 50, 90);
    racionalista->setBrush(Qt::NoBrush);
    racionalista->setPen(QPen(Qt::NoPen));
    racionalista->setData(0, "team");

    QGraphicsTextItem* racionalista_lb = new QGraphicsTextItem("Press A to choose!");
    racionalista_lb->setDefaultTextColor(Qt::white);
    racionalista_lb->setZValue(10);
    racionalista_lb->setVisible(false);

    racionalista->setData(1, QVariant::fromValue<void*>(racionalista_lb));
    racionalista->setData(2,1);

    scene->addItem(racionalista);
    scene->addItem(racionalista_lb);

    //empirista
    QGraphicsRectItem* empirista = new QGraphicsRectItem(632, 130, 50, 90);
    empirista->setBrush(Qt::NoBrush);
    empirista->setPen(QPen(Qt::NoPen));
    empirista->setData(0, "team");

    QGraphicsTextItem* empirista_lb = new QGraphicsTextItem("Press A to choose!");
    empirista_lb->setDefaultTextColor(Qt::white);
    empirista_lb->setZValue(10);
    empirista_lb->setVisible(false);

    empirista->setData(1, QVariant::fromValue<void*>(empirista_lb));
    empirista->setData(2,2);

    scene->addItem(empirista);
    scene->addItem(empirista_lb);
}

void hallway::intermission()
{
    removeItems();

    // --- Change background for the mini-game ---
    QPixmap newBackground(":/Fondos/lobby_2.jpg");
    scene->setBackgroundBrush(newBackground.scaled(
        scene->sceneRect().size().toSize(),
        Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation
        ));

    protag->setPos(500,524);
    walls_intermision();
    chooseTeam();

    scene->update();
}

void hallway::Batalla_window()
{
    removeItems();

    // --- Change background for the mini-game ---
    QPixmap newBackground(":/Fondos/batalla.jpg");
    scene->setBackgroundBrush(newBackground.scaled(
        scene->sceneRect().size().toSize(),
        Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation
        ));

    lifes->setVisible(false);

    protag->setPos(440,416);

    protag->setShowHeartsAbove(true);
    battleWindow = true;

    this->battle = new Batalla(this->scene, protag->getEmpirista(), protag);

    connect(battle, &Batalla::minigameFinished, this, &hallway::kant_descartes);
    connect(battle, &Batalla::returnToLobby, this, &hallway::toMenu);

    scene->update();
}

void hallway::kant()
{
    removeItems();

    kantCalled = true;

    // --- Change background for the mini-game ---
    QPixmap newBackground(":/Fondos/kant_classroom.jpg");
    scene->setBackgroundBrush(newBackground.scaled(
        scene->sceneRect().size().toSize(),
        Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation
        ));

    protag->resetearProtag();
    protag->setPos(936,364);

    kantC = new Kant_class(this->scene);

    connect(kantC, &Kant_class::minigameFinished, this, &hallway::kant_descartes);

    scene->update();
}


void hallway::descartes()
{
    removeItems();

    DescartesCalled = true;

    // --- Change background for the mini-game ---
    QPixmap newBackground(":/Fondos/labo_descartes.jpg");
    scene->setBackgroundBrush(newBackground.scaled(
        scene->sceneRect().size().toSize(),
        Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation
        ));

    protag->resetearProtag();
    protag->setPos(636,300);

    labD = new descartes_lab(this->scene);

    connect(labD, &descartes_lab::minigameFinished, this, &hallway::kant_descartes);

    scene->update();
}

void hallway::kant_descartes()
{
    removeItems();

    battleWindow = false;

    if (kantCalled && kantC) {
        if (kantC->wonKant){
            inv->completarNodo("Kant");
        }
        this->finishedGamed[0] = true;
        kantC->deleteLater();
        kantC = nullptr;
        kantCalled = false;
    }

    if (DescartesCalled && labD) {
        if (labD->wonDescart){
            inv->completarNodo("Descartes");
        }
        this->finishedGamed[1] = true;
        labD->deleteLater();
        labD = nullptr;
        DescartesCalled = false;
    }

    // ---------- Stupid wall ----------
    QGraphicsRectItem* wall_center = new QGraphicsRectItem(0, 0, 1000, 275);
    wall_center->setPos(0, -100);
    wall_center->setBrush(Qt::NoBrush);
    wall_center->setPen(Qt::NoPen);
    wall_center->setData(0,"wall");
    scene->addItem(wall_center);

    // ---------- Triggers ----------
    QGraphicsRectItem* lab = new QGraphicsRectItem(188, 130, 50, 90);
    lab->setBrush(Qt::NoBrush);
    lab->setPen(QPen(Qt::NoPen));
    lab->setData(0, "trigger");

    QGraphicsTextItem* lab_lb = new QGraphicsTextItem("Press A to choose!");
    lab_lb->setDefaultTextColor(Qt::white);
    lab_lb->setZValue(10);
    lab_lb->setVisible(false);
    lab->setData(1, QVariant::fromValue<void*>(lab_lb));
    lab->setData(2,6);
    scene->addItem(lab);
    scene->addItem(lab_lb);

    QGraphicsRectItem* aula = new QGraphicsRectItem(800, 130, 50, 90);
    aula->setBrush(Qt::NoBrush);
    aula->setPen(QPen(Qt::NoPen));
    aula->setData(0, "trigger");

    QGraphicsTextItem* aula_lb = new QGraphicsTextItem("Press A to choose!");
    aula_lb->setDefaultTextColor(Qt::white);
    aula_lb->setZValue(10);
    aula_lb->setVisible(false);
    aula->setData(1, QVariant::fromValue<void*>(aula_lb));
    aula->setData(2,7);
    scene->addItem(aula);
    scene->addItem(aula_lb);

    // ---------- Background ----------
    QPixmap newBackground(":/Fondos/kant_descartes.jpg");
    scene->setBackgroundBrush(newBackground.scaled(
        scene->sceneRect().size().toSize(),
        Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation
        ));

    protag->resetearProtag();
    protag->setPos(500,524);

    // ---------- Message Box ----------
    if (finishedGamed[0] && finishedGamed[1]) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("¡Felicidades!");
        msgBox.setText("Has completado el Juego del Conocimiento.");
        msgBox.setInformativeText("¿Deseas quedarte explorando o volver al menu principal?");
        msgBox.setIcon(QMessageBox::Information);

        QPushButton* stayButton = msgBox.addButton("Quedarme", QMessageBox::YesRole);
        QPushButton* menuButton = msgBox.addButton("Volver al menú", QMessageBox::NoRole);

        msgBox.exec();

        if (msgBox.clickedButton() == stayButton) {
            qDebug() << "Jugador eligió quedarse.";
            // player stays, can only replay Kant/Descartes
        } else if (msgBox.clickedButton() == menuButton) {
            toMenu(); // calls your menu function
        }
    }

    scene->update();
}


void hallway::toMenu()
{
    menu* men = new menu();
    men->show();
    this->close();
}

void hallway::walls_intermision()
{
    //wall left
    QGraphicsRectItem* wall_left = new QGraphicsRectItem(0, 0, 110, 100);
    wall_left->setPos(110, 380);
    wall_left->setBrush(Qt::NoBrush);
    wall_left->setPen(Qt::NoPen);
    wall_left->setData(0,"wall");

    scene->addItem(wall_left);

    //wall_center
    QGraphicsRectItem* wall_center = new QGraphicsRectItem(0, 0, 1000, 275);
    wall_center->setPos(0, -100);
    wall_center->setBrush(Qt::NoBrush);
    wall_center->setPen(Qt::NoPen);
    wall_center->setData(0,"wall");

    scene->addItem(wall_center);

    //wall right
    QGraphicsRectItem* wall_right = new QGraphicsRectItem(0, 0, 110, 100);
    wall_right->setPos(800, 380);
    wall_right->setBrush(Qt::NoBrush);
    wall_right->setPen(Qt::NoPen);
    wall_right->setData(0,"wall");

    scene->addItem(wall_right);

    //book_left
    QGraphicsRectItem* book_left = new QGraphicsRectItem(0, 0, 300, 10);
    book_left->setPos(0, 330);
    book_left->setBrush(Qt::NoBrush);
    book_left->setPen(Qt::NoPen);
    book_left->setData(0,"wall");

    scene->addItem(book_left);

    //book right
    QGraphicsRectItem* book_right = new QGraphicsRectItem(0, 0, 300, 10);
    book_right->setPos(705,330);
    book_right->setBrush(Qt::NoBrush);
    book_right->setPen(Qt::NoPen);
    book_right->setData(0,"wall");

    scene->addItem(book_right);

    //door 1 to choose
    QGraphicsRectItem* door1 = new QGraphicsRectItem(470, 50, 50, 90);
    door1->setBrush(Qt::NoBrush);
    door1->setPen(QPen(Qt::NoPen));
    door1->setData(0, "trigger");

    //POP-UP message for the trigger thingy
    QGraphicsTextItem* door1_lb = new QGraphicsTextItem("Press A to choose!");
    door1_lb->setDefaultTextColor(Qt::white);
    door1_lb->setZValue(10);
    door1_lb->setVisible(false);

    door1->setData(1, QVariant::fromValue<void*>(door1_lb));
    door1->setData(2,1);

    scene->addItem(door1);
    scene->addItem(door1_lb);

    //door 2
    QGraphicsRectItem* door2 = new QGraphicsRectItem(470, 50, 50, 90);
    door2->setBrush(Qt::NoBrush);
    door2->setPen(QPen(Qt::NoPen));
    door2->setData(0, "trigger");

    //POP-UP message for the trigger thingy
    QGraphicsTextItem* door2_lb = new QGraphicsTextItem("Press A to choose!");
    door2_lb->setDefaultTextColor(Qt::white);
    door2_lb->setZValue(10);
    door2_lb->setVisible(false);

    door2->setData(1, QVariant::fromValue<void*>(door2_lb));
    door2->setData(2,2);

    scene->addItem(door2);
    scene->addItem(door2_lb);
}

void hallway::minigameCiencia()
{
    removeItems();

    this->cienciaCalled = true;

    // --- Change background for the mini-game ---
    QPixmap newBackground(":/Fondos/doors_game.jpg");
    scene->setBackgroundBrush(newBackground.scaled(
        scene->sceneRect().size().toSize(),
        Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation
        ));

    protag->setPos(936,330);

    //pos door
    ciencia = new Ciencia(this->scene);
    connect(ciencia, &Ciencia::minigameFinished, this, &hallway::loadLobby);

    roulette->resetSpun();

    scene->update();
}

void hallway::minigamePolitica()
{
    removeItems();
    //
    this->politicsCalled = true;

    QPixmap newBackground(":/Fondos/politics.jpg");
    scene->setBackgroundBrush(newBackground.scaled(
        scene->sceneRect().size().toSize(),
        Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation
        ));

    poli = new Politics(this->scene);

    connect(poli, &Politics::gameFinished, this, &hallway::loadLobby);
    qDebug() << "loaded connect";

    roulette->resetSpun();
    scene->update();
    qDebug() << "updated scene connect";

}

void hallway::minigameHistoria()
{
    removeItems();

    //
    QPixmap newBackground(":/Fondos/history_v2.jpg");
    scene->setBackgroundBrush(newBackground.scaled(
        scene->sceneRect().size().toSize(),
        Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation
        ));

    history = new History(this->scene);

    historyCalled = true;

    protag->setPos(488,532);

    connect(history, &History::minigameFinished, this, &hallway::loadLobby);

    roulette->resetSpun();
    scene->update();

}

void hallway::minigameArte()
{
    removeItems();

    //
    QPixmap newBackground(":/Fondos/art_classroom.jpg");
    scene->setBackgroundBrush(newBackground.scaled(
        scene->sceneRect().size().toSize(),
        Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation
        ));

    arte = new Arte(this->scene);

    artCalled = true;

    protag->setPos(488,532);

    connect(arte, &Arte::minigameFinished, this, &hallway::loadLobby);

    roulette->resetSpun();
    scene->update();
}

void hallway::loadLobby()
{
    // --- Restore hallway background ---
    qDebug() << "entered lobby";

    removeItems();
    qDebug() << "removing items";

    qDebug() << "entered lobby past pol check";

    QPixmap background(":/Fondos/looby_v5.jpg");
    scene->setBackgroundBrush(background.scaled(
        scene->sceneRect().size().toSize(),
        Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation
        ));

    // --- Show previously hidden elements ---
    if (board) {
        board->setVisible(true);
        this->playRoulette();
    }

    if (protag->getLifes() == 0 && roulette->frames.isEmpty()){
        roulette->resetteRoulette();
        qDebug() << "reset roulette";
    }

    else if (protag->getLifes() > 0 && roulette->frames.isEmpty() /*protag->getLifes() > 0*/){
        scene->removeItem(this->board);
        scene->removeItem(roulette->displayItem);
        scene->removeItem(this->roulette_T);
        scene->removeItem(this->roulette_TL);
        loadDoor();

        qDebug() << "load door, delete roulette";
    }

    //install the doors probably someway to make this better
    right_door_close = new QGraphicsPixmapItem(QPixmap(":/Deco/right_door_close.png"));
    left_door_close = new QGraphicsPixmapItem(QPixmap(":/Deco/left_door_close.png"));

    right_door_down = new QGraphicsPixmapItem(QPixmap(":/Deco/right_door_close.png"));
    left_door_down = new QGraphicsPixmapItem(QPixmap(":/Deco/left_door_close.png"));

    //left
    left_door_close->setPos(1,280);
    left_door_close->setScale(1.5);

    left_door_down->setPos(1,500);
    left_door_down->setScale(1.5);

    //right
    right_door_close->setPos(940,280);
    right_door_close->setScale(1.5);

    right_door_down->setPos(940,500);
    right_door_down->setScale(1.5);

    scene->addItem(right_door_close);

    scene->addItem(right_door_down);

    scene->addItem(left_door_close);
    scene->addItem(left_door_down);

    if (roulette && roulette->getDisplayItem()) {
        // ✅ make sure the item still belongs to the scene
        if (scene->items().contains(roulette->getDisplayItem())) {
            roulette->getDisplayItem()->setVisible(true);
            qDebug() << "✅ roulette display restored safely";
        } else {
            qDebug() << "⚠️ roulette display no longer in scene";
        }
    }

    walls();

    if (cienciaCalled) {
        if (ciencia->wonTheGame()) {
            if (inv) {
                inv->completarNodo("Ciencia");
                qDebug () << "node completed?";
            }
            //points
            currentPlayer.updateScore(100,"players.json");

            protag->addLifes();
            lifes->showLife(protag->getLifes());
            protag->setPos(916, 250);
        }
        cienciaCalled = false;
        ciencia->deleteLater();
        ciencia = nullptr;
    }

    //maybe put trigger still and dont reset wheel
    if (politicsCalled) {
        if (poli->wonTheGame()) {
            if (inv) {
                inv->completarNodo("Politica");
                qDebug () << "node completed?";
            }
            //points
            currentPlayer.updateScore(100,"players.json");

            protag->addLifes();
            lifes->showLife(protag->getLifes());
            protag->setPos(888, 508);
        }
        politicsCalled = false;
        poli->deleteLater();
        poli = nullptr;
    }

    if (historyCalled) {
        if (history->wonTheGame()) {
            if (inv) {
                inv->completarNodo("Historia");
                qDebug () << "node completed?";
            }
            //points
            currentPlayer.updateScore(100,"players.json");

            protag->addLifes();
            lifes->showLife(protag->getLifes());
            protag->setPos(76, 512);
        }
        historyCalled = false;
        history->deleteLater();
        history = nullptr;
    }

    qDebug() << "almost to like arte";

    if (artCalled) {
        if (arte->wonTheGame()) {
            if (inv) {
                inv->completarNodo("Arte");
                qDebug () << "node completed?";
            }
            //points
            currentPlayer.updateScore(100,"players.json");

            protag->addLifes();
            lifes->showLife(protag->getLifes());
            protag->setPos(76,284);
        }

        qDebug () << "made it pass the things now deleting";
        artCalled = false;
        arte->deleteLater();
        arte = nullptr;

        qDebug() << "deleted";
    }

    qDebug() << "made it pass arte";

    //reset roulette or not - add if idk

    qDebug() << "evrything passed";

    scene->update();
}
