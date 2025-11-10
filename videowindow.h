#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QAudioOutput>
#include <QUrl>
#include <QFile>
#include <QDebug>

class VideoWindow : public QWidget {
    Q_OBJECT

public:
    VideoWindow(QWidget *parent = nullptr) : QWidget(parent) {
        setWindowTitle("Intro Video");
        resize(800, 450);

        // --- Video widget ---
        videoWidget = new QVideoWidget(this);
        videoWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        // --- Skip button ---
        QPushButton *skipButton = new QPushButton("Skip");
        skipButton->setFixedWidth(100);
        skipButton->setStyleSheet("font-size: 16px; padding: 5px;");

        // --- Media player & audio output ---
        player = new QMediaPlayer(this);
        audioOutput = new QAudioOutput(this);
        player->setAudioOutput(audioOutput);
        player->setVideoOutput(videoWidget);

        // --- Load video ---
        QString videoPath = ":/Winners_Music/Discovery.mp4";
        if (QFile::exists(videoPath)) {
            player->setSource(QUrl("qrc:/Winners_Music/Discovery.mp4"));
        } else {
            qWarning() << "Video file not found:" << videoPath;
        }

        // --- Layout ---
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(videoWidget);
        layout->addWidget(skipButton, 0, Qt::AlignCenter);
        setLayout(layout);

        // --- Connections ---
        connect(skipButton, &QPushButton::clicked, this, [=]() {
            player->stop();
            this->close();
        });
        connect(player, &QMediaPlayer::mediaStatusChanged, this, [=](QMediaPlayer::MediaStatus status){
            if (status == QMediaPlayer::EndOfMedia) this->close();
        });

        audioOutput->setVolume(1.0); // max volume
        player->play();
    }

private:
    QMediaPlayer *player;
    QVideoWidget *videoWidget;
    QAudioOutput *audioOutput;
};
