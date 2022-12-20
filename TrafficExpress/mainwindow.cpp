#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>
#include <QStyle>
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
#include <headers/miniround.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , sc(new QGraphicsScene())
{
    ui->setupUi(this);
    this->setWindowTitle("Traffic Express");
    ui->stackedWidget->setCurrentIndex(0);

    dialogInit();
    connectButtons();
    setImages();
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
    pbBackToMainMenu->setStyleSheet("border-image : url(://button.png); color: white; background: transparent;");



    QPushButton *pbQuit=new QPushButton();
    pbQuit->setPalette(QPalette("://buttonPaleta.xml"));
    pbQuit->setParent(dialog);
    pbQuit->setText("Quit");
    connect(pbQuit,&QPushButton::clicked,this,&QCoreApplication::quit);
    pbQuit->setStyleSheet("border-image : url(://button.png); color: white; background: transparent;");

    vl->addWidget(pbBackToMainMenu);
    vl->addWidget(pbQuit);

    dialog->setLayout(vl);
}

void MainWindow::setImages()
{
    ui->labelTrafficExpress->setPixmap(QPixmap("://traffic_express.png").scaled(QSize(350,350), Qt::IgnoreAspectRatio, Qt::FastTransformation));
    ui->pbPlay->setStyleSheet("border-image : url(://button.png); color: white; background: transparent;");
    ui->pbBackToMain->setStyleSheet("border-image : url(://button.png); color: white; background: transparent;");
    ui->pbQuit->setStyleSheet("border-image : url(://button.png); color: white; background: transparent;");
    ui->pbGameRules->setStyleSheet("border-image : url(://button.png); color: white; background: transparent;");
    ui->pbConnect->setStyleSheet("border-image : url(://button.png); color: white; background: transparent;");
    ui->pbBackToMain_2->setStyleSheet("border-image : url(://button.png); color: white; background: transparent;");
    ui->pbBackToMain_3->setStyleSheet("border-image : url(://button.png); color: white; background: transparent;");
    ui->pbConnect->setStyleSheet("border-image : url(://button.png); color: white; background: transparent;");
    ui->pbStart->setStyleSheet("border-image : url(://button.png); color: white; background: transparent;");
    ui->pbReady->setStyleSheet("border-image : url(://button.png); color: white; background: transparent;");

    ui->scroll_rules->setStyleSheet("border-image : url(://rules_bg.jpg);");
    ui->textEdit->setStyleSheet("border-image : url(://rules_bg.jpg);");
}


// Message Box
void MainWindow::showMessageBox(QString content) const {
  QMessageBox mb;

  mb.setWindowTitle("Message: ");
  mb.setIconPixmap(QPixmap("://box.jpg"));
  mb.setInformativeText(content);
  //mb.setIcon(QMessageBox::Question);
  //mb.setTextInteractionFlags(QStyle::StandardPixmap);
  mb.exec();
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

    //showMessageBox("Enter your username!");

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

    // imaginarni plejeri u nasoj partiji
    std::vector<Player*> players;
        players = {
            new Player(BanditType::PICKPOCKET),
            new Player(BanditType::SEDUCTRESS),
            new Player(BanditType::STUDENT),
    //        new Player(BanditType::RETIREE),
    //        new Player(BanditType::HOMELESS_MAN),
    //        new Player(BanditType::BUSINESS_WOMAN)
        };

    // inicijalizacija partije s ovim plejerima
    // i pocetni gui tj. samo one stvari koje svi vide




    Game*game=new Game(players);
    game->initialize();
    std::cout<<game->players().size()<<std::endl;

//    PlayerPerspective*pp=new PlayerPerspective(game,1);
//    pp->addGameToScene();
//    pp->drawCards(6);
    this->pps=std::vector<PlayerPerspective*>();
    for(int i=0;i<players.size();i++){
        this->pps.push_back(new PlayerPerspective(new Game(*game),i));
        //std::cout<<pps.back()->getPlayerSize()<<std::endl;
        pps.back()->addGameToScene();
        pps.back()->drawCards(6);
    }



    pps[0]->setSceneRect(ui->graphicsView->rect());
    ui->graphicsView->setScene(pps[0]);
//    pp->setSceneRect(ui->graphicsView->rect());
//    ui->graphicsView->setScene(pp);
    ui->graphicsView->setBackgroundBrush(QPixmap("://clouds.png"));
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);



    ui->stackedWidget->setCurrentIndex(4);
}


//void MainWindow::initializeGameGUI(Game *game)
//{
//    sc->setSceneRect(ui->graphicsView->rect());
//    ui->graphicsView->setScene(sc);
//    ui->graphicsView->setBackgroundBrush(QPixmap("://clouds.png"));
//    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
//    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);

//    train = game->wagons();
//    sc->addItem(train);
//    train->setPos(50,50);

//    table = new Table();
//    for (Player* p:game->players()){
//        table->push_back(new PlayerStats(p));
//    }
//    sc->addItem(table);
//    table->setPos(810,270);

//    roundcard = game->rounds()[0];
//    sc->addItem(roundcard);
//    roundcard->setPos(500,300);

//    groupDeck = new Deck();
//    sc->addItem(groupDeck);
//    groupDeck->setPos(300,300);

//    playerDeck = new Deck();
//    sc->addItem(playerDeck);
//    playerDeck->setPos(50,300);

//    hand = new Hand();
//    sc->addItem(hand);
//    hand->setPos(50,450);
//}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(ui->stackedWidget->currentIndex()==4 && event->key()==Qt::Key_Escape){
        dialog->show();
    }
    if(event->key()==Qt::Key_G){


        for(PlayerPerspective*pp:pps){
            pp->setNextPlayerToToMove();

        }
        int pToMove=pps[0]->getPlayerToMoveIndex();
//        std::cout<<pToMove<<std::endl;
        pps[pToMove]->setSceneRect(ui->graphicsView->rect());
        ui->graphicsView->setScene(pps[pToMove]);


    }
    if(event->key()==Qt::Key_D){
        //std::cout<<"im here"<<std::endl;
        int pToMove=pps[0]->getPlayerToMoveIndex();
        pps[pToMove]->drawCards(1);
    }


}


