#include "pfpnode.h"

pFPnode::pFPnode()
{
    this->distanceLabel = 1000;
    this->excess = 0;
}

int pFPnode::getExcess() const
{
    return excess;
}

void pFPnode::setExcess(int value)
{
    excess = value;
}

int pFPnode::getDistanceLabel() const
{
    return distanceLabel;
}

void pFPnode::setDistanceLabel(int value)
{
    distanceLabel = value;
}
