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
    for(int i=0;i<m_perspectives.size();i++){
        connect(m_perspectives[i],&PlayerPerspective::playerChoseWagon,pp
                ,&PlayerPerspective::onPlayerChoseWagon);
        connect(pp,&PlayerPerspective::playerChoseWagon,m_perspectives[i]
                ,&PlayerPerspective::onPlayerChoseWagon);


        connect(m_perspectives[i],&PlayerPerspective::playerPlayedCard,pp
                ,&PlayerPerspective::onPlayerPlayedCard);
        connect(pp,&PlayerPerspective::playerPlayedCard,m_perspectives[i]
                ,&PlayerPerspective::onPlayerPlayedCard);

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
