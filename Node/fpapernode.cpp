#include "fpapernode.h"

FPaperNode::FPaperNode()
{

}

FPaperNode::FPaperNode(int nodeId, int year, QString authors, int dateFrom, QString id, int pageFrom, QString paperTitle, QString paperTitleShort)
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
