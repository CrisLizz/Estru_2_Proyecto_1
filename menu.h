#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class menu : public QWidget
{
    Q_OBJECT
public:
    explicit menu(QWidget *parent = nullptr);
    QPushButton* playButton;
    QPushButton* exitButton;

private:
    QLabel* fondo;
    QLabel* title;

private slots:
    void onPlayButtonClicked();

signals:
};

#endif // MENU_H
