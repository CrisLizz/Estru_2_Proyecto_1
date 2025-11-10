#ifndef NODO_H
#define NODO_H

#include <QString>
#include <QPointF>

class Nodo {
public:
    QString nombre;
    QPointF posicion;
    bool completado = false;
    bool disponible = false;

    Nodo(const QString& n = QString(), const QPointF& pos = QPointF())
        : nombre(n), posicion(pos) {}
};

#endif // NODO_H
