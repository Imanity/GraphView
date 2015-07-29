#include "fpapernode.h"

FPaperNode::FPaperNode()
{

}

FPaperNode::FPaperNode(int nodeId, int year, char *authors, int dateFrom, char *id, int pageFrom, char *paperTitle, char *paperTitleShort)
{
    this->nodeId = nodeId;
    this->year = year;
    this->authors = authors;
    this->dateFrom = dateFrom;
    this->id = id;
    this->pageFrom = pageFrom;
    this->paperTitle = paperTitle;
    this->paperTitleShort = paperTitleShort;
}
