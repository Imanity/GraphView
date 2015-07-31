#ifndef FPAPERCONFERENCEAUTHORGRAPH_H
#define FPAPERCONFERENCEAUTHORGRAPH_H

#include <vector>
#include "fgraph.h"
#include "Node/fpapernode.h"
#include "Node/fconferencenode.h"
#include "Node/fauthornode.h"
#include "Edge/fdirectededge.h"
using namespace std;

class FPaperConferenceAuthorGraph : public FGraph
{
public:
    vector<FPaperNode> paperNodes;
    vector<FConferenceNode> conferenceNodes;
    vector<FAuthorNode> authorNodes;
    vector<FDirectedEdge> directedEdges;
    Graph graphView;
    GraphAttributes GA;
public:
    FPaperConferenceAuthorGraph();
    virtual void readFile();
    node getOgdfId(int nodeId);
    FNode getNode(int nodeId);
};

#endif // FPAPERCONFERENCEAUTHORGRAPH_H
