#include "arc.h"

Arc::Arc(bool residualType,int origin,int destination, int capacity)
{
    this->origin = origin;
    this->destination = destination;
    this->capacity = capacity;
    this->flow = 0;
    this->residualType = residualType;
    if(residualType){

        this->residual = capacity - flow;
    }
    else{

        this->residual = flow;
    }

    this->mate = 0;

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
    if(this->residualType){

        this->residual = capacity - flow;
    }
    else{

        this->residual = flow;
    }

}

size_t Arc::getMate() const
{
    return mate;
}

void Arc::setMate(const size_t &value)
{
    mate = value;
}

int Arc::getResidual() const
{
    return residual;
}

void Arc::setResidual(int value)
{
    residual = value;
}
