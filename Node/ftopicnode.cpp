#include "ftopicnode.h"

FTopicNode::FTopicNode()
{

}

FTopicNode::FTopicNode(int nodeId, QString topicWords, QString topicDocuments)
{
    this->nodeId = nodeId;
    this->topicWords = topicWords;
    this->topicDocuments = topicDocuments;
    connectivity = 0;
}
