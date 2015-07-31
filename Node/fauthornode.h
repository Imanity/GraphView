#ifndef FAUTHORNODE_H
#define FAUTHORNODE_H

#include "fnode.h"

class FAuthorNode : public FNode
{
public:
    int year;
    char *id;
    char *authorName;
    char *authorNameShort;
public:
    FAuthorNode();
    FAuthorNode(int nodeId, int year, char *id, char *authorName, char *authorNameShort);
};

#endif // FAUTHORNODE_H
