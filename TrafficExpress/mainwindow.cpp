#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pbGameRules, &QPushButton::clicked,
            this, &MainWindow::onGameRules);
    connect(ui->pbPlay, &QPushButton::clicked,
            this, &MainWindow::onPlay);
    connect(ui->pbBackToMain, &QPushButton::clicked,
            this, &MainWindow::onBackToTheMenu);
    connect(ui->pbConnect, &QPushButton::clicked,
            this, &MainWindow::onConnect);
    connect(ui->pbReady, &QPushButton::clicked,
            this, &MainWindow::onReady);
    connect(ui->pbStart, &QPushButton::clicked,
            this, &MainWindow::onStart);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onPlay()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::onGameRules()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::onBackToTheMenu()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::onConnect()
{
    // auto const name = ui->leName;
    // postaviti ime plejera na name, a ako polje nije popunjeno onda na Player1, Player2...

    // napraviti konekciju sa serverom :))))))

    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::onReady()
{
    // obavestiti Game da je plejer spreman

    // izmeniti graphics view da se u tabelu doda "ime_plejera - ready"
}

void MainWindow::onStart()
{
    /*  plejer moze da klikne ovo samo ako je HOST
        a ako nije host, ne desi se nista...
        nmp za pocetak cu staviti da svako moze da klikne  */

    // SADA POCINJE INICIJALIZACIJA PARTIJE !!!!!

    ui->stackedWidget->setCurrentIndex(4);
}


