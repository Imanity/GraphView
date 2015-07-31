#ifndef FPAPERNODE_H
#define FPAPERNODE_H

#include "fnode.h"

class FPaperNode : public FNode
{
public:
    int year;
    char *authors;
    int dateFrom;
    char *id;
    int pageFrom;
    char *paperTitle;
    char *paperTitleShort;
public:
    FPaperNode();
    FPaperNode(int nodeId, int year, char *authors, int dateFrom, char *id,
               int pageFrom, char *paperTitle, char *paperTitleShort);
};

#endif // FPAPERNODE_H
