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
#include <playerstats.h>
#include <QPixmap>
#include<headers/miniround.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , sc(new QGraphicsScene())
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    dialogInit();
    connectButtons();
    ui->labelTrafficExpress->setPixmap(QPixmap("://traffic_express.png").scaled(QSize(350,350), Qt::IgnoreAspectRatio, Qt::FastTransformation));
    //setButtonIcon();

    //testing start *******************************************************
    sc->setSceneRect(ui->graphicsView->rect());
    ui->graphicsView->setScene(sc);
    //ui->graphicsView->setBackgroundBrush(QPixmap("://clouds.png"));
    //ui->graphicsView->setBackgroundBrush(QColor:);
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
            voz->back()->addContentDown(new Treasure(250, TreasureType::MONEYBAG));
            voz->back()->addPlayerDown(new Player(BanditType::BUSINESS_WOMAN));
            voz->back()->addPlayerUp(new Player(BanditType::PICKPOCKET));
            voz->back()->addContentUp(new Treasure(500, TreasureType::DIAMOND));
        }

    }
    voz->back()->takePlayerDown(BanditType::BUSINESS_WOMAN);
    sc->addItem(voz);
    voz->setPos(50,50);

    Hand* ruka= new Hand();
    ruka->push_back( new ActionCard(ActionType::MARSHAL, BanditType::BUSINESS_WOMAN));
    ruka->push_back(new ActionCard(ActionType::PUNCH, BanditType::HOMELESS_MAN));
    ruka->push_back(new NeutralBullet());
    ruka->push_back(new BulletCard(BanditType::SEDUCTRESS, 3));
    ruka->push_back(new BulletCard(BanditType::RETIREE, 4));
    ruka->push_back(new ActionCard(ActionType::ROBBERY, BanditType::STUDENT));
    ruka->push_back(new ActionCard(ActionType::FLOOR_CHANGE, BanditType::PICKPOCKET));
    sc->addItem(ruka);
    ruka->setPos(50,450);

    Deck* spil = new Deck();
    spil->push_back(new ActionCard(ActionType::PUNCH, BanditType::BUSINESS_WOMAN));
    NeutralBullet *nb = new NeutralBullet();
    nb->setFaceUp(false);
    spil->push_back(nb);
    sc->addItem(spil);
    spil->setPos(50,300);

    Deck* grupniSpil = new Deck();
    grupniSpil->push_back(new ActionCard(ActionType::FIRE, BanditType::STUDENT));
    sc->addItem(grupniSpil);
    grupniSpil->setPos(300,300);

    //Table test
    Table* tb = new Table();
    for (int i = 0; i<4; i++){
        tb->push_back(new PlayerStats());
    }
    sc->addItem(tb);
    tb->setPos(810,270);

    MiniRound*mr=new MiniRound(MiniRoundType::DOUBLE_CARDS);
    MiniRound*mr1=new MiniRound(MiniRoundType::HIDDEN);
    RoundCard*rc=new RoundCard(RoundCardType::THREE_TO_FOUR_PLAYERS,EventType::MARSHALS_REVENGE,std::vector<MiniRound*>());
    sc->addItem(rc);
    rc->setPos(500,300);
    //rc->push_back(mr);
    //rc->push_back(mr1);
    for(int i=0;i<4;i++){
        rc->push_back(new MiniRound(MiniRoundType::HIDDEN));

    }
//    mr->setParentItem(rc);
//    mr->setPos(0,0);
//    mr1->setParentItem(rc);
//    mr1->setPos(60,0);


//    PlayerStats *ps = new PlayerStats();
//    sc->addItem(ps);
//    ps->setPos(810, 270);

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
    connect(ui->pbBackToMain_2, &QPushButton::clicked,
            this, &MainWindow::onBackToTheMenu);
    connect(ui->pbBackToMain_3, &QPushButton::clicked,
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
    pbBackToMainMenu->setPalette(QPalette("://buttonPaleta.xml"));
    pbBackToMainMenu->setParent(dialog);
    pbBackToMainMenu->setText("Back to main menu");
    QFont font("Magnolia Sky");
    font.setBold(true);
    font.setPixelSize(14);
    setFont(font);
    connect(pbBackToMainMenu,&QPushButton::clicked,this,&MainWindow::onBackToTheMenu);

    QPushButton *pbQuit=new QPushButton();
    pbQuit->setPalette(QPalette("://buttonPaleta.xml"));
    pbQuit->setParent(dialog);
    pbQuit->setText("Quit");
    connect(pbQuit,&QPushButton::clicked,this,&QCoreApplication::quit);

    vl->addWidget(pbBackToMainMenu);
    vl->addWidget(pbQuit);

    dialog->setLayout(vl);
}

//void MainWindow::setButtonIcon()
//{
//    QImage img;
//        QPixmap pixmap;

//        img.load(":/../resource/button.png");
//        pixmap = QPixmap::fromImage(img).scaled(30, 30);

//        ui->pbPlay->setIcon(QIcon(pixmap));
//        ui->pbPlay->setIconSize(QSize(30, 30));
//}

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


