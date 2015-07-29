#ifndef FPAPERCONFERENCEAUTHORGRAPH_H
#define FPAPERCONFERENCEAUTHORGRAPH_H

#include <vector>
#include "fgraph.h"
#include "Node/fpapernode.h"
#include "Node/fconferencenode.h"
#include "Node/fauthornode.h"
#include "Edge/fdirectededge.h"
using namespace std;

class FPaperConferenceAuthorGraph : FGraph
{
public:
    vector<FPaperNode> paperNodes;
    vector<FConferenceNode> conferenceNodes;
    vector<FAuthorNode> authorNodes;
    vector<FDirectedEdge> directedEdges;
public:
    FPaperConferenceAuthorGraph();
    virtual void readFile();
};

#endif // FPAPERCONFERENCEAUTHORGRAPH_H
