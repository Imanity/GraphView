#ifndef FPAPERCONFERENCEAUTHORGRAPH_H
#define FPAPERCONFERENCEAUTHORGRAPH_H

#include <vector>
#include<QString>
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
    virtual FNode& getNode(int nodeId);
    virtual void resetStatus();
    virtual void getFmmmLayout();
    virtual void changeToFmmmLayout();
    virtual void setRandom();
    virtual void setCircle();
    virtual void setForm();
    virtual void getMaxConnectivity();
    QString getType(int nodeId);
    int getYear(int nodeId);
    QString getAuthors(int nodeId);
    int getDateFrom(int nodeId);
    QString getId(int nodeId);
    int getPageFrom(int nodeId);
    QString getPaperTitle(int nodeId);
    QString getPaperTitleShort(int nodeId);
    QString getConferenceName(int nodeId);
    QString getConferenceNameShort(int nodeId);
    QString getAuthorName(int nodeId);
    QString getAuthorNameShort(int nodeId);
    virtual void saveLayout();
    virtual void loadLayout();
};

#endif // FPAPERCONFERENCEAUTHORGRAPH_H
