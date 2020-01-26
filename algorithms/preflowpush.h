#ifndef PREFLOWPUSH_H
#define PREFLOWPUSH_H

#include <data_structures/adjacency_list.h>
#include <data_structures/pfpnode.h>
#include <queue>

Adjacency_list convertToResidual(Adjacency_list network);

void computeDistanceLabels(Adjacency_list network,std::vector<pFPnode> nodes);

#endif // PREFLOWPUSH_H
