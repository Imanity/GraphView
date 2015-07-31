#include "fconferencenode.h"

FConferenceNode::FConferenceNode()
{

}

FConferenceNode::FConferenceNode(int nodeId, int year, char *id, char *conferenceName, char *conferenceNameShort)
{
    this->nodeId = nodeId;
    this->year = year;
    this->id = id;
    this->conferenceName = conferenceName;
    this->conferenceNameShort = conferenceNameShort;
}
