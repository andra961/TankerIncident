#ifndef PFPNODE_H
#define PFPNODE_H


class pFPnode
{
public:
    pFPnode();

    double getExcess() const;
    void setExcess(double value);

    int getDistanceLabel() const;
    void setDistanceLabel(int value);

    void increaseExcess(double delta);
    void decreaseExcess(double delta);

protected:
    int distanceLabel;
    double excess;
};

#endif // PFPNODE_H
