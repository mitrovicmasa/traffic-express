#ifndef CARDCOLECTION_H
#define CARDCOLECTION_H

#include <card.h>
#include <vector>



class CardColection:public std::vector<Card*>
{
public:
    CardColection();
    CardColection Copy();
};

#endif // CARDCOLECTION_H
