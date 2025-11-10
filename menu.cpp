#include "menu.h"
#include "mainwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMovie>
#include <QDebug>
#include "player.h"
#include <QInputDialog>

menu::menu(QWidget *parent)
    : QWidget{parent}
{
    setFixedSize(1000, 600);

    fondo = new QLabel(this);
    fondo->setGeometry(0, 0, width(), height());
    fondo->setScaledContents(true);

    QMovie* movie = new QMovie(":/Fondos/school_Menu.gif");
    if(!movie->isValid())
        qDebug() << "No se pudo cargar el GIF";
    else
        fondo->setMovie(movie);
    movie->start();
    fondo->lower();

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);

    title = new QLabel("Juego del Conocimiento",this);
    playButton = new QPushButton("Jugar", this);
    exitButton = new QPushButton("Salir", this);

    QString estiloLabel =
        "QLabel {"
        " color: black;"
        "font-bold;"
        " font-family: 'Courier New';"
        " font-size: 48px;"
        "}";


    QString estiloBoton =
        "QPushButton {"
        " background-color: rgba(30, 30, 30, 190);"
        " color: white;"
        " border: 2px solid #ccc;"
        " border-radius: 8px;"
        " font-family: 'Courier New';"
        " padding: 14px 28px;"
        " font-size: 16px;"
        " min-width: 280px;"
        "}"
        "QPushButton:hover {"
        " background-color: rgba(60, 60, 60, 220);"
        "}";

    title->setStyleSheet(estiloLabel);
    playButton->setStyleSheet(estiloBoton);
    exitButton->setStyleSheet(estiloBoton);

    layout->addWidget(title);
    layout->addWidget(playButton);
    layout->addWidget(exitButton);

    setLayout(layout);

    connect(exitButton, &QPushButton::clicked, this, &QWidget::close);
    connect(playButton, &QPushButton::clicked, this, &menu::onPlayButtonClicked);

}

#include <QInputDialog>

void menu::onPlayButtonClicked() {
    bool ok;
    QString name = QInputDialog::getText(this, "Nombre del jugador",
                                         "Ingrese su nombre:", QLineEdit::Normal,
                                         "", &ok);
    if(ok && !name.isEmpty()) {
        Player currentPlayer(name);
        // Load leaderboard
        QList<Player> players = currentPlayer.loadPlayers("players.json");
        players.append(currentPlayer); // add new player
        currentPlayer.savePlayers(players, "players.json");

        MainWindow* game = new MainWindow(currentPlayer); // pass player to game
        game->show();
        this->close();
    }
}

