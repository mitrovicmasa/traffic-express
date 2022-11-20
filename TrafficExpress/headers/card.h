#ifndef CARD_H
#define CARD_H

#include<string>

class Card {

public:

    // Constructors
    Card();
    virtual Card *Copy() const = 0;

    // Destructor
    virtual ~Card();

    // Other methods
    virtual std::string toString() const;

    //virtual bool operator==(const Card *c) const = 0;
    //virtual bool operator!=(const Card *c) const = 0;

private:

};

#endif // CARD_H
