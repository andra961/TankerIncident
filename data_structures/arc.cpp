#include "arc.h"

Arc::Arc(int origin,int destination, int capacity)
{
    this->origin = origin;
    this->destination = destination;
    this->capacity = capacity;
    this->flow = 0;
    this->residual = capacity - flow;
}

int Arc::getOrigin() const
{
    return origin;
}

int Arc::getDestination() const
{
    return destination;
}

int Arc::getCapacity() const
{
    return capacity;
}

int Arc::getFlow() const
{
    return flow;
}

void Arc::setFlow(int value)
{
    flow = value;
    this->residual = capacity - flow;
}
