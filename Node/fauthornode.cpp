#include "fauthornode.h"

FAuthorNode::FAuthorNode()
{

}

FAuthorNode::FAuthorNode(int nodeId, int year, QString id, QString authorName, QString authorNameShort)
{
    this->nodeId = nodeId;
    this->year = year;
    this->id = id;
    this->authorName = authorName;
    this->authorNameShort = authorNameShort;
}
