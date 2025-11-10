#include "batalla.h"
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QRandomGenerator>
#include <QDebug>
#include <QMessageBox>

Batalla::Batalla(QGraphicsScene* scene, bool team, Protagonista* protag)
{
    m_scene = scene;
    protagonista = protag;
    battle = new cuestionario();
    battle->insertarBatalla();

    player = new QMediaPlayer(this);
    this->audio = new QAudioOutput(this); // new QAudioOutput
    player->setAudioOutput(audio);
    audio->setVolume(0.5); // 0.0 to 1.0

    loadNpc(team);

    playerTurn = true;
    loadQuestion();
}

// ================= WALL =================
void Batalla::wall(QGraphicsScene* scene)
{
    QGraphicsRectItem* wall_center = new QGraphicsRectItem(0, 0, 1000, 305);
    wall_center->setPos(0, -100);
    wall_center->setBrush(Qt::NoBrush);
    wall_center->setPen(Qt::NoPen);
    wall_center->setData(0, "wall");
    scene->addItem(wall_center);
}

// ================= LOAD QUESTION =================
void Batalla::loadQuestion()
{
    // --- Remove previous question items ---
    if (question) {
        m_scene->removeItem(question);
        delete question;
        question = nullptr;
    }

    if (battleEnded) {
        qDebug() << "⚠️ Tried to load question after battle ended — ignored.";
        return;
    }

    // --- Load next question if battle is not over ---
    currentQuestion = battle->batallaQueue.head();

    QGraphicsRectItem* background = new QGraphicsRectItem(0, 0, 420, 180);
    background->setPos(320, 90);
    background->setBrush(QColor(50, 50, 80, 220));
    background->setPen(QPen(QColor(200, 200, 220), 3));
    background->setZValue(10);
    m_scene->addItem(background);

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
    question->setTextWidth(400);  // keep text inside box
    question->setPos(330, 100);
    question->setZValue(20);
    m_scene->addItem(question);

    npcAnswer();
}

void Batalla::answerQuestion(bool isPlayer, int choice)
{
    if (battleEnded || !playerTurn || battle->batallaQueue.isEmpty()) return;

    playerTurn = false; // block further input

    bool correct = (choice == currentQuestion.opcionCorrecta);

    if (isPlayer) {
        if (correct)
            showStyledMessage("Correcto!", "Respuesta Correcta!", "");
        else
            showStyledMessage("Incorrecto!", "Respuesta Incorrecta!", "");
    } else {
        if (correct)
            showStyledMessage("Correcto!", "Npc dio la Respuesta Correcta!", "");
        else
            showStyledMessage("Incorrecto!", "Npc dio la Respuesta Incorrecta!", "");
    }

    if (correct)
        attack(isPlayer, true);

    int delay = correct ? 3000 : 800; // wait for attack animation if correct

    QTimer::singleShot(delay, [this]() {
        removeCurrentQuestion();

        // ✅ Check if battle ended
        if (!battleEnded &&
            protagonista->getLifes() > 0 &&
            npc->getLifes() > 0 &&
            !battle->batallaQueue.isEmpty())
        {
            playerTurn = true;
            loadQuestion();
        }else{
            dead();
        }

    });
}

// Player answers
void Batalla::chooseAnswer(int key)
{
    if (!playerTurn || battle->batallaQueue.isEmpty()) return;

    answerQuestion(true, key); // Player answered
}


// NPC auto-answer
void Batalla::npcAnswer()
{
    qDebug() << "npc is going to answer the question...";
    if (!playerTurn || battle->batallaQueue.isEmpty()) return;

    int delay = QRandomGenerator::global()->bounded(1500, 4000);
    QTimer::singleShot(delay, [this]() {
        if (!playerTurn || battle->batallaQueue.isEmpty()) return;

        int npcChoice = QRandomGenerator::global()->bounded(1, 5); // random choice
        answerQuestion(false, npcChoice);
        qDebug() << "npc answered the question...";

    });
}

// Remove question after both turns
void Batalla::removeCurrentQuestion() {
    if (!battle->batallaQueue.isEmpty())
        battle->quitarPregunta(battle->batallaQueue);

    if (question) {
        m_scene->removeItem(question);
        delete question;
        question = nullptr;
    }
}

