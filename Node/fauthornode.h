#ifndef FAUTHORNODE_H
#define FAUTHORNODE_H

#include "fnode.h"

class FAuthorNode : public FNode
{
public:
    int year;
    QString id;
    QString authorName;
    QString authorNameShort;
public:
    FAuthorNode();
    FAuthorNode(int nodeId, int year, QString id, QString authorName, QString authorNameShort);
};

#endif // FAUTHORNODE_H
