#include "fauthornode.h"

FAuthorNode::FAuthorNode()
{

}

FAuthorNode::FAuthorNode(int nodeId, int year, char *id, char *authorName, char *authorNameShort)
{
    this->nodeId = nodeId;
    this->year = year;
    this->id = id;
    this->authorName = authorName;
    this->authorNameShort = authorNameShort;
}
