#ifndef WAGONARRAY_H
#define WAGONARRAY_H

#include <wagon.h>



class WagonArray:public std::vector<Wagon*>
{
public:
    WagonArray();
};

#endif // WAGONARRAY_H
