#ifndef FTOPICNODE_H
#define FTOPICNODE_H

#include <vector>
#include "fnode.h"
using namespace std;

class FTopicNode : public FNode
{
public:
    char *topicWords;
    vector<int> topicDocuments;
public:
    FTopicNode();
};

#endif // FTOPICNODE_H
