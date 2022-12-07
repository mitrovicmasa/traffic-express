#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QKeyEvent>
#include <QMainWindow>
#include<QDialog>
#include<QPushButton>
#include <QGraphicsScene>

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

private:
    void keyPressEvent(QKeyEvent*);

    Ui::MainWindow *ui;
    QDialog*dialog;
    QGraphicsScene*sc;
};
#endif // MAINWINDOW_H
