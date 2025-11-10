#ifndef INVENTORY_H
#define INVENTORY_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QMap>
#include <QListWidget>
#include <QPropertyAnimation>

#include "nodo.h"
#include "player.h"
#include "aristas.h"

class Inventory : public QWidget
{
    Q_OBJECT
public:
    explicit Inventory(QWidget *parent = nullptr);

    void configurarGrafoPorDefecto();
    void dibujarGrafo();
    void completarNodo(const QString &nombre); // marca completado y desbloquea rutas
    Nodo* buscarNodo(const QString &nombre);

private:
    QList<Nodo*> m_nodos;
    QList<Arista*> m_aristas;

    QGraphicsScene* m_scene = nullptr;
    QMap<Nodo*, QGraphicsEllipseItem*> m_nodoItems;
    QMap<Nodo*, QGraphicsTextItem*> m_labelItems;
    QMap<Arista*, QGraphicsLineItem*> m_aristaBaseItems;    // grises
    QMap<Arista*, QGraphicsLineItem*> m_aristaOverlayItems; // verdes animadas

    QList<QPropertyAnimation*> m_animaciones;

    void desbloquearAristasSalientes(Nodo* nodo);
    void actualizarVisualNodo(Nodo* nodo);

    QWidget* leaderboardWidget;
    QWidget* logrosContainer;

    QListWidget* leaderboardList;
    Player players;

    void mostrarLeaderboard(); // fills leaderboardList
    void mostrarLogros();
};

#endif // INVENTORY_H

