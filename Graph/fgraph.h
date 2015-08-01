#ifndef FGRAPH_H
#define FGRAPH_H

#include <ogdf/energybased/FMMMLayout.h>
#include <ogdf/basic/Graph.h>
#include <ogdf/basic/GraphAttributes.h>
#include "Node/fnode.h"
using namespace ogdf;

class FGraph
{
public:
    FGraph();
    virtual void readFile() = 0;
    virtual node getOgdfId(int nodeId) = 0;
    virtual FNode getNode(int nodeId) = 0;
    virtual void resetStatus() = 0;
    virtual void moveNodes(int direction) = 0;
};

#endif // FGRAPH_H
