#ifndef CARDCOLECTION_H
#define CARDCOLECTION_H

#include <card.h>
#include <actioncard.h>
#include <vector>



class CardColection:public std::vector<Card*>
{
public:
    CardColection();
    CardColection(std::vector<ActionCard*> cards);
    CardColection(const CardColection&);
    CardColection Copy();
};

#endif // CARDCOLECTION_H
