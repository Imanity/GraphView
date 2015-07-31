#ifndef FDIRECTEDEDGE_H
#define FDIRECTEDEDGE_H

#include "fedge.h"

class FDirectedEdge : public FEdge
{
public:
    FDirectedEdge();
    FDirectedEdge(int node1, int node2);
};

#endif // FDIRECTEDEDGE_H
