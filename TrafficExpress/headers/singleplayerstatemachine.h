#ifndef SINGLEPLAYERSTATEMACHINE_H
#define SINGLEPLAYERSTATEMACHINE_H


#include "playerperspectivecollection.h"


class SinglePlayerStateMachine:public QObject
{
    Q_OBJECT
public:
    SinglePlayerStateMachine();
    SinglePlayerStateMachine(std::vector<PlayerPerspective*>&);



    PlayerPerspective*operator[](int);
    int size();
    void push_back(PlayerPerspective*);
    PlayerPerspective* back();


public slots:
    void onMovePlayed(PlayerPerspective*);

signals:
    void movePlayed(int i);

private:
    PlayerPerspectiveCollection m_perspectives;

    int currPerspectiveIndex;



};

#endif // SINGLEPLAYERSTATEMACHINE_H
