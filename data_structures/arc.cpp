#include "arc.h"

Arc::Arc(bool residualType,int origin,int destination, double capacity)
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

double Arc::getCapacity() const
{
    return capacity;
}

double Arc::getFlow() const
{
    return flow;
}

void Arc::setFlow(double value)
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

double Arc::getResidual() const
{
    return residual;
}

void Arc::setResidual(double value)
{
    residual = value;
}

void Arc::pushFlow(double flow)
{
    if(this->residualType)
    {
        this->setFlow(this->getFlow() + flow);
    }
    else
    {
        this->setFlow(this->getFlow() - flow);
    }
}

bool Arc::getResidualType() const
{
    return residualType;
}

void Arc::setResidualType(bool value)
{
    residualType = value;
}
