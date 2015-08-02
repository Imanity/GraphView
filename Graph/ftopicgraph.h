#ifndef FTOPICGRAPH_H
#define FTOPICGRAPH_H

#include <vector>
#include <QString>
#include "fgraph.h"
#include "Node/ftopicnode.h"
#include "Edge/fundirectededge.h"
using namespace std;

class FTopicGraph : public FGraph
{
public:
    vector<FTopicNode> topicNodes;
    vector<FUndirectedEdge> undirectedEdges;
    Graph graphView;
    GraphAttributes GA;
public:
    FTopicGraph();
    virtual void readFile();
    virtual node getOgdfId(int nodeId);
    virtual FNode& getNode(int nodeId);
    virtual void resetStatus();
    virtual void getFmmmLayout();
    virtual void changeToFmmmLayout();
    virtual void setRandom();
    virtual void setCircle();
    virtual void setForm();
    QString getTopicWords(int nodeId);
    QString getTopicDocuments(int nodeId);
};

#endif // FTOPICGRAPH_H
