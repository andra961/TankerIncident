#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H

#include <vector>
#include <array>
#include <data_structures/arc.h>

class Adjacency_list
{
public:
    Adjacency_list(size_t nNodes,size_t source, size_t sink);
    void addArc(bool residualType,int origin, int destination, int capacity);
    void addArc(int origin, Arc arc);
    bool updateArc(bool residualType,int origin, int destination, int capacity);
    bool deleteArc(int origin, int destination);

    std::vector<std::vector<Arc>>& getAdjacency_lists();

    size_t getNNodes() const;

    size_t getSource() const;

    size_t getSink() const;

protected:
    std::vector<std::vector<Arc>> adjacency_lists;
    size_t nNodes;
    size_t source;
    size_t sink;
};

#endif // ADJACENCY_LIST_H
