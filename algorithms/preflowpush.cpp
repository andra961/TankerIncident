#include "preflowpush.h"

Adjacency_list convertToResidual(Adjacency_list& network)
{

    Adjacency_list residualNetwork = Adjacency_list(network.getAdjacency_lists().size());

    for(size_t i = 0; i<network.getAdjacency_lists().size(); i++)
    {
        for(size_t j = 0; j<network.getAdjacency_lists()[i].size(); j++)
        {
            Arc currentArc = network.getAdjacency_lists()[i][j];
            Arc residualArcIJ = Arc(1,currentArc.getOrigin(),currentArc.getDestination(),currentArc.getCapacity());
            Arc residualArcJI = Arc(0,currentArc.getDestination(),int(i),currentArc.getCapacity());
            //inizializzo il mate di ij, che sarà l'indice dove ji si trova nella lista di adiacenza di j
            size_t mate1 = residualNetwork.getAdjacency_lists()[currentArc.getDestination()].size();
            //inizializzo il mate di ji, che sarà l'indice dove ij si trova nella lista di adiacenza di i
            size_t mate2 = residualNetwork.getAdjacency_lists()[currentArc.getOrigin()].size();
            residualArcIJ.setMate(mate1);
            residualArcJI.setMate(mate2);
            residualNetwork.addArc(i,residualArcIJ);
            residualNetwork.addArc(currentArc.getDestination(),residualArcJI);
        }
    }

    return residualNetwork;
}


void computeDistanceLabels(Adjacency_list& network,std::vector<pFPnode>& nodes)
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


void preProcess(Adjacency_list& network, std::vector<pFPnode>& nodes)
{
    //calcolo le distance label della rete
    computeDistanceLabels(network, nodes);
    //scorro tutti i nodi uscenti dalla sorgente s
    for(size_t i = 0; i<network.getAdjacency_lists()[0].size();i++)
    {
        //capacità massima dell'arco
        int flowAmount = network.getAdjacency_lists()[0][i].getCapacity();
        //saturo l'arco
        network.getAdjacency_lists()[0][i].setFlow(flowAmount);
        //aumento l'eccesso
        nodes[network.getAdjacency_lists()[0][i].getDestination()].setExcess(flowAmount);
    }
    //imposto d(s) = n
    nodes.back().setDistanceLabel(nodes.size());

}

void pushRelabel(Adjacency_list& network, std::vector<pFPnode>& nodes, size_t activeNode)
{
    //bool che indica la presenza di archi ammissibili dal nodo attivo
    bool hasAdmArc = 0;
    //scorro gli archi uscenti dal nodo attivo
    for(size_t i = 0; i<network.getAdjacency_lists()[activeNode].size() && !hasAdmArc; i++)
    {
        Arc current = network.getAdjacency_lists()[activeNode][i];
        //se l'arco i j è ammissibile, ovvero d(j)<=d(i)+1:
        if(nodes[current.getDestination()].getDistanceLabel() <= nodes[current.getOrigin()].getDistanceLabel() + 1)
        {
            hasAdmArc = 1;
            int newFlow = 0;

            //se il residuale è minore dell'eccesso di i:
            if(current.getResidual() <= nodes[current.getOrigin()].getExcess())
            {
                //aumento il flusso del residuale,saturandolo
                newFlow = network.getAdjacency_lists()[activeNode][i].getFlow() + current.getResidual();
            }
            else
            {
                //aumento il flusso di tutto l'eccesso di i
                newFlow = network.getAdjacency_lists()[activeNode][i].getFlow() + nodes[current.getOrigin()].getExcess();
            }
            //imposto il flusso nell'arco
            network.getAdjacency_lists()[activeNode][i].setFlow(newFlow);
            //devo impostare il flusso nel mate dell'arco, accedendo con [destination][mate] nella rete
            //devo aumentare l'eccesso nel nodo destinazione
            //devo
        }
    }

    if(!hasAdmArc)
    {
        //aggiorno la distance label di active node
    }
}


