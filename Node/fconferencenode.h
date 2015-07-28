#ifndef FCONFERENCENODE_H
#define FCONFERENCENODE_H

#include "fnode.h"

class FConferenceNode : FNode
{
public:
    int year;
    char *id;
    char *conferenceName;
    char *conferenceNameShort;
public:
    FConferenceNode();
};

#endif // FCONFERENCENODE_H
