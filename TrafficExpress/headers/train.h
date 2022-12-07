#ifndef TRAIN_H
#define TRAIN_H

#include <vector>
#include <wagon.h>



class Train:public std::vector<Wagon*>
{

public:
    Train();

    void addTrainToScene(QGraphicsScene*sc);

};

#endif // TRAIN_H
