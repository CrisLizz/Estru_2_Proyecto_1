#ifndef CUESTIONARIO_H
#define CUESTIONARIO_H

#include <QString>
#include <QVector>
#include <QQueue>

class cuestionario
{
public:
    cuestionario();

    struct Preguntas {
        QString pregunta;
        QVector<QString> opciones;
        int opcionCorrecta;
    };

    void insertarArte();
    void insertarPolitica();
    void insertarCiencia();
    void insertarHistoria();
    void insertarBatalla();
    void insertarKant();
    void insertarDescartes();

    // Mostrar
    QString mostrarArte();
    QString mostrarPolitica();
    QString mostrarCiencia();
    QString mostrarHistoria();

    void siguientePregunta(QQueue<Preguntas>& cola);
    void quitarPregunta(QQueue<Preguntas>& cola);

    QQueue<Preguntas> arteQueue;
    QQueue<Preguntas> KantQueue;
    QQueue<Preguntas> DescartesQueue;
    QQueue<Preguntas> politicaQueue;
    QQueue<Preguntas> cienciaQueue;
    QQueue<Preguntas> batallaQueue;
    QQueue<Preguntas> historiaQueue;

private:

};

#endif // CUESTIONARIO_H
