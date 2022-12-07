#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>
#include <QFont>
#include <treasure.h>
#include <wagon.h>
#include <train.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,sc(new QGraphicsScene())
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    //testing start
    sc->setSceneRect(ui->graphicsView->rect());
    ui->graphicsView->setScene(sc);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);

//    Treasure*t=new Treasure();
//    Treasure*t1=new Treasure();
//    Wagon*w=new Wagon();
//    w->addContentUp(t1);
//    w->addContentUp(t);
//    sc->addItem(w);
//    w->setPos(100,100);

    Train voz=Train();
    for(int i=0;i<6;i++){
        voz.push_back(new Wagon());
        for( int j=0;j<3;j++){
            voz.back()->addContentDown(new Treasure());

        }
    }
    voz.addTrainToScene(sc);


    //testing finish

    //init of Dialog
    dialog=new QDialog();

    dialog->setWindowModality(Qt::WindowModality::ApplicationModal);
    //dialog->setWindowTitle("")
    dialog->setMinimumWidth(640);
    dialog->setMinimumHeight(480);

    QVBoxLayout *vl=new QVBoxLayout();


    QPushButton*pbBackToMainMenu=new QPushButton();
    pbBackToMainMenu->setParent(dialog);
    pbBackToMainMenu->setText("Back to main menu");
    QFont font("Magnolia Sky");
    font.setBold(true);
    font.setPixelSize(14);
    setFont(font);

    //pbBackToMainMenu->setStyleSheet("border-image : url(:/images/button.png); color: white; background: transparent;");
    connect(pbBackToMainMenu,&QPushButton::clicked,this,&MainWindow::onBackToTheMenu);

    QPushButton*pbQuit=new QPushButton();
    pbQuit->setParent(dialog);
    pbQuit->setText("Quit");
    //pbQuit->setStyleSheet("border-image : url(:/images/button.png); color: white; background: transparent;");
    connect(pbQuit,&QPushButton::clicked,this,&QCoreApplication::quit);

    vl->addWidget(pbBackToMainMenu);
    vl->addWidget(pbQuit);

    dialog->setLayout(vl);
    //end of dialog init


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
    delete dialog;
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
    dialog->close();
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

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(ui->stackedWidget->currentIndex()==4 && event->key()==Qt::Key_Escape){

        dialog->show();
    }
}


