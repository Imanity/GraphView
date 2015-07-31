#ifndef FTOPICGRAPH_H
#define FTOPICGRAPH_H

#include <vector>
#include "fgraph.h"
#include "Node/ftopicnode.h"
#include "Edge/fundirectededge.h"
using namespace std;

class FTopicGraph : public FGraph
{
public:
    vector<FTopicNode> topicNodes;
    vector<FUndirectedEdge> undirectedEdges;
public:
    FTopicGraph();
    virtual void readFile();
};

#endif // FTOPICGRAPH_H
