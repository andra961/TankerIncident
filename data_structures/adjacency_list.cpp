#include "adjacency_list.h"

Adjacency_list::Adjacency_list(size_t nNodes,size_t source, size_t sink)
{
    this->adjacency_lists.resize(nNodes);
    this->nNodes = nNodes;
    this->source = source;
    this->sink = sink;
}

void Adjacency_list::addArc(bool residualType,int origin, int destination, int capacity)
{
    Arc arc = Arc(residualType,origin,destination,capacity);
    this->adjacency_lists[origin].push_back(arc);
}

void Adjacency_list::addArc(int origin, Arc arc)
{
    this->adjacency_lists[origin].push_back(arc);
}

bool Adjacency_list::updateArc(bool residualType,int origin, int destination, int capacity)
{
    size_t size = this->adjacency_lists[origin].size();
    for(size_t i = 0; i< size; i++){
        if(this->adjacency_lists[origin][i].getDestination() == destination){
            Arc newArc = Arc(residualType,origin,capacity,destination);
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

size_t Adjacency_list::getNNodes() const
{
    return nNodes;
}

size_t Adjacency_list::getSource() const
{
    return source;
}

size_t Adjacency_list::getSink() const
{
    return sink;
}
