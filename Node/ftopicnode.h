#ifndef FTOPICNODE_H
#define FTOPICNODE_H

#include <vector>
#include "fnode.h"
using namespace std;

class FTopicNode : public FNode
{
public:
    QString topicWords;
    QString topicDocuments;
public:
    FTopicNode();
    FTopicNode(int nodeId, QString topicWords, QString topicDocuments);
};

#endif // FTOPICNODE_H
