#ifndef FCONFERENCENODE_H
#define FCONFERENCENODE_H

#include "fnode.h"

class FConferenceNode : public FNode
{
public:
    int year;
    QString id;
    QString conferenceName;
    QString conferenceNameShort;
public:
    FConferenceNode();
    FConferenceNode(int nodeId, int year, QString id, QString conferenceName, QString conferenceNameShort);
};

#endif // FCONFERENCENODE_H
