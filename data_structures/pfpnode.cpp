#include "pfpnode.h"

pFPnode::pFPnode()
{
    this->distanceLabel = 1000000;
    this->excess = 0;
}

double pFPnode::getExcess() const
{
    return excess;
}

void pFPnode::setExcess(double value)
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

void pFPnode::increaseExcess(double delta)
{
    this->excess += delta;
}

void pFPnode::decreaseExcess(double delta)
{
    this->excess -= delta;
}
