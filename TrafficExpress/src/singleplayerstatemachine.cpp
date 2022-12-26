#include "../headers/singleplayerstatemachine.h"

//#include "ui_mainwindow.h"

SinglePlayerStateMachine::SinglePlayerStateMachine()
    :currPerspectiveIndex(0)
{

}



SinglePlayerStateMachine::SinglePlayerStateMachine(std::vector<PlayerPerspective *> &pps)
{

    currPerspectiveIndex=0;
    for(PlayerPerspective*pp:pps){
        m_perspectives.push_back(pp);
    }

    for(int i=0;i<m_perspectives.size();i++){
        for(int j=0;j<m_perspectives.size();j++){
            if(i!=j){
                //connect Player Perspectives here!
                connect(m_perspectives[i],&PlayerPerspective::playerChoseWagon,m_perspectives[j]
                        ,&PlayerPerspective::onPlayerChoseWagon);
                ;
            }
        }
        connect(m_perspectives[i],&PlayerPerspective::movePlayed,this,
                &SinglePlayerStateMachine::onMovePlayed);
    }
}

PlayerPerspective *SinglePlayerStateMachine::operator[](int i)
{
    return m_perspectives[i];
}

int SinglePlayerStateMachine::size()
{
    return m_perspectives.size();
}

void SinglePlayerStateMachine::push_back(PlayerPerspective *pp)
{
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



    for(int i=0;i<m_perspectives.size();i++){

        connect(m_perspectives[i],&PlayerPerspective::actionChangeWagonSignal,pp,&PlayerPerspective::onActionChangeWagonSignal);
        connect(pp,&PlayerPerspective::actionChangeWagonSignal,m_perspectives[i],&PlayerPerspective::onActionChangeWagonSignal);

        connect(m_perspectives[i],&PlayerPerspective::actionChangeFloorSignal,pp,&PlayerPerspective::onActionChangeFloorSignal);
        connect(pp,&PlayerPerspective::actionChangeFloorSignal,m_perspectives[i],&PlayerPerspective::onActionChangeFloorSignal);

        connect(m_perspectives[i],&PlayerPerspective::actionSheriffSignal,pp
                ,&PlayerPerspective::onActionSheriffSignal);
        connect(pp,&PlayerPerspective::actionSheriffSignal,m_perspectives[i]
                ,&PlayerPerspective::onActionSheriffSignal);

        connect(m_perspectives[i],&PlayerPerspective::actionFireSignal,pp
                ,&PlayerPerspective::onActionFireSignal);
        connect(pp,&PlayerPerspective::actionFireSignal,m_perspectives[i]
                ,&PlayerPerspective::onActionFireSignal);

        connect(m_perspectives[i],&PlayerPerspective::actionRobberySignal,pp
                ,&PlayerPerspective::onActionRobberySignal);
                connect(pp,&PlayerPerspective::actionRobberySignal,m_perspectives[i]
                ,&PlayerPerspective::onActionRobberySignal);

        connect(m_perspectives[i],&PlayerPerspective::playerChoseWagon,pp
                ,&PlayerPerspective::onPlayerChoseWagon);
        connect(pp,&PlayerPerspective::playerChoseWagon,m_perspectives[i]
                ,&PlayerPerspective::onPlayerChoseWagon);


        connect(m_perspectives[i],&PlayerPerspective::playerPlayedCard,pp
                ,&PlayerPerspective::onPlayerPlayedCard);
        connect(pp,&PlayerPerspective::playerPlayedCard,m_perspectives[i]
                ,&PlayerPerspective::onPlayerPlayedCard);

        connect(m_perspectives[i],&PlayerPerspective::playerDrawCards,
                pp,&PlayerPerspective::onPlayerDrawCards);
        connect(pp,&PlayerPerspective::playerDrawCards,m_perspectives[i],&PlayerPerspective::onPlayerDrawCards);
    }


    m_perspectives.push_back((pp));
    //Needs more conecting!! TODO
    connect(pp,&PlayerPerspective::movePlayed,this,
            &SinglePlayerStateMachine::onMovePlayed);
}

PlayerPerspective *SinglePlayerStateMachine::back()
{
    return m_perspectives.back();
}

void SinglePlayerStateMachine::onMovePlayed(PlayerPerspective *p)
{
    qDebug()<<currPerspectiveIndex;
    currPerspectiveIndex=(currPerspectiveIndex+1)%m_perspectives.size();


    emit movePlayed(currPerspectiveIndex);


}
