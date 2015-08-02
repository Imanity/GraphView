#ifndef FPAPERNODE_H
#define FPAPERNODE_H

#include "fnode.h"

class FPaperNode : public FNode
{
public:
    int year;
    QString authors;
    int dateFrom;
    QString id;
    int pageFrom;
    QString paperTitle;
    QString paperTitleShort;
public:
    FPaperNode();
    FPaperNode(int nodeId, int year, QString authors, int dateFrom, QString id,
               int pageFrom, QString paperTitle, QString paperTitleShort);
};

#endif // FPAPERNODE_H