// ================= ATTACK =================
void Batalla::attack(bool isPlayer, bool hit)
{
    if (battleEnded || !hit) return;

    // Prevent overlapping attacks
    static bool isAttacking = false;
    if (isAttacking) return;
    isAttacking = true;

    if (isPlayer) {
        if (!protagonista || !npc) { isAttacking = false; return; }

        QPointF startPos = protagonista->pos();
        protagonista->velocidadX = 10;
        protagonista->sprite = protagonista->walkDerecha;

        // Step 1: Move forward
        QTimer::singleShot(1000, this, [=, this]() mutable {
            if (battleEnded) { isAttacking = false; return; }

            protagonista->velocidadX = 0;
            protagonista->attack();

            npc->takeLifes();
            bool npcDied = npc->getLifes() <= 0;

            if (npcDied) {
                npc->setPos(584, 438);
                npc->death();
                this->dead();
                isAttacking = false;
                return;
            }

            // Step 2: Wait for attack animation, then retreat
            QTimer::singleShot(500, this, [=, this]() mutable {
                if (battleEnded) { isAttacking = false; return; }

                protagonista->velocidadX = -10;
                protagonista->sprite = protagonista->walkIzq;

                // Step 3: Return to start
                QTimer::singleShot(1000, this, [=, this]() mutable {
                    protagonista->velocidadX = 0;
                    protagonista->Detener();
                    protagonista->setPos(startPos);
                    isAttacking = false;
                });
            });
        });
    }

    else { // NPC attack
        if (!npc || !protagonista) { isAttacking = false; return; }

        QPointF startPos = npc->pos();
        npc->velocidadX = -10;
        npc->sprite = npc->walkIzq;

        // Step 1: Move forward
        QTimer::singleShot(1000, this, [=, this]() mutable {
            if (battleEnded) { isAttacking = false; return; }

            npc->velocidadX = 0;
            npc->attack();

            protagonista->takeLifes();
            bool playerDied = protagonista->getLifes() <= 0;

            if (playerDied) {
                protagonista->setPos(440, 438);
                protagonista->death();
                this->dead();
                isAttacking = false;
                return;
            }

            // Step 2: Wait for attack animation, then retreat
            QTimer::singleShot(500, this, [=, this]() mutable {
                if (battleEnded) { isAttacking = false; return; }

                npc->velocidadX = 10;
                npc->sprite = npc->walkDerecha;

                // Step 3: Return to start
                QTimer::singleShot(1000, this, [=, this]() mutable {
                    npc->velocidadX = 0;
                    npc->Detener();
                    npc->setPos(startPos);
                    isAttacking = false;
                });
            });
        });
    }
}


// ================= CHECK DEATH =================
void Batalla::dead()
{
    if (battleEnded) return; // already ended

    // Check if battle ended due to questions
    if (battle->batallaQueue.isEmpty() ||
        protagonista->getLifes() <= 0 ||
        npc->getLifes() <= 0)
    {
        battleEnded = true;

        // Stop any movement/animations
        if (!battle->batallaQueue.isEmpty()){
            loadQuestion();
        }
        protagonista->showHeartsAbove = false;

        // Determine winner
        if (protagonista->getLifes() == npc->getLifes()) {
            Empate();
        } else if (protagonista->getLifes() <= 0) {
            if (protagonista->empirista) GanoRacionalista();
            else GanoEmpirista();
        } else if (npc->getLifes() <= 0) {
            if (protagonista->empirista) GanoEmpirista();
            else GanoRacionalista();
        } else {
            // Questions ran out, compare lives
            if (protagonista->getLifes() > npc->getLifes()) {
                qDebug() << "entered run out";
                if (protagonista->empirista) GanoEmpirista();
                else GanoRacionalista();

            } else if (npc->getLifes() > protagonista->getLifes()) {
                if (protagonista->empirista) GanoRacionalista();
                else GanoEmpirista();
            } else {
                Empate();
            }
        }
    }
}
void Batalla::GanoRacionalista()
{
    cantMove = false; // block movement initially
    playWinnerMusic("qrc:/Winners_Music/Oh_Fortuna_Carmina.mp3");

    QTimer::singleShot(500, [this]() {
        QMessageBox msgBox;
        msgBox.setIconPixmap(QPixmap(":/Icons/racionalista_icon.png").scaled(48,48));

        // Si el jugador perdió (menos vidas que el NPC)
        if (protagonista->getLifes() < npc->getLifes()) {
            msgBox.setWindowTitle("Derrota...");
            msgBox.setText("El Racionalista gano...\n");
            QAbstractButton* btnLobby = msgBox.addButton("Volver al Menu", QMessageBox::AcceptRole);
            msgBox.exec();

            if (msgBox.clickedButton() == btnLobby) {
                cantMove = true;
                player->stop();
                emit returnToLobby();  // 🔹 emite señal diferente
                endBattle();
            }
            return;
        }

        // --- Si el jugador ganó (mantén flujo original) ---
        msgBox.setWindowTitle("¡Victoria!");
        msgBox.setText("¡Racionalista gano!\nPresiona 'Ir a Nivel 4' para continuar.");

        QAbstractButton* btnGoLevel4 = msgBox.addButton("Ir a Nivel 4", QMessageBox::AcceptRole);
        msgBox.exec();

        if (msgBox.clickedButton() == btnGoLevel4) {
            cantMove = true;        // now player can move
            player->stop();
            emit minigameFinished(); // signal that minigame ended
            endBattle();
        }
    });
}


