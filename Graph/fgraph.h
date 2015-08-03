#ifndef FGRAPH_H
#define FGRAPH_H

#include <ogdf/energybased/FMMMLayout.h>
#include <ogdf/misclayout/BalloonLayout.h>
#include <ogdf/basic/Graph.h>
#include <ogdf/basic/GraphAttributes.h>
#include "Node/fnode.h"
using namespace ogdf;

class FGraph
{
public:
    int nodeNum;
    int maxConnectivity;
public:
    FGraph();
    virtual void readFile() = 0;
    virtual node getOgdfId(int nodeId) = 0;
    virtual FNode& getNode(int nodeId) = 0;
    virtual void resetStatus() = 0;
    virtual void getFmmmLayout() = 0;
    virtual void changeToFmmmLayout() = 0;
    virtual void setRandom() = 0;
    virtual void setCircle() = 0;
    virtual void setForm() = 0;
    virtual void getMaxConnectivity() = 0;
    virtual void saveLayout() = 0;
    virtual void loadLayout() = 0;
};

#endif // FGRAPH_H
