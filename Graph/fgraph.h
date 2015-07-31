#ifndef FGRAPH_H
#define FGRAPH_H

#include <ogdf/energybased/FMMMLayout.h>
#include <ogdf/basic/Graph.h>
#include <ogdf/basic/GraphAttributes.h>
using namespace ogdf;

class FGraph
{
public:
    FGraph();
    virtual void readFile() = 0;
};

#endif // FGRAPH_H
