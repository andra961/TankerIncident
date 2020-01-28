#ifndef PREFLOWPUSH_H
#define PREFLOWPUSH_H

#include <data_structures/adjacency_list.h>
#include <data_structures/pfpnode.h>
#include <queue>
#include <iostream>
#include <fstream>

Adjacency_list convertToResidual(Adjacency_list& network);

bool hasActiveNodes(std::vector<pFPnode>& nodes);

size_t getHighestLabelActiveNode(std::vector<pFPnode>& nodes);

void computeDistanceLabels(Adjacency_list& network,std::vector<pFPnode>& nodes);

void preProcess(Adjacency_list& network, std::vector<pFPnode>& nodes);

void preFlowPush(Adjacency_list& network);

void writeResultsOnFile(Adjacency_list& network,std::string& path);

#endif // PREFLOWPUSH_H
