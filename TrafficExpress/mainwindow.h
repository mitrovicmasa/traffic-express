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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onPlay();
    void onGameRules();
    void onBackToTheMenu();
    void onConnect();
    void onReady();
    void onStart();

    //void onMovePlayed(int i);

    void connectButtons();
    void dialogInit();
    void setImages();
    //void initializeGameGUI(Game*);
private:
    std::vector<PlayerPerspective*>pps;
    QGraphicsScene*sc;

    void showMessageBox(QString content) const;
    void keyPressEvent(QKeyEvent*);
    Ui::MainWindow *ui;
    QDialog*dialog;

    SinglePlayerStateMachine *sp;

};
#endif // MAINWINDOW_H
