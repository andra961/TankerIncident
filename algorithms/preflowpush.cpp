#include "preflowpush.h"

Adjacency_list convertToResidual(Adjacency_list& network)
{

    Adjacency_list residualNetwork = Adjacency_list(network.getNNodes(),network.getSource(),network.getSink());

    for(size_t i = 0; i<network.getAdjacency_lists().size(); i++)
    {
        for(size_t j = 0; j<network.getAdjacency_lists()[i].size(); j++)
        {
            Arc currentArc = network.getAdjacency_lists()[i][j];
            Arc residualArcIJ = Arc(1,currentArc.getOrigin(),currentArc.getDestination(),currentArc.getCapacity());
            Arc residualArcJI = Arc(0,currentArc.getDestination(),currentArc.getOrigin(),currentArc.getCapacity());

            //inizializzo il mate di ij, che sarà l'indice dove ji si trova nella lista di adiacenza di j
            size_t mate1 = residualNetwork.getAdjacency_lists()[currentArc.getDestination()].size();
            //inizializzo il mate di ji, che sarà l'indice dove ij si trova nella lista di adiacenza di i
            size_t mate2 = residualNetwork.getAdjacency_lists()[currentArc.getOrigin()].size();
            residualArcIJ.setMate(mate1);
            residualArcJI.setMate(mate2);
            residualNetwork.addArc(currentArc.getOrigin(),residualArcIJ);
            residualNetwork.addArc(currentArc.getDestination(),residualArcJI);
        }
    }

    return residualNetwork;
}

bool hasActiveNodes(std::vector<pFPnode>& nodes,size_t source, size_t sink)
{
    bool hasActiveNodes = 0;

    for(size_t i = 0;i < nodes.size();i++)
    {
        if(nodes[i].getExcess() > 0 && i != source && i != sink) hasActiveNodes = 1;
    }

    return hasActiveNodes;
}

