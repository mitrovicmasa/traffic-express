#ifndef CARD_H
#define CARD_H

#include<string>

class Card {

public:
    Card();
    virtual ~Card();

    virtual Card *Copy() const = 0;

    virtual std::string toString() const;
    virtual bool operator==(const Card *c) const = 0;
    virtual bool operator!=(const Card *c) const = 0;

private:

};

#endif // CARD_H
