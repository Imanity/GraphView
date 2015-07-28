#ifndef FAUTHORNODE_H
#define FAUTHORNODE_H

#include "fnode.h"

class FAuthorNode : FNode
{
public:
    int year;
    char *id;
    char *authorName;
    char *authorNameShort;
public:
    FAuthorNode();
};

#endif // FAUTHORNODE_H
