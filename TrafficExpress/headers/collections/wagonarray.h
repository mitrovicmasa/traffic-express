#ifndef WAGONARRAY_H
#define WAGONARRAY_H

#include <wagon.h>



class WagonArray:public std::vector<Wagon*>
{
public:
    WagonArray();

    WagonArray(const WagonArray&other);
};

#endif // WAGONARRAY_H
