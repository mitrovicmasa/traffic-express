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
    pbBackToMainMenu->setDisabled(true);
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

void MainWindow::onChangeReadyColor(bool condition)
{
    if(m_client->getReadys()[m_client->getIndex()]){
        ui->pbReady->setStyleSheet("background-color:green");
    }else{
        ui->pbReady->setStyleSheet("background-color:red");
    }
    ui->listWidget->clear();
    auto readys=m_client->getReadys();
    auto names=m_client->getNames();

    for(int i=0;i<names.size();i++){
        ui->listWidget->addItem(names[i]);


    }


}

void MainWindow::onChangeStartColor()
{
    if(m_client->allReady() && m_client->getHost()){
        ui->pbStart->setStyleSheet("background-color:green");
        ui->pbStart->setDisabled(false);
    }else if(m_client->getHost()){
        ui->pbStart->setStyleSheet("background-color:yellow");
        ui->pbStart->setDisabled(true);
    }else{

        ui->pbStart->setStyleSheet("background-color:red");
        ui->pbStart->setDisabled(true);
    }
    ui->listWidget->clear();
    auto readys=m_client->getReadys();
    auto names=m_client->getNames();

    for(int i=0;i<names.size();i++){
        ui->listWidget->addItem(names[i]);
        if(readys[i])
            ui->listWidget->item(i)->setBackground(Qt::green);
        else
            ui->listWidget->item(i)->setBackground(Qt::red);
    }





}

