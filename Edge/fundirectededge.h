#ifndef FUNDIRECTEDEDGE_H
#define FUNDIRECTEDEDGE_H

#include "fedge.h"

class FUndirectedEdge : public FEdge
{
public:
    double weight;
public:
    FUndirectedEdge();
    FUndirectedEdge(int node1, int node2, double weight);
};

#endif // FUNDIRECTEDEDGE_H
