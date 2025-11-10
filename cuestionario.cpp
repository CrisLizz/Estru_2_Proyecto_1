#include "cuestionario.h"
#include <iostream>
using namespace std;

cuestionario::cuestionario() {}

void cuestionario::insertarArte() {
    arteQueue.enqueue({"¿Quién pintó la Capilla Sixtina?",
                       {"Miguel Ángel", "Donatello", "Leonardo Da Vinci", "Francis Bacon"},
                       0});

    arteQueue.enqueue({"¿Quién esculpió el Moisés, el David y la Pietá?",
                       {"Miguel Ángel Buonarroti", "Leonardo Da Vinci", "Rafael Sanzio", "Galileo Galilei"},
                       0});

    arteQueue.enqueue({"Durante el renacimiento, el estilo artístico dominante fue:",
                       {"Gótico", "Barroco", "Clasicismo", "Romanticismo"},
                       1});

    arteQueue.enqueue({"La nueva visión del hombre reflejada en arte, política y ciencias se llama:",
                       {"Antropocentrismo", "Humanismo", "Paradigma antropológico", "Teocentrismo"},
                       1});

    arteQueue.enqueue({"Leonardo, Donatello, Rafael y Miguel Ángel aparecen en los cómics de:",
                       {"Las tortugas ninjas", "Los caballeros del Zodiaco", "Los cuatro fantásticos", "Attack on Titan"},
                       0});
}

void cuestionario::insertarPolitica() {
    politicaQueue.enqueue({"Durante el renacimiento, el modelo de gobierno es:",
                           {"Monarquía absoluta", "Tiranía republicana", "Democracia participativa", "Liberalismo político"},
                           0});

    politicaQueue.enqueue({"De los siguientes acontecimientos, selecciones el que inicia el período moderno:",
                           {"Toma de Constantinopla", "Tratado de Paz de Westfalia", "Toma de la Bastilla. La ruta de la seda."},
                           1});

    politicaQueue.enqueue({"Durante el siglo XV, la sociedad se estratifica en tres estamentos definidos:",
                           {"Clase media, baja y alta", "Nobleza, clero y estado llano", "Artesanos, guardianes y gobernantes"},
                           1});

    politicaQueue.enqueue({"El realismo político fue desarrollado por:",
                           {"Tomás Moro", "Jean Bodin", "Nicolás Maquiavelo", "Erasmo de Rotterdam"},
                           2});

    politicaQueue.enqueue({"Terminada la Edad Media, en política:",
                           {"La Iglesia resalta su poder", "La Iglesia pierde el papel rector", "La Iglesia evangélica se posiciona", "La política desaparece"},
                           1});
}

void cuestionario::insertarCiencia() {
    cienciaQueue.enqueue({"Filósofo-científico precursor del heliocentrismo:",
                          {"Tomás Moro", "Galileo", "Platón", "Arquímedes"},
                          1});

    cienciaQueue.enqueue({"Uno de los siguientes no es precursor del método científico:",
                          {"Francis Bacon", "Galileo Galilei", "Nicolás Maquiavelo", "René Descartes"},
                          2});

    cienciaQueue.enqueue({"Uno de los precursores del pensamiento moderno:",
                          {"Isaac Newton", "René Descartes", "Erasmo de Rotterdam", "Francis Bacon"},
                          1});

    cienciaQueue.enqueue({"Filósofo que niega el geocentrismo:",
                          {"Aristóteles", "Nicolás Copérnico", "Tomás de Aquino", "Isaac Newton"},
                          1});

    cienciaQueue.enqueue({"Invento de Gutenberg que amplió el conocimiento humano:",
                          {"El astrolabio", "La imprenta", "La Nao y la Carabela", "El telescopio"},
                          1});
}

void cuestionario::insertarHistoria() {
    historiaQueue.enqueue({"Después del feudalismo surge una nueva clase social llamada:",
                           {"La monarquía", "El mercantilismo", "La burguesía", "El proletariado"},
                           2});

    historiaQueue.enqueue({"El renacimiento supone una época de absolutismo y nacionalismos en monarquías como:",
                           {"Grecia", "Inglaterra", "Yugoslavia", "Egipto"},
                           1});

    historiaQueue.enqueue({"Antes del estado moderno, Italia estaba dividida en ciudades-estado como:",
                           {"Florencia-Nápoles", "Ámsterdam-Cracovia", "Reims-Colonia", "Milán-Lourdes"},
                           0});

    historiaQueue.enqueue({"La toma de Constantinopla (bloqueo comercial) ocurrió en lo que hoy es:",
                           {"Eslovaquia", "Estambul, Turquía", "Mesopotamia", "Jerusalén"},
                           1});

    historiaQueue.enqueue({"Resurge el interés por Grecia y Roma, junto a innovaciones como:",
                           {"La imprenta y la brújula", "La rueda y la escritura", "Máquinas de vapor y producción en masa", "La pólvora y la rueda"},
                           0});
}

