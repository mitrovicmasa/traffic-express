#ifndef CARDCOLECTION_H
#define CARDCOLECTION_H

#include <card.h>
#include <vector>



class CardColection:public std::vector<Card*>
{
public:
    CardColection();
};

#endif // CARDCOLECTION_H
