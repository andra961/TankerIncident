#include "adjacency_list.h"

Adjacency_list::Adjacency_list(int nNodes)
{
 this->adjacency_lists.resize(nNodes);
}

void Adjacency_list::addArc(int origin, int destination, int capacity)
{
    Arc arc = Arc(origin,destination,capacity);
    this->adjacency_lists[origin].push_back(arc);
}

void Adjacency_list::addArc(int origin, Arc arc)
{
    this->adjacency_lists[origin].push_back(arc);
}

bool Adjacency_list::updateArc(int origin, int destination, int capacity)
{
    size_t size = this->adjacency_lists[origin].size();
    for(size_t i = 0; i< size; i++){
        if(this->adjacency_lists[origin][i].getDestination() == destination){
            Arc newArc = Arc(origin,capacity,destination);
            this->adjacency_lists[origin][i] = newArc;
            return 1;
        }
    }

    return 0;
}

bool Adjacency_list::deleteArc(int origin, int destination)
{
    size_t size = this->adjacency_lists[origin].size();
    for(size_t i = 0; i< size; i++){
        if(this->adjacency_lists[origin][i].getDestination() == destination){
            this->adjacency_lists[origin].erase(this->adjacency_lists[origin].begin() + i);
            return 1;
        }
    }

    return 0;
}

std::vector<std::vector<Arc>>& Adjacency_list::getAdjacency_lists()
{
    return adjacency_lists;
}
