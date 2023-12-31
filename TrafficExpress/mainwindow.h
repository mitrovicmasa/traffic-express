#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QKeyEvent>
#include <QMainWindow>
#include<QDialog>
#include<QPushButton>
#include <QGraphicsScene>
#include <game.h>
#include <table.h>
#include <playerperspective.h>
#include <singleplayerstatemachine.h>

#include <client/playerclient.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void connectButtons();
    void dialogInit();
    void setImages();
    void keyPressEvent(QKeyEvent*);

private slots:
    void onPlay();
    void onGameRules();
    void onBackToTheMenu();
    void onConnect();
    void onReady();
    void onStart();
    void onMovePlayed(int i);
    void onChangeReadyColor(bool);
    void onChangeStartColor();
    void onGameLoaded();

signals:
    void readyClicked();
    void startClicked();

private:
    PlayerClient* m_client;
    Ui::MainWindow* ui;
    QDialog* dialog;
};
#endif // MAINWINDOW_H