void MainWindow::onGameLoaded()
{
    PlayerPerspective*pp=m_client->getPlayerPerspective();
    connect(pp,&PlayerPerspective::playerChoseWagon,pp
            ,&PlayerPerspective::onPlayerChoseWagon);

    connect(pp,&PlayerPerspective::playerDrawCards,pp,&PlayerPerspective::onPlayerDrawCards);

    connect(pp,&PlayerPerspective::playerPlayedCard,pp
            ,&PlayerPerspective::onPlayerPlayedCard);

    connect(pp,&PlayerPerspective::actionSheriffSignal,pp
            ,&PlayerPerspective::onActionSheriffSignal);

    connect(pp,&PlayerPerspective::actionFireSignal,pp
            ,&PlayerPerspective::onActionFireSignal);

    connect(pp,&PlayerPerspective::actionRobberySignal, pp
            ,&PlayerPerspective::onActionRobberySignal);

    connect(pp,&PlayerPerspective::actionChangeFloorSignal,pp,&PlayerPerspective::onActionChangeFloorSignal);

    connect(pp,&PlayerPerspective::actionChangeWagonSignal,pp,&PlayerPerspective::onActionChangeWagonSignal);

    connect(pp,&PlayerPerspective::actionPunchSignal,pp,&PlayerPerspective::onActionPunchSignal);
////
    connect(pp,&PlayerPerspective::playerChoseWagon,m_client,&PlayerClient::onPlayerChoseWagon);
    connect(m_client,&PlayerClient::playerChoseWagon,pp,&PlayerPerspective::onPlayerChoseWagon);

    connect(pp,&PlayerPerspective::playerPlayedCard,m_client,&PlayerClient::onPlayerPlayedCard);
    connect(m_client,&PlayerClient::playerPlayedCard,pp,&PlayerPerspective::onPlayerPlayedCard);

    connect(pp,&PlayerPerspective::playerDrawCards,m_client,&PlayerClient::onPlayerDrawCards);
    connect(m_client,&PlayerClient::playerDrawCards,pp,&PlayerPerspective::onPlayerDrawCards);

    connect(pp,&PlayerPerspective::actionSheriffSignal,m_client,&PlayerClient::onActionSheriffSignal);
    connect(m_client,&PlayerClient::actionSheriffSignal,pp,&PlayerPerspective::onActionSheriffSignal);

    connect(pp,&PlayerPerspective::actionFireSignal,m_client,&PlayerClient::onActionFireSignal);
    connect(m_client,&PlayerClient::actionFireSignal,pp,&PlayerPerspective::onActionFireSignal);

    connect(pp,&PlayerPerspective::actionChangeFloorSignal,m_client,&PlayerClient::onActionChangeFloorSignal);
    connect(m_client,&PlayerClient::actionChangeFloorSignal,pp,&PlayerPerspective::onActionChangeFloorSignal);

    connect(pp,&PlayerPerspective::actionChangeWagonSignal,m_client,&PlayerClient::onActionChangeWagonSignal);
    connect(m_client,&PlayerClient::actionChangeWagonSignal,pp,&PlayerPerspective::onActionChangeWagonSignal);

    connect(pp,&PlayerPerspective::actionRobberySignal,m_client,&PlayerClient::onActionRobberySignal);
    connect(m_client,&PlayerClient::actionRobberySignal,pp,&PlayerPerspective::onActionRobberySignal);

    connect(pp,&PlayerPerspective::actionPunchSignal,m_client,&PlayerClient::onActionPunchSignal);
    connect(m_client,&PlayerClient::actionPunchSignal,pp,&PlayerPerspective::onActionPunchSignal);


    pp->setSceneRect(ui->graphicsView->rect());
    ui->graphicsView->setScene(pp);

    pp->addGameToScene();



    ui->graphicsView->setBackgroundBrush(QPixmap("://bluemoon.png"));
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    ui->stackedWidget->setCurrentIndex(4);
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
    QString name;
    if(ui->leName->isModified())
        name = ui->leName->text();
    else name = "Player";



    m_client=new PlayerClient();
    m_client->setUsername(name);

    connect(this,&MainWindow::readyClicked,m_client,&PlayerClient::onClickedReady);
    connect(this,&MainWindow::startClicked,m_client,&PlayerClient::onClickedStart);

    connect(m_client,&PlayerClient::gameLoaded,this,&MainWindow::onGameLoaded);
    connect(m_client,&PlayerClient::changeReadyColor,this,&MainWindow::onChangeReadyColor);
    connect(m_client,&PlayerClient::changeStartColor,this,&MainWindow::onChangeStartColor);
    m_client->startClient();
    if(m_client->getHost()){
        ui->pbStart->setStyleSheet("background-color:yellow");
        ui->pbStart->setDisabled(false);
    }else{
        ui->pbStart->setStyleSheet("background-color:red");
        ui->pbStart->setDisabled(true);
    }
     ui->pbReady->setStyleSheet("background-color:red");

//    sc->setSceneRect(ui->gvWaitingRoom->rect());
//    ui->gvWaitingRoom->setScene(sc);
//    ui->gvWaitingRoom->setBackgroundBrush(QColor(100,100,100));
//    ui->gvWaitingRoom->setRenderHint(QPainter::Antialiasing);
//    ui->gvWaitingRoom->setAlignment(Qt::AlignTop | Qt::AlignLeft);
//    //TODO: napraviti Tabelu za ovaj gv koja ce da ispisuje ime i ready/not ready

    //TODO: napraviti konekciju sa serverom :))))))
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::onReady()
{
    //TODO: obavestiti server da je plejer spreman
    ui->pbReady->setStyleSheet("background-color:green");
    emit readyClicked();


    //TODO: izmeniti tabelu da bude ready
}

void MainWindow::onStart()
{
    /*  plejer moze da klikne ovo samo ako je HOST
        a ako nije host, ne desi se nista...
        nmp za pocetak cu staviti da svako moze da klikne  */

    // imaginarni plejeri u nasoj partiji
//    std::vector<Player*> players;
//        players = {
//            new Player(BanditType::PICKPOCKET),
//            new Player(BanditType::SEDUCTRESS),
//            new Player(BanditType::STUDENT),
//    //        new Player(BanditType::RETIREE),
//    //        new Player(BanditType::HOMELESS_MAN),
//    //        new Player(BanditType::BUSINESS_WOMAN)
//        };
//    emit startClicked();
//    Game*game=new Game(players);
//    game->initialize();
//    game->setPhase(Phase::WAGON_SELECTION);
//    game->allPlayersDrawCards(6);
//    std::cout<<game->rounds()->size()<<std::endl;

//    if(m_client->getHost()){
        //start game
//    }


//        this->m_sp=new SinglePlayerStateMachine();
//        for(int i=0;i<players.size();i++){
//            Game*g=new Game();
//            g->fromVariant(game->toVariant());
//            //Ovo sada koristimo
////            this->m_sp->push_back(new PlayerPerspective(g,i));
//            //Ovo smo ranije koristili
//            this->m_sp->push_back(new PlayerPerspective(new Game(*game),i));


//            //std::cout<<pps.back()->getPlayerSize()<<std::endl;
//            m_sp->back()->addGameToScene();
//            //m_sp->back()->drawCards(6);
//        }
//        connect(m_sp,&SinglePlayerStateMachine::movePlayed,
//                this,&MainWindow::onMovePlayed);

//        (*m_sp)[0]->setSceneRect(ui->graphicsView->rect());
//        ui->graphicsView->setScene((*m_sp)[0]);
    if(m_client->getPlayerCount()<3)
        return;

    emit startClicked();

//    m_client->getPlayerPerspective()->setSceneRect(ui->graphicsView->rect());
//    ui->graphicsView->setScene(m_client->getPlayerPerspective());

//    m_client->getPlayerPerspective()->addGameToScene();



    ui->graphicsView->setBackgroundBrush(QPixmap("://bluemoon.png"));
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::onMovePlayed(int i)
{
    //qDebug()<<"MainWindow stigao";
    //qDebug()<<m_sp;

//    (*m_sp)[i]->setSceneRect(ui->graphicsView->rect());
//    ui->graphicsView->setScene((*m_sp)[i]);

}




void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(ui->stackedWidget->currentIndex()==4 && event->key()==Qt::Key_Escape){
        dialog->show();
    }
    if(event->key()==Qt::Key_G){


//        for(PlayerPerspective*pp:pps){
//            pp->setNextPlayerToToMove();

//        }
//        int pToMove=pps[0]->getPlayerToMoveIndex();
////        std::cout<<pToMove<<std::endl;
//        pps[pToMove]->setSceneRect(ui->graphicsView->rect());
//        ui->graphicsView->setScene(pps[pToMove]);


    }
    if(event->key()==Qt::Key_D){
//        //std::cout<<"im here"<<std::endl;
//        int pToMove=pps[0]->getPlayerToMoveIndex();
//        pps[pToMove]->drawCards(1);
    }


}


