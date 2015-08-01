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
    virtual node getOgdfId(int nodeId);
    virtual FNode getNode(int nodeId);
    virtual void resetStatus();
    virtual void moveNodes(int direction);
    virtual void getFmmmLayout();
    virtual void changeToFmmmLayout();
};

#endif // FPAPERCONFERENCEAUTHORGRAPH_H
