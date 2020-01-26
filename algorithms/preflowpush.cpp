#include "preflowpush.h"

Adjacency_list convertToResidual(Adjacency_list network)
{

    Adjacency_list residualNetwork = Adjacency_list(network.getAdjacency_lists().size());

    for(size_t i = 0; i<network.getAdjacency_lists().size(); i++)
    {
        for(size_t j = 0; j<network.getAdjacency_lists()[i].size(); j++)
        {
            Arc currentArc = network.getAdjacency_lists()[i][j];
            Arc residualArcIJ = Arc(currentArc.getOrigin(),currentArc.getDestination(),currentArc.getCapacity());
            Arc residualArcJI = Arc(currentArc.getDestination(),int(i),currentArc.getCapacity());
            residualNetwork.addArc(i,residualArcIJ);
            residualNetwork.addArc(currentArc.getDestination(),residualArcJI);
        }
    }

    return residualNetwork;
}


void computeDistanceLabels(Adjacency_list network,std::vector<pFPnode> nodes)
{
    //l'array contenente i marchi inizializzato a 0 per tutti i nodi
    bool marks[nodes.size()];
    for(size_t i = 0;i < nodes.size();i++)
    {
        marks[i] = 0;
    }
    //la coda usata per salvare i nodi di cui esplorare i predecessori
    std::queue<int> list;
    //marchio il pozzo
    marks[nodes.size()-1] = 1;
    //setto la sua distance label a 0
    nodes[nodes.size()-1].setDistanceLabel(0);
    //inserisco il pozzo nella coda
    list.push(nodes.size()-1);
    //finchè la coda ha elementi:
    while(list.size()>0)
    {
        //prendo il primo nodo nella coda
        int node = list.front();
        for(size_t i = 0; i<network.getAdjacency_lists().size(); i++)
        {
            for(size_t j = 0; j<network.getAdjacency_lists()[i].size(); j++)
            {
                //per ognuno dei suoi archi entranti:
                Arc arc = network.getAdjacency_lists()[i][j];
                //se il nodo da cui si origina non è stato già marcato:
                if(arc.getDestination() == node && !marks[arc.getOrigin()])
                {
                    //marchio il nodo da cui si origina
                    marks[arc.getOrigin()] = 1;
                    //se la distance label del nodo destinazione + 1 è minore di quella attuale del nodo origine:
                    if(nodes[node].getDistanceLabel() + 1 < nodes[arc.getOrigin()].getDistanceLabel())
                    {
                        //la aggiorno con tale valore
                        nodes[arc.getOrigin()].setDistanceLabel(nodes[node].getDistanceLabel() + 1);
                    }
                    //aggiungo il nodo origine infondo alla coda
                    list.push(arc.getOrigin());
                }
            }
        }
        //rimuovo il primo nodo dalla coda
        list.pop();
    }
}


