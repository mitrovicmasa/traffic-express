#include "../headers/singleplayerstatemachine.h"

//#include "ui_mainwindow.h"

SinglePlayerStateMachine::SinglePlayerStateMachine()
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
    m_perspectives.push_back((pp));
}

PlayerPerspective *SinglePlayerStateMachine::back()
{
    return m_perspectives.back();
}

void SinglePlayerStateMachine::onMovePlayed(PlayerPerspective *p)
{
    currPerspectiveIndex=(currPerspectiveIndex+1)%m_perspectives.size();

    emit movePlayed(currPerspectiveIndex);


}
