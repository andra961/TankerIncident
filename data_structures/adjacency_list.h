#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H

#include <vector>
#include <array>

class Adjacency_list
{
public:
    Adjacency_list();
    void addNode(int node);
    void addToAdjacencyList(int origin, int destination, int capacity, int flow, int residual);

protected:
    std::vector<std::vector<std::array<int,4>>>  adjacency_lists;
};

#endif // ADJACENCY_LIST_H
