#ifndef FPAPERNODE_H
#define FPAPERNODE_H

#include "fnode.h"

class FPaperNode : FNode
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
};

#endif // FPAPERNODE_H
