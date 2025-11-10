#include "kant_class.h"
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QMessageBox>

Kant_class::Kant_class(QGraphicsScene* scene){
    this->scene = scene;
    kantP = new cuestionario();
    kantP->insertarKant();

    walls(scene);
    loadHints(scene);
    loadKant(scene);
}

void Kant_class::walls(QGraphicsScene *scene)
{
    QGraphicsRectItem* wall_center = new QGraphicsRectItem(0, 0, 1000, 305);
    wall_center->setPos(0, -100);
    wall_center->setBrush(Qt::NoBrush);
    wall_center->setPen(Qt::NoPen);
    wall_center->setData(0,"wall");

    scene->addItem(wall_center);

    QGraphicsRectItem* wall_bottom = new QGraphicsRectItem(0, 0, 300, 250);
    wall_bottom->setPos(100, 474);
    wall_bottom->setBrush(Qt::NoBrush);
    wall_bottom->setPen(Qt::NoPen);
    wall_bottom->setData(0,"wall");

    scene->addItem(wall_bottom);

    //kant miniwall
    QGraphicsRectItem* kant_wall = new QGraphicsRectItem(0, 0, 1, 1);
    kant_wall->setPos(960, 508);
    kant_wall->setBrush(Qt::yellow);
    kant_wall->setPen(Qt::NoPen);
    kant_wall->setData(0,"wall");

    scene->addItem(kant_wall);
}

