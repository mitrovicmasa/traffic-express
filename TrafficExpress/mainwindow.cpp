#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>
#include <QFont>
#include <treasure.h>
#include <wagon.h>
#include <train.h>
#include <hand.h>
#include <deck.h>
#include <table.h>
#include <actioncard.h>
#include <bulletcard.h>
#include <neutralbullet.h>
#include <roundcard.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , sc(new QGraphicsScene())
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    dialogInit();
    connectButtons();

    //testing start *******************************************************
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

    Train* voz=new Train();
    for(int i=0;i<6;i++){
        voz->push_back(new Wagon());
        for( int j=0;j<3;j++){
            voz->back()->addContentDown(new Treasure());

        }
    }

    sc->addItem(voz);
    voz->setPos(50,50);

    Hand* ruka= new Hand();
    ruka->push_back(new ActionCard(ActionType::PUNCH, BanditType::BUSINESS_WOMAN));
    ruka->push_back(new ActionCard(ActionType::PUNCH, BanditType::HOMELESS_MAN));
    ruka->push_back(new NeutralBullet());
    ruka->push_back(new BulletCard(BanditType::PICKPOCKET, 6));
    sc->addItem(ruka);
    ruka->setPos(50,500);

    Deck* spil = new Deck();
    spil->push_back(new ActionCard(ActionType::PUNCH, BanditType::BUSINESS_WOMAN));
    spil->push_back(new NeutralBullet());
    sc->addItem(spil);
    spil->setPos(600,500);

//    ruka.push_back(new ActionCard(ActionType::PUNCH, BanditType::BUSINESS_WOMAN));
//    ruka.push_back(new ActionCard(ActionType::PUNCH, BanditType::HOMELESS_MAN));
//    ruka.push_back(new NeutralBullet());
//    ruka.push_back(new BulletCard(BanditType::PICKPOCKET, 6));
//    ruka.addHandToScene(sc);


//    Deck spil = Deck();
//    spil.push_back(new ActionCard(ActionType::PUNCH, BanditType::BUSINESS_WOMAN));
//    spil.push_back(new ActionCard(ActionType::PUNCH, BanditType::HOMELESS_MAN));
//    spil.push_back(new NeutralBullet());
//    spil.push_back(new BulletCard(BanditType::PICKPOCKET, 6));
//    spil.addDeckToScene(sc);

    //Table test
    Table* tb = new Table();
    sc->addItem(tb);
    tb->setPos(1000,270);

//  ne radi mi ovaj test, nmg sad :)
//    std::vector<std::vector<MiniRoundType>> miniRounds = {
//         {MiniRoundType::FACE_UP, MiniRoundType::DOUBLE_CARDS, MiniRoundType::FACE_UP},
//         {MiniRoundType::FACE_UP, MiniRoundType::FACE_UP, MiniRoundType::HIDDEN, MiniRoundType::OPPOSITE_DIRECTION}
//    };
//    RoundCard* rc = new RoundCard(RoundCardType::FIVE_TO_SIX_PLAYERS, EventType::NONE, miniRounds[0]);
//    sc->addItem(rc);
//    rc.setPos(0,0);

    //testing finish ************************************************************
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dialog;
}


void MainWindow::connectButtons()
{
    connect(ui->pbGameRules, &QPushButton::clicked,
            this, &MainWindow::onGameRules);
    connect(ui->pbPlay, &QPushButton::clicked,
            this, &MainWindow::onPlay);
    connect(ui->pbQuit, &QPushButton::clicked,
            this, &QCoreApplication::quit);
    connect(ui->pbBackToMain, &QPushButton::clicked,
            this, &MainWindow::onBackToTheMenu);
    connect(ui->pbConnect, &QPushButton::clicked,
            this, &MainWindow::onConnect);
    connect(ui->pbReady, &QPushButton::clicked,
            this, &MainWindow::onReady);
    connect(ui->pbStart, &QPushButton::clicked,
            this, &MainWindow::onStart);
}

void MainWindow::dialogInit()
{
    dialog=new QDialog();

    dialog->setWindowModality(Qt::WindowModality::ApplicationModal);
    //dialog->setWindowTitle("")
    dialog->setMinimumWidth(640);
    dialog->setMinimumHeight(480);

    QVBoxLayout *vl=new QVBoxLayout();


    QPushButton *pbBackToMainMenu=new QPushButton();
    pbBackToMainMenu->setParent(dialog);
    pbBackToMainMenu->setText("Back to main menu");
    QFont font("Magnolia Sky");
    font.setBold(true);
    font.setPixelSize(14);
    setFont(font);

    //pbBackToMainMenu->setStyleSheet("border-image : url(:/images/button.png); color: white; background: transparent;");
    connect(pbBackToMainMenu,&QPushButton::clicked,this,&MainWindow::onBackToTheMenu);

    QPushButton *pbQuit=new QPushButton();
    pbQuit->setParent(dialog);
    pbQuit->setText("Quit");
    //pbQuit->setStyleSheet("border-image : url(:/images/button.png); color: white; background: transparent;");
    connect(pbQuit,&QPushButton::clicked,this,&QCoreApplication::quit);

    vl->addWidget(pbBackToMainMenu);
    vl->addWidget(pbQuit);

    dialog->setLayout(vl);
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


