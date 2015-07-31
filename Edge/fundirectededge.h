#ifndef FUNDIRECTEDEDGE_H
#define FUNDIRECTEDEDGE_H

#include "fedge.h"

class FUndirectedEdge : public FEdge
{
public:
    double weight;
public:
    FUndirectedEdge();
};

#endif // FUNDIRECTEDEDGE_H
