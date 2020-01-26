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

protected:
    int distanceLabel;
    int excess;
};

#endif // PFPNODE_H