void cuestionario::insertarBatalla()
{
    batallaQueue.enqueue({
        "Para algunos de los siguientes filósofos, el criterio de verdad es la evidencia sensible:",
        {"Empiristas", "Criticistas", "Racionalistas", "Dogmáticos"},
        0
    });

    batallaQueue.enqueue({
        "De las siguientes, una de ellas es la corriente filosófica que en general tiende a negar la posibilidad de la metafísica y a sostener que hay conocimiento únicamente de los fenómenos.",
        {"Racionalistas", "Empiristas", "Escolásticos", "Escépticos"},
        1
    });

    batallaQueue.enqueue({
        "Para unos de los siguientes filósofos, la experiencia como única fuente del conocimiento.",
        {"Epistemólogos", "Racionalistas", "Empiristas", "Escépticos"},
        2
    });

    batallaQueue.enqueue({
        "Filósofos para quienes la única fuente del conocimiento es la razón.",
        {"Epistemólogos", "Racionalistas", "Empiristas", "Escépticos"},
        1
    });

    batallaQueue.enqueue({
        "Filósofos que postulan las ideas innatas en el sujeto.",
        {"Empiristas", "Idealistas", "Racionalistas", "Innatistas"},
        2
    });

    batallaQueue.enqueue({
        "De los siguientes filósofos seleccione el que no se considera Racionalista:",
        {"David Hume", "John Locke", "Nicolas Malebranch", "Francis Bacon"},
        2
    });

    batallaQueue.enqueue({
        "Es la doctrina que establece que todos nuestros conocimientos provienen de la razón.",
        {"Empirismo", "Criticismo", "Racionalismo", "Epistemología"},
        2
    });

    batallaQueue.enqueue({
        "Uno de los siguientes filósofos postula las ideas innatas en el sujeto:",
        {"George Berkeley", "David Hume", "Leibniz", "Hipatía"},
        2
    });
}

void cuestionario::insertarKant()
{
    KantQueue.enqueue({
        "Seleccione el mandato cuya obligación viene del miedo al castigo o la búsqueda de un premio:",
        {"Imperativo Hipotético", "Imperativo categórico", "Ambos", "Ninguno"},
        0
    });

    KantQueue.enqueue({
        "Para Emanuel Kant, es posible conocer lo que las cosas nos permiten (como lo superficial) a través de nuestros sentidos:",
        {"Conocimiento Noumenico", "Conocimiento fenoménico", "Conocimiento Empírico", "Conocimiento Racional"},
        1
    });

    KantQueue.enqueue({
        "Kant decía que el lema de la ilustración era “Sapere aude”, que significa:",
        {"Sopesa tus acciones", "Atrévete a saber por ti mismo", "Saber a la fuerza", "Someterse al conocimiento"},
        1
    });

    KantQueue.enqueue({
        "Kant (igual que Copérnico cambió el centro del universo de la tierra al sol), cambia el centro del conocimiento del objeto al sujeto, a esto se le llama:",
        {"Subjetivismo", "Prejuicio", "Giro copernicano", "Suerte"},
        2
    });

    KantQueue.enqueue({
        "La postura conciliadora de Kant respecto a los empiristas y racionalistas define que los datos experimentales son la fuente del conocimiento racional del sujeto:",
        {"Racionalismo", "Empirismo", "Criticismo", "Escepticismo"},
        2
    });

    KantQueue.enqueue({
        "De las siguientes obras de Emanuel Kant, seleccione aquella que define su epistemología:",
        {"Crítica de la razón práctica", "Crítica de la razón pura", "Crítica del juicio", "Crítica fenomenológica"},
        1
    });
}

void cuestionario::insertarDescartes()
{
    DescartesQueue.enqueue({
        "Los pasos o razones de la duda metódica:",
        {"Los sentidos nos engañan", "La existencia del genio maligno", "Imposibilidad para diferenciar la vigilia del sueño", "Todas son correctas"},
        3
    });

    DescartesQueue.enqueue({
        "Una de las siguientes es considerada una de las cuatro reglas del método en Descartes:",
        {"Hipótesis", "Deducción", "Evidencia", "Inducción"},
        2
    });

    DescartesQueue.enqueue({
        "En relación con los datos experimentales que otorgan los sentidos en el conocimiento, Descartes define:",
        {"Los sentidos son una fuente confiable para conocer", "Desconfianza de lo que los sentidos nos proporcionan", "Los sentidos son complementarios", "Los sentidos son determinantes"},
        1
    });

    DescartesQueue.enqueue({
        "Solo debemos aceptar como verdadero aquel conocimiento que sea EVIDENTE, CLARO Y DISTINTO:",
        {"René Descartes", "David Hume", "George Berkeley", "Aristóteles"},
        0
    });

    DescartesQueue.enqueue({
        "En cuanto a la certeza del conocimiento, René Descartes afirma lo siguiente:",
        {"Es preciso dudar", "Debemos confiar ciegamente", "Nada es importante", "Todo es posible"},
        0
    });
}


// ==================== NAVEGACIÓN ====================
// void cuestionario::siguientePregunta(QQueue<Preguntas>& cola) {
//     if (!cola.isEmpty()) {
//         Preguntas p = cola.head();
//         cout << p.pregunta.toStdString() << endl;
//         for (int i = 0; i < p.opciones.size(); ++i)
//             cout << "   " << char('A' + i) << ") " << p.opciones[i].toStdString() << endl;
//     } else {
//         cout << "No hay más preguntas.\n";
//     }
// }

void cuestionario::quitarPregunta(QQueue<Preguntas>& cola) {
     if (!cola.isEmpty()) cola.dequeue();
}