void Batalla::GanoEmpirista()
{
    cantMove = false;
    playWinnerMusic("qrc:/Winners_Music/Hallowed_be_thy_Name.mp3");

    QTimer::singleShot(500, [this]() {
        QMessageBox msgBox;
        msgBox.setIconPixmap(QPixmap(":/Icons/empirista_icon.png").scaled(48,48));

        // 🔹 Si el jugador perdió
        if (protagonista->getLifes() < npc->getLifes()) {
            msgBox.setWindowTitle("Derrota...");
            msgBox.setText("El Empirista NPC ganó...\n");
            QAbstractButton* btnLobby = msgBox.addButton("Volver al Menu", QMessageBox::AcceptRole);
            msgBox.exec();

            if (msgBox.clickedButton() == btnLobby) {
                cantMove = true;
                player->stop();
                emit returnToLobby(); // <- volver al lobby
                endBattle();
            }
            return;
        }

        // 🔹 Si el jugador ganó
        msgBox.setWindowTitle("¡Victoria!");
        msgBox.setText("¡Empirista gano!\nPresiona 'Ir a Nivel 4' para continuar.");
        QAbstractButton* btnGoLevel4 = msgBox.addButton("Ir a Nivel 4", QMessageBox::AcceptRole);
        msgBox.exec();

        if (msgBox.clickedButton() == btnGoLevel4) {
            cantMove = true;
            player->stop();
            emit minigameFinished(); // avanza nivel
            endBattle();
        }
    });
}
// ================== EMPATE ==================
void Batalla::Empate()
{
    qDebug() << "Empate!";

    protagonista->setShowHeartsAbove(false);
    npc->setVisible(false);

    QTimer::singleShot(500, [this]() {
        QMessageBox msgBox;
        msgBox.setIconPixmap(QPixmap(":/Icons/empirista_icon.png").scaled(48,48));
        msgBox.setWindowTitle("Empate");
        msgBox.setText("¡Es un empate!\n");


        QAbstractButton* btnLobby = msgBox.addButton("Volver al Menu", QMessageBox::AcceptRole);
        msgBox.exec();

        if (msgBox.clickedButton() == btnLobby) {
            player->stop();
            emit returnToLobby();
            endBattle();
        }
    });

    cantMove = false;
}


void Batalla::showStyledMessage(const QString& title, const QString& text, const QString& team)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.setText(text);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setIconPixmap(QPixmap(team == "racionalista" ? ":/Icons/racionalista_icon.png"
                                                        : ":/Icons/empirista_icon.png").scaled(48, 48));

    // 💅 Custom style
    QString color = (team == "racionalista") ? "#2d89ef" : "#e67e22";
    msgBox.setStyleSheet(QString(R"(
        QMessageBox {
            background-color: rgba(20, 20, 20, 220);
            color: white;
            border: 2px solid %1;
            border-radius: 15px;
            font-family: 'Segoe UI';
            font-size: 12pt;
        }
        QPushButton {
            background-color: %1;
            color: white;
            border-radius: 8px;
            padding: 5px 15px;
        }
        QPushButton:hover {
            background-color: #ffffff;
            color: %1;
        }
    )").arg(color));

    msgBox.exec();
}


// ================= END BATTLE =================
void Batalla::endBattle()
{
    qDebug() << "🎬 Battle ended.";
}

void Batalla::loadNpc(bool team)
{
    npc = new Npcs();
    m_scene->addItem(npc);
    npc->setPos(584,416);
    npc->changeTeam(team ? 1 : 2);
}

void Batalla::playWinnerMusic(const QString& path)
{
    player->setSource(QUrl(path));
    player->play();
}


