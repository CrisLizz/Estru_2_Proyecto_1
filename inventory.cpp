#include "inventory.h"
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QPen>
#include <QGraphicsOpacityEffect>
#include <QBrush>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <QLabel>
#include <QTimer>

#include <QTabWidget>
#include <QListWidget>
#include "player.h"

// Inside Inventory constructor, after setting up the scene
Inventory::Inventory(QWidget *parent)
    : QWidget(parent)
{
    // --- Graph scene setup (your existing code) ---
    m_scene = new QGraphicsScene(this);
    QGraphicsView* view = new QGraphicsView(m_scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setFixedSize(720, 440);
    m_scene->setSceneRect(0, 0, 700, 400);

    view->setStyleSheet(
        "QGraphicsView { "
        "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, "
        "stop:0 #2b2b2b, stop:1 #3c3f41); "
        "border-radius: 15px; "
        "border: 2px solid #555; }"
        );

    // --- Tabs ---
    QTabWidget* tabs = new QTabWidget(this);

    // Tab 1: Graph
    QWidget* graphTab = new QWidget();
    QVBoxLayout* graphLayout = new QVBoxLayout(graphTab);
    graphLayout->addWidget(view);
    graphTab->setLayout(graphLayout);

    // Tab 2: Leaderboard
    leaderboardWidget = new QWidget();
    QVBoxLayout* leaderboardLayout = new QVBoxLayout(leaderboardWidget);
    leaderboardList = new QListWidget();

    // --- Inside constructor, after creating leaderboardList ---
    leaderboardList->setStyleSheet(
        "QListWidget {"
        " background-color: #2b2b2b;"
        " border-radius: 10px;"
        " padding: 5px;"
        " color: white;"
        " font-family: 'Segoe UI';"
        " font-size: 16px;"
        "}"
        "QListWidget::item {"
        " padding: 8px;"
        " border-bottom: 1px solid #444;"
        "}"
        "QListWidget::item:selected {"
        " background-color: #3c8dbc;"
        " color: white;"
        " border-radius: 5px;"
        "}"
        );

    // Optional: alternating row colors
    leaderboardList->setAlternatingRowColors(true);
    leaderboardList->setAlternatingRowColors(true);
    QPalette p = leaderboardList->palette();
    p.setColor(QPalette::AlternateBase, QColor("#3a3a3a"));
    leaderboardList->setPalette(p);


    leaderboardLayout->addWidget(leaderboardList);
    leaderboardWidget->setLayout(leaderboardLayout);


    QWidget* imageTab = new QWidget();
    QVBoxLayout* imageLayout = new QVBoxLayout(imageTab);
    QLabel* imageLabel = new QLabel();
    imageLabel->setPixmap(QPixmap(":/Fondos/Mapa.png").scaled(700, 400, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLayout->addWidget(imageLabel);
    imageTab->setLayout(imageLayout);

    // Tab 3: Achievements / Logros
    QWidget* logrosTab = new QWidget();
    QVBoxLayout* logrosLayout = new QVBoxLayout(logrosTab);

    // This will hold each logro
    logrosContainer = new QWidget();
    QVBoxLayout* containerLayout = new QVBoxLayout(logrosContainer);
    logrosContainer->setLayout(containerLayout);

    QScrollArea* scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setWidget(logrosContainer);

    logrosLayout->addWidget(scroll);
    logrosTab->setLayout(logrosLayout);

    // Add tabs
    tabs->addTab(logrosTab, "Logros");
    tabs->addTab(graphTab, "Mapa del Conocimiento");
    tabs->addTab(leaderboardWidget, "Leaderboard");
    tabs->addTab(imageTab, "Mapa");

    // --- Main layout ---
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(tabs);
    setLayout(mainLayout);

    configurarGrafoPorDefecto();
    dibujarGrafo();

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Inventory::mostrarLeaderboard);
    timer->start(1000);
}

void Inventory::mostrarLogros()
{
    QVBoxLayout* vLayout = qobject_cast<QVBoxLayout*>(logrosContainer->layout());
    if (!vLayout) return;

    // Clear previous items
    QLayoutItem* child;
    while ((child = vLayout->takeAt(0)) != nullptr) {
        if (child->widget()) child->widget()->deleteLater();
        delete child;
    }

    // Header
    QLabel* header = new QLabel("---- Logros ----");
    QFont headerFont("Segoe UI", 18, QFont::Bold);
    header->setFont(headerFont);
    header->setStyleSheet("color: #FFD700;"); // golden color
    header->setAlignment(Qt::AlignCenter);
    vLayout->addWidget(header);
    vLayout->addSpacing(10);

    for (Nodo* n : m_nodos) {
        if (n->completado) {
            QWidget* logroWidget = new QWidget();
            QHBoxLayout* hLayout = new QHBoxLayout(logroWidget);
            hLayout->setContentsMargins(10, 5, 10, 5);
            hLayout->setSpacing(15);

            QLabel* imgLabel = new QLabel();
            QString text;

            // Custom text & images for Empirista and Racionalista
            if (n->nombre == "Empirista") {
                text = "Escogió Empirista";
                imgLabel->setPixmap(QPixmap(":/Deco/emp_banner.png").scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            }
            else if (n->nombre == "Racionalista") {
                text = "Escogió Racionalista";
                imgLabel->setPixmap(QPixmap(":/Deco/rac_banner.png").scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            }
            else {
                text = QString("Aprobó %1").arg(n->nombre);
                imgLabel->setPixmap(QPixmap(":/Deco/trophy.png").scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            }

            hLayout->addWidget(imgLabel);

            QLabel* textLabel = new QLabel(text);
            QFont font("Segoe UI", 14, QFont::Bold);
            textLabel->setFont(font);
            textLabel->setStyleSheet("color: white;");
            hLayout->addWidget(textLabel);

            hLayout->addStretch();

            QVBoxLayout* wrapperLayout = new QVBoxLayout();
            wrapperLayout->setContentsMargins(0,0,0,0);
            wrapperLayout->addLayout(hLayout);

            QFrame* line = new QFrame();
            line->setFrameShape(QFrame::HLine);
            line->setFrameShadow(QFrame::Sunken);
            line->setStyleSheet("color: #555555;");
            wrapperLayout->addWidget(line);

            logroWidget->setLayout(wrapperLayout);
            vLayout->addWidget(logroWidget);
        }
    }

    vLayout->addStretch();
}


void Inventory::mostrarLeaderboard()
{
    QList<Player> players = Player().loadPlayers("players.json");

    //ordenamiento
    int n = players.size();
    for (int i = 0; i < n - 1; ++i) {
        int maxIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (players[j].score > players[maxIdx].score)
                maxIdx = j;
        }
        if (maxIdx != i)
            std::swap(players[i], players[maxIdx]);
    }

    leaderboardList->clear();

    // Header
    QListWidgetItem* header = new QListWidgetItem("--- Leaderboard ---");
    header->setTextAlignment(Qt::AlignCenter);
    QFont headerFont("Segoe UI", 18, QFont::Bold);
    header->setFont(headerFont);
    header->setFlags(Qt::NoItemFlags);
    leaderboardList->addItem(header);

    QFont playerFont("Segoe UI", 14);
    for (int i = 0; i < qMin(players.size(), 20); ++i) {
        QString line = QString("%1. %2 : %3 pts").arg(i + 1).arg(players[i].name).arg(players[i].score);
        QListWidgetItem* item = new QListWidgetItem(line);
        item->setFont(playerFont);
        leaderboardList->addItem(item);
    }
}

void Inventory::configurarGrafoPorDefecto()
{

    Nodo* ruleta = new Nodo("Ruleta", QPointF(320, 40));
    m_nodos.append(ruleta);

    Nodo* arte = new Nodo("Arte", QPointF(140, 130));
    Nodo* politica = new Nodo("Politica", QPointF(260, 130));
    Nodo* historia = new Nodo("Historia", QPointF(380, 130));
    Nodo* ciencia = new Nodo("Ciencia", QPointF(500, 130));
    m_nodos << arte << politica << historia << ciencia;

    Nodo* intermedio1 = new Nodo("Intermedio", QPointF(320, 190));
    m_nodos.append(intermedio1);

    Nodo* empirista = new Nodo("Empirista", QPointF(240, 260));
    Nodo* racionalista = new Nodo("Racionalista", QPointF(400, 260));
    m_nodos << empirista << racionalista;

    Nodo* intermedio2 = new Nodo("Intermedio", QPointF(320, 310));
    m_nodos.append(intermedio2);

    Nodo* descartes = new Nodo("Descartes", QPointF(260, 360));
    Nodo* kant = new Nodo("Kant", QPointF(380, 360));
    m_nodos << descartes << kant;

    m_aristas.append(new Arista(ruleta, arte));
    m_aristas.append(new Arista(ruleta, politica));
    m_aristas.append(new Arista(ruleta, historia));
    m_aristas.append(new Arista(ruleta, ciencia));

    for (Nodo* n : {arte, politica, historia, ciencia})
        m_aristas.append(new Arista(n, intermedio1));

    m_aristas.append(new Arista(intermedio1, empirista));
    m_aristas.append(new Arista(intermedio1, racionalista));

    m_aristas.append(new Arista(empirista, intermedio2));
    m_aristas.append(new Arista(racionalista, intermedio2));

    m_aristas.append(new Arista(intermedio2, descartes));
    m_aristas.append(new Arista(intermedio2, kant));

    ruleta->disponible = true;
}

void Inventory::dibujarGrafo()
{
    m_scene->clear();

    // --- Background image ---
    QGraphicsPixmapItem* bg = new QGraphicsPixmapItem(
        QPixmap(":/Fondos/school_Front.jpg")
            .scaled(700, 400, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation)
        );
    bg->setZValue(-10);
    m_scene->addItem(bg);

    // --- Semi-transparent overlay (for readability) ---
    QGraphicsRectItem* overlay = new QGraphicsRectItem(0, 0, 700, 400);
    overlay->setBrush(QColor(0, 0, 0, 120));
    overlay->setPen(Qt::NoPen);
    overlay->setZValue(-5);
    m_scene->addItem(overlay);

    m_nodoItems.clear();
    m_labelItems.clear();
    m_aristaBaseItems.clear();
    m_aristaOverlayItems.clear();

    QPen penBase(QColor(150, 150, 150));
    penBase.setWidth(1.8);
    penBase.setCapStyle(Qt::RoundCap);

    for (Arista* a : m_aristas) {
        QPointF p1 = a->origen->posicion + QPointF(20, 20);
        QPointF p2 = a->destino->posicion + QPointF(20, 20);

        QGraphicsLineItem* line = new QGraphicsLineItem(QLineF(p1, p2));
        line->setPen(penBase);
        line->setZValue(0);
        m_scene->addItem(line);
        m_aristaBaseItems[a] = line;

        QPen penOverlay(QColor(0, 220, 130));
        penOverlay.setWidth(3);
        penOverlay.setCapStyle(Qt::RoundCap);

        QGraphicsLineItem* overlay = new QGraphicsLineItem(QLineF(p1, p2));
        overlay->setPen(penOverlay);
        overlay->setOpacity(a->desbloqueada ? 1.0 : 0.0);
        overlay->setZValue(1);
        m_scene->addItem(overlay);
        m_aristaOverlayItems[a] = overlay;
    }

    QFont labelFont("Segoe UI", 8, QFont::Medium);

    for (Nodo* n : m_nodos) {
        QRectF r(n->posicion.x(), n->posicion.y(), 40, 40);
        QGraphicsEllipseItem* circle = new QGraphicsEllipseItem(r);
        circle->setPen(QPen(Qt::black, 1.2));
        circle->setBrush(QColor("#aaaaaa"));
        circle->setZValue(2);

        QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect();
        shadow->setBlurRadius(12);
        shadow->setOffset(2, 3);
        shadow->setColor(QColor(0, 0, 0, 100));
        circle->setGraphicsEffect(shadow);

        m_scene->addItem(circle);
        m_nodoItems[n] = circle;
        QGraphicsTextItem* label = new QGraphicsTextItem(n->nombre);

        // make it bold, readable, and on top
        QFont labelFont("Segoe UI", 11, QFont::Bold);
        label->setFont(labelFont);
        label->setDefaultTextColor(Qt::white);
        label->setPos(n->posicion.x() - 15, n->posicion.y() - 28); // move above node
        label->setZValue(3);

        // subtle shadow for contrast
        QGraphicsDropShadowEffect* textShadow = new QGraphicsDropShadowEffect();
        textShadow->setBlurRadius(6);
        textShadow->setOffset(1, 1);
        textShadow->setColor(QColor(0, 0, 0, 160));
        label->setGraphicsEffect(textShadow);

        m_scene->addItem(label);
        m_labelItems[n] = label;

    }

    for (Nodo* n : m_nodos)
        actualizarVisualNodo(n);
}

void Inventory::actualizarVisualNodo(Nodo* nodo)
{
    if (!m_nodoItems.contains(nodo)) return;
    QGraphicsEllipseItem* circle = m_nodoItems[nodo];

    QColor color;
    if (nodo->completado)
        color = QColor("#4CAF50");
    else if (nodo->disponible)
        color = QColor("#FFD54F");
    else
        color = QColor("#666666");

    circle->setBrush(QBrush(color));
    circle->setPen(QPen(Qt::black, 1.3));
}

Nodo* Inventory::buscarNodo(const QString &nombre)
{
    for (Nodo* n : m_nodos)
        if (n->nombre == nombre)
            return n;
    return nullptr;
}

void Inventory::desbloquearAristasSalientes(Nodo* nodo)
{
    for (Arista* a : m_aristas) {
        if (a->origen == nodo && !a->desbloqueada) {
            a->desbloqueada = true;

            QGraphicsLineItem* overlay = m_aristaOverlayItems.value(a, nullptr);
            if (!overlay) continue;

            QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect();
            overlay->setGraphicsEffect(effect);
            effect->setOpacity(0.0);

            QPropertyAnimation* anim = new QPropertyAnimation(effect, "opacity", this);
            anim->setDuration(800);
            anim->setStartValue(0.0);
            anim->setEndValue(1.0);
            anim->setEasingCurve(QEasingCurve::OutCubic);
            anim->start(QAbstractAnimation::DeleteWhenStopped);
            m_animaciones.append(anim);

            if (!a->destino->completado) {
                a->destino->disponible = true;
                actualizarVisualNodo(a->destino);
            }
        }
    }
}
void Inventory::completarNodo(const QString &nombre)
{
    Nodo* nodo = buscarNodo(nombre);
    if (!nodo) return;

    nodo->completado = true;
    nodo->disponible = false;
    actualizarVisualNodo(nodo);

    // 🔹 Highlight edges connected FROM this node
    for (Arista* a : m_aristas) {
        if (a->origen == nodo) {
            QGraphicsLineItem* overlay = m_aristaOverlayItems.value(a, nullptr);
            if (overlay) {
                overlay->setOpacity(1.0);
            }
        }
    }

    // 🔹 Also highlight the edge that leads TO this node
    for (Arista* a : m_aristas) {
        if (a->destino == nodo) {
            QGraphicsLineItem* overlay = m_aristaOverlayItems.value(a, nullptr);
            if (overlay) {
                overlay->setOpacity(1.0);
            }
        }
    }

    desbloquearAristasSalientes(nodo);
    mostrarLogros(); // <-- update achievements tab
}
