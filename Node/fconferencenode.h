#ifndef FCONFERENCENODE_H
#define FCONFERENCENODE_H

#include "fnode.h"

class FConferenceNode : public FNode
{
public:
    int year;
    char *id;
    char *conferenceName;
    char *conferenceNameShort;
public:
    FConferenceNode();
    FConferenceNode(int nodeId, int year, char *id, char *conferenceName, char *conferenceNameShort);
};

#endif // FCONFERENCENODE_H
