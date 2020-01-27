#ifndef ARC_H
#define ARC_H
#include <stddef.h>

class Arc
{
public:
    Arc(bool residualType,int origin,int destination,int capacity);

    int getOrigin() const;

    int getDestination() const;

    int getCapacity() const;

    int getFlow() const;
    void setFlow(int value);

    size_t getMate() const;
    void setMate(const size_t &value);

    int getResidual() const;
    void setResidual(int value);

protected:
    bool residualType;
    int origin;
    int destination;
    int capacity;
    int flow;
    int residual;
    size_t mate;
};

#endif // ARC_H
