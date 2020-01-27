#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H

#include <vector>
#include <array>
#include <data_structures/arc.h>

class Adjacency_list
{
public:
    Adjacency_list(int nNodes);
    void addArc(bool residualType,int origin, int destination, int capacity);
    void addArc(int origin, Arc arc);
    bool updateArc(bool residualType,int origin, int destination, int capacity);
    bool deleteArc(int origin, int destination);

    std::vector<std::vector<Arc>>& getAdjacency_lists();

protected:
    std::vector<std::vector<Arc>> adjacency_lists;
};

#endif // ADJACENCY_LIST_H
