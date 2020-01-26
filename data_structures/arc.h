#ifndef ARC_H
#define ARC_H


class Arc
{
public:
    Arc(int origin,int destination,int capacity);

    int getOrigin() const;

    int getDestination() const;

    int getCapacity() const;

    int getFlow() const;
    void setFlow(int value);

protected:
    int origin;
    int destination;
    int capacity;
    int flow;
    int residual;
};

#endif // ARC_H
