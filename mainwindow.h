#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include "protagonista.h"
#include "hallway.h"
#include "ruleta.h"
#include "videowindow.h"
#include "player.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(const Player &p, QWidget* parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

private:
    QGraphicsScene* scene;
    QGraphicsView* view;
    Protagonista* protag;
    Player currentPlayer;

    int ancho, alto;
};

#endif // MAINWINDOW_H