void Kant_class::loadHints(QGraphicsScene *scene)
{
    // === Book 1 - Imperativo Hipotético ===
    object1 = scene->addRect(44, 244, 50, 20, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    object1->setData(0, "object");
    object1->setData(3, 0); // imperativo hipotético

    auto label1 = scene->addText("Press E to investigate");
    label1->setDefaultTextColor(Qt::white);
    label1->setZValue(10);
    label1->setVisible(false);
    object1->setData(1, QVariant::fromValue<void*>(label1));

    // === Book 2 - Epistemología ===
    object2 = scene->addRect(248, 244, 50, 20, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    object2->setData(0, "object");
    object2->setData(3, 5); // crítica de la razón pura (epistemología)

    auto label2 = scene->addText("Press E to investigate!");
    label2->setDefaultTextColor(Qt::white);
    label2->setZValue(10);
    label2->setVisible(false);
    object2->setData(1, QVariant::fromValue<void*>(label2));

    // === Pizarra - Sapere aude ===
    object3 = scene->addRect(720, 244, 50, 20, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    object3->setData(0, "object");
    object3->setData(3, 2); // lema de la ilustración

    auto label3 = scene->addText("Press E to investigate!");
    label3->setDefaultTextColor(Qt::white);
    label3->setZValue(10);
    label3->setVisible(false);
    object3->setData(1, QVariant::fromValue<void*>(label3));

    // === Sistema Solar - Giro Copernicano ===
    object4 = scene->addRect(472, 244, 50, 20, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    object4->setData(0, "object");
    object4->setData(3, 3); // giro copernicano

    auto label4 = scene->addText("Press E to investigate!");
    label4->setDefaultTextColor(Qt::white);
    label4->setZValue(10);
    label4->setVisible(false);
    object4->setData(1, QVariant::fromValue<void*>(label4));

    // === Planta - Criticismo ===
    object5 = scene->addRect(396, 500, 50, 20, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    object5->setData(0, "object");
    object5->setData(3, 4); // criticismo

    auto label5 = scene->addText("Press E to investigate!");
    label5->setDefaultTextColor(Qt::white);
    label5->setZValue(10);
    label5->setVisible(false);
    object5->setData(1, QVariant::fromValue<void*>(label5));

    // === Extra object - Fenoménico (sentidos) ===
    object6 = scene->addRect(64, 450, 50, 20, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    object6->setData(0, "object");
    object6->setData(3, 1); // conocimiento fenoménico

    auto label6 = scene->addText("Press E to investigate!");
    label6->setDefaultTextColor(Qt::white);
    label6->setZValue(10);
    label6->setVisible(false);
    object6->setData(1, QVariant::fromValue<void*>(label6));
}

void Kant_class::loadMesssages(int hint)
{
    if (hint < 0 || hint >= totalHints) return;

    // Only mark this hint if not collected yet
    QString message;

    switch (hint) {
    case 0:
        message = "Imperativos Hipopeticos, los que dependen de una condición (premio o castigo).";
        break;
    case 1:
        message = "Conocimiento Fenomenico, lo que percibimos a través de los sentidos.";
        break;
    case 2:
        message = "Sapere Aude!‘Atrévete a saber por ti mismo’, lema de la Ilustración.";
        break;
    case 3:
        message = "Así como Copérnico cambió el centro del universo, Kant cambió el del conocimiento: es el giro copernicano.";
        break;
    case 4:
        message = "Criticismo, la unión entre empirismo y racionalismo.";
        break;
    case 5:
        message = "Solo dos libros pueden abrirse: ‘Crítica de la razon pura’ y ‘Crítica de la razon practica’.\n"
                  "El primero habla del Conocimiento, es decir, de la epistemología.";
        break;
    default:
        message = "No hay pista disponible.";
        break;
    }

    QMessageBox msgBox;
    msgBox.setWindowTitle("💡 Hint encontrado");
    msgBox.setText(message);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();

    if (!hintsCollected[hint]) {
        hintsCollected[hint] = true;
        hintsFound++;

        // Update hints counter on screen
        if (!hintsCounter) {
            hintsCounter = new QGraphicsTextItem();
            hintsCounter->setDefaultTextColor(Qt::black);
            hintsCounter->setFont(QFont("Segoe UI", 16, QFont::Bold));
            hintsCounter->setPos(10, 10); // top-left corner
            hintsCounter->setZValue(50);
            scene->addItem(hintsCounter);
        }
        hintsCounter->setPlainText(QString("Pistas: %1/%2").arg(hintsFound).arg(totalHints));

        qDebug() << "Hint found:" << hintsFound << "/" << totalHints;

        if (hintsFound >= totalHints) {
            allHintsFound = true;
            QMessageBox::information(nullptr, "✅ Todas las pistas encontradas",
                                     "Has encontrado todas las pistas. ¡Habla con Kant para resolver el caso!");
        }
    }
}

void Kant_class::loadKant(QGraphicsScene *scene)
{
    npcKant = new Npcs();
    npcKant->ChangeToKantDesc("Kant");
    npcKant->setPos(924,500);

    scene->addItem(npcKant);

    //load itemTalk 924,500
    KantTrigger = scene->addRect(924,500, 50, 20, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    KantTrigger->setData(0, "npc");
    KantTrigger->setData(4, 0); // conocimiento fenoménico

    auto KantTrigger_lb = scene->addText("Press E to to talk to Kant!");
    KantTrigger_lb->setDefaultTextColor(Qt::white);
    KantTrigger_lb->setZValue(10);
    KantTrigger_lb->setVisible(false);
    KantTrigger->setData(1, QVariant::fromValue<void*>(KantTrigger_lb));
}

void Kant_class::loadQuestions(QGraphicsScene* scene)
{
    if (!scene) return; // defensive

    // Remove previous question text
    if (question) {
        scene->removeItem(question);
        delete question;
        question = nullptr;
    }

    // Get next question
    if (kantP->KantQueue.isEmpty()) return;
    currentQuestion = kantP->KantQueue.head();

    // Background panel
    QGraphicsRectItem* background = new QGraphicsRectItem(0, 0, 420, 180);
    background->setPos(320, 40);
    background->setBrush(QColor(50, 50, 80, 220));
    background->setPen(QPen(QColor(200, 200, 220), 3));
    background->setZValue(10);
    scene->addItem(background);

    // Question text
    question = new QGraphicsTextItem();
    QString html = QString(
                       "<div style='font-family:\"Segoe UI\"; font-size:12pt; color:#FFD700; font-weight:bold;'>%1</div>"
                       "<div style='font-family:\"Segoe UI\"; font-size:10pt; color:white; margin-top:5px;'>"
                       "1) %2<br>2) %3<br>3) %4<br>4) %5</div>")
                       .arg(currentQuestion.pregunta,
                            currentQuestion.opciones[0],
                            currentQuestion.opciones[1],
                            currentQuestion.opciones[2],
                            currentQuestion.opciones[3]);
    question->setHtml(html);
    question->setTextWidth(400);
    question->setPos(330, 50);
    question->setZValue(20);
    scene->addItem(question);

    // Create buttons as QWidget children of viewport
    if (!scene->views().isEmpty() && scene->views().first()) {
        QWidget* viewport = scene->views().first()->viewport();

        optionButtons.resize(4);
        int x = 340, y = 260;

        for (int i = 0; i < 4; ++i) {
            QPushButton* btn = new QPushButton(currentQuestion.opciones[i], viewport);
            btn->setGeometry(x, y + i * 40, 380, 30);
            btn->setStyleSheet(
                "background-color:#333;"
                "color:white;"
                "border:1px solid #AAA;"
                "border-radius:6px;"
                );
            btn->show();

            connect(btn, &QPushButton::clicked, [this, i]() {
                checkKantAnswer(i);
            });

            optionButtons[i] = btn;
        }
    }
}


void Kant_class::onKantTalk()
{
    if (!allHintsFound) {
        QMessageBox::information(nullptr, "🔒 Pistas incompletas",
                                 "Aún no has encontrado todas las pistas. Busca más antes de hablar con Kant.");
        return;
    }

    if (!kantTalked) {
        kantTalked = true;
        QMessageBox::information(nullptr, "🧠 Kant",
                                 "Has reunido todas las pistas. Kant te hará algunas preguntas...");
        loadQuestions(scene);
    }
}

void Kant_class::checkKantAnswer(int index)
{
    if (kantP->KantQueue.isEmpty()) return;

    auto current = kantP->KantQueue.head();

    if (index == current.opcionCorrecta) {
        correctAnswers++;
        showTemporaryMessage(":/Deco/arte_correcto.jpg");
    } else {
        showTemporaryMessage(":/Deco/arte_incorrecto.jpg");
    }

    kantP->KantQueue.dequeue();

    // // Remove current question and buttons
    // if (question) {
    //     scene->removeItem(question);
    //     delete question;
    //     question = nullptr;
    // }
    // for (auto btn : {option1, option2, option3, option4}) {
    //     scene->removeItem(scene->itemAt(btn->pos(), QTransform()));
    //     delete btn;
    // }

    for (QPushButton* btn : optionButtons) {
        if (btn) {
            btn->hide();
            btn->setParent(nullptr);
            delete btn;
        }
    }

    optionButtons.clear();

    if (kantP->KantQueue.isEmpty()) {
        // Show final result
        QString finalMsg = QString("🎓 Cuestionario terminado!\nRespuestas correctas: %1/%2")
                               .arg(correctAnswers)
                               .arg(totalHints);
        QMessageBox::information(nullptr, "Resultado final", finalMsg);
        kantDone = true;
        minigameFinished();
        return;
    }

    loadQuestions(scene);
}

void Kant_class::showTemporaryMessage(const QString& imagePath) {
    QGraphicsPixmapItem* img = new QGraphicsPixmapItem(QPixmap(imagePath));
    img->setScale(0.4);
    img->setPos(420, 220);
    img->setZValue(9999);
    scene->addItem(img);

    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect;
    img->setGraphicsEffect(effect);

    QPropertyAnimation* anim = new QPropertyAnimation(effect, "opacity");
    anim->setDuration(2000); anim->setStartValue(1.0);
    anim->setEndValue(0.0);

    QObject::connect(anim, &QPropertyAnimation::finished, [this, img, effect]() {
        scene->removeItem(img); delete effect; delete img; });
        anim->start(QAbstractAnimation::DeleteWhenStopped);
}
