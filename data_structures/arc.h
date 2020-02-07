#ifndef ARC_H
#define ARC_H
#include <stddef.h>

class Arc
{
public:
    Arc(bool residualType,int origin,int destination,double capacity);

    int getOrigin() const;

    int getDestination() const;

    double getCapacity() const;

    double getFlow() const;
    void setFlow(double value);

    size_t getMate() const;
    void setMate(const size_t &value);

    double getResidual() const;
    void setResidual(double value);

    void pushFlow(double flow);

    bool getResidualType() const;
    void setResidualType(bool value);

protected:
    bool residualType;
    int origin;
    int destination;
    double capacity;
    double flow;
    int residual;
    size_t mate;
};

#endif // ARC_H
