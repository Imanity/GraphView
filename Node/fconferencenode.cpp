#include "fconferencenode.h"

FConferenceNode::FConferenceNode()
{

}

FConferenceNode::FConferenceNode(int nodeId, int year, QString id, QString conferenceName, QString conferenceNameShort)
{
    this->nodeId = nodeId;
    this->year = year;
    this->id = id;
    this->conferenceName = conferenceName;
    this->conferenceNameShort = conferenceNameShort;
    connectivity = 0;
}
