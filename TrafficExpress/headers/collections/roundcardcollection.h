#ifndef ROUNDCARDCOLLECTION_H
#define ROUNDCARDCOLLECTION_H

#include <roundcard.h>



class RoundCardCollection:public std::vector<RoundCard*>
{
public:
    RoundCardCollection();

    RoundCardCollection(std::vector<RoundCard*>&);
    RoundCardCollection(const RoundCardCollection&);
};

#endif // ROUNDCARDCOLLECTION_H