size_t getHighestLabelActiveNode(std::vector<pFPnode>& nodes,size_t source, size_t sink)
{
    int currentDistance = 0;
    size_t activeNode = 0;

    for(size_t i = 0;i < nodes.size();i++)
    {
        if(nodes[i].getExcess() > 0 && i != source && i != sink && nodes[i].getDistanceLabel() > currentDistance)
        {
            currentDistance = nodes[i].getDistanceLabel();
            activeNode = i;
        }
    }

    return activeNode;
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
    marks[network.getSink()] = 1;
    //setto la sua distance label a 0
    nodes[network.getSink()].setDistanceLabel(0);
    //inserisco il pozzo nella coda
    list.push(network.getSink());
    //finchè la coda ha elementi:
    while(list.size()>0)
    {
        //prendo il primo nodo nella coda
        int node = list.front();

        //scorro gli archi uscenti dal nodo node
        for(size_t i = 0; i<network.getAdjacency_lists()[node].size(); i++)
        {
            //l'arco uscente dal nodo node
            Arc outgoingArc = network.getAdjacency_lists()[node][i];
            //ottengo il suo mate, che sarà quindi entrante in node
            Arc arc = network.getAdjacency_lists()[outgoingArc.getDestination()][outgoingArc.getMate()];

            if(arc.getResidualType() && arc.getDestination() == node && !marks[arc.getOrigin()])
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
        //rimuovo il primo nodo dalla coda
        list.pop();
    }
}


void preProcess(Adjacency_list& network, std::vector<pFPnode>& nodes)
{
    //calcolo le distance label della rete
    computeDistanceLabels(network, nodes);

    size_t source = network.getSource();

    //scorro tutti i nodi uscenti dalla sorgente s
    for(size_t i = 0; i < network.getAdjacency_lists()[source].size(); i++)
    {
        Arc currentArc = network.getAdjacency_lists()[source][i];
        //capacità massima dell'arco
        double flowAmount = network.getAdjacency_lists()[source][i].getCapacity();
        //saturo l'arco
        network.getAdjacency_lists()[source][i].pushFlow(flowAmount);
        network.getAdjacency_lists()[currentArc.getDestination()][currentArc.getMate()].setFlow(flowAmount);
        //aumento l'eccesso
        nodes[network.getAdjacency_lists()[source][i].getDestination()].setExcess(flowAmount);
    }

    //imposto d(s) = n
    nodes[source].setDistanceLabel(network.getNNodes());

}

void pushRelabel(Adjacency_list& network, std::vector<pFPnode>& nodes, size_t activeNode)
{
    //bool che indica la presenza di archi ammissibili uscenti dal nodo attivo
    bool hasAdmArc = 0;
    //scorro gli archi uscenti dal nodo attivo
    for(size_t i = 0; i<network.getAdjacency_lists()[activeNode].size() && !hasAdmArc; i++)
    {
        Arc current = network.getAdjacency_lists()[activeNode][i];
        //se l'arco i j è ammissibile, ovvero d(j)<=d(i)+1:
        if(nodes[current.getDestination()].getDistanceLabel() + 1 == nodes[current.getOrigin()].getDistanceLabel() && current.getResidual() > 0)
        {
            //ho trovato un arco ammissibile
            hasAdmArc = 1;
            //il flusso corrente nell'arco ammissibile
            double oldFlow = network.getAdjacency_lists()[activeNode][i].getFlow();
            double deltaFlow = 0;
            double newFlow = 0;

            //se il residuale è minore dell'eccesso di i:
            if(current.getResidual() <= nodes[current.getOrigin()].getExcess())
            {
                //la quantità di cui aumentare il flusso sarà uguale al residuale,saturandolo
                deltaFlow = current.getResidual();
            }
            else
            {
                //la quantità di cui aumentare il flusso sarà uguale all'eccesso,saturandolo
                deltaFlow = nodes[current.getOrigin()].getExcess();
            }
            //il flusso aumentato
            if(current.getResidualType())
            {
                newFlow = oldFlow + deltaFlow;
            }
            else
            {
                newFlow = oldFlow - deltaFlow;
            }

            //imposto il flusso nell'arco

            //network.getAdjacency_lists()[activeNode][i].setFlow(newFlow);

            network.getAdjacency_lists()[activeNode][i].pushFlow(deltaFlow);
            //imposto il flusso nel mate dell'arco, accedendo con [destination][mate] nella rete

            network.getAdjacency_lists()[current.getDestination()][current.getMate()].setFlow(newFlow);

            //network.getAdjacency_lists()[current.getDestination()][current.getMate()].pushFlow(deltaFlow);


            //diminuisco l'eccesso del nodo origine dell'ammontare del flusso
            nodes[current.getOrigin()].decreaseExcess(deltaFlow);
            //aumento l'eccesso del nodo destinazione dell'ammontare del flusso
            nodes[current.getDestination()].increaseExcess(deltaFlow);
        }
    }
    //se il noto attivo non ha archi ammissibili
    if(!hasAdmArc)
    {
        //aggiorno la distance label di active node
        int minDistance = 10000;
        int currentDistance;

        //scorro gli archi adiacenti
        for(size_t i = 0;i < network.getAdjacency_lists()[activeNode].size();i++)
        {
            currentDistance = nodes[network.getAdjacency_lists()[activeNode][i].getDestination()].getDistanceLabel();
            //salvo la minima distance label della destinazione dell'arco
            if(currentDistance < minDistance && network.getAdjacency_lists()[activeNode][i].getResidual() > 0)
            {
                minDistance = currentDistance;
            }
        }
        //setto la distance label con la distanza minima
        nodes[activeNode].setDistanceLabel(minDistance+1);
    }
}

double preFlowPush(Adjacency_list& residualNetwork)
{
    std::vector<pFPnode> nodes;
    nodes.resize(residualNetwork.getNNodes());

    preProcess(residualNetwork,nodes);


    while(hasActiveNodes(nodes,residualNetwork.getSource(),residualNetwork.getSink()))
    {
        pushRelabel(residualNetwork,nodes,getHighestLabelActiveNode(nodes,residualNetwork.getSource(),residualNetwork.getSink()));
    }

    //restituisco il max flow
    return nodes[residualNetwork.getSink()].getExcess();
}

void writePreFlowResultsOnFile(Adjacency_list& network,double maxFlow,std::string& path,const double& time)
{
    std::ofstream myfile (path);

    myfile << "i,      j,      xij";
    myfile << "\n\n";

    for(size_t i = 0; i<network.getAdjacency_lists().size(); i++)
    {
        for(size_t j = 0; j<network.getAdjacency_lists()[i].size(); j++)
        {

            Arc currentArc = network.getAdjacency_lists()[i][j];
            if(currentArc.getResidualType() && currentArc.getFlow() > 0)
            {
                myfile << currentArc.getOrigin() + 1 << "\t" << currentArc.getDestination() + 1 << "\t" << currentArc.getFlow() << "\n\n";
            }
        }
    }

    myfile << "\n\n";

    myfile << "Il flusso massimo passante per la rete è:" << maxFlow;

    myfile << "\n\nIl tempo impiegato per l'esecuzione è:" << time;

    myfile << "\n\n\n";

    myfile << "　 　　　　　　　 　　　　　 /ﾟ　　　　。";
    myfile << "\n" << "　　　 　 　 　 　　　　　 ／　．　　ﾟ";
    myfile << "\n" << "　　　　　　　　　　　,　'　　　　。　　・";
    myfile << "\n" << "` ー　 ＿ 　 - 　'　　　゜";
    myfile << "\n" << "。　　　　　　　．　　　　　　。　　ﾟ";
    myfile << "\n" << "　　　　：　　　　　。";
    myfile << "\n" << "ﾟ　　　　　　　　　　　　　．";
    myfile << "\n" << "　 ヾ冖ﾌ 　   ヾス";
    myfile << "\n" << "　　 [,]　　　 []";
    myfile << "\n" << "　　 |.|　 /|,ィ.!";
    myfile << "\n" << ".　　 ! }.r`j7!j";
    myfile << "\n" << "　　　 !｀､亠 {}";
    myfile << "\n" << "　　　  } / _,/,";
    myfile << "\n" << "　　　  ヽｼ_,-i";
    myfile << "\n" << "　　 　 /`´~ﾊﾞ}";
    myfile << "\n" << ".　　　/　　　 j";
    myfile << "\n" << "　 　 ∧　''/`, ｲ";
    myfile << "\n" << "　　　!　ヽ '/|_ j";
    myfile << "\n" << "　　/ ＼,/　 }＼,!";
    myfile << "\n" << "　 .ｧ､ヽｨ 　  <`-ｲ";
    myfile << "\n" << ".　 |.`iT. 　 ヽ　j";
    myfile << "\n" << "　　＼||' 　　　 `'";

    myfile.close();
}


