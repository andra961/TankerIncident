#ifndef PFPNODE_H
#define PFPNODE_H


class pFPnode
{
public:
    pFPnode();

    int getExcess() const;
    void setExcess(int value);

    int getDistanceLabel() const;
    void setDistanceLabel(int value);

    void increaseExcess(int delta);
    void decreaseExcess(int delta);

protected:
    int distanceLabel;
    int excess;
};

#endif // PFPNODE_H
