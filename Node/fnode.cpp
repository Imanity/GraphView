#include "fnode.h"

FNode::FNode()
{

}

void FNode::setColor(int viewColorR, int viewColorG, int viewColorB, int viewColorA)
{
    this->viewColorR = viewColorR;
    this->viewColorG = viewColorG;
    this->viewColorB = viewColorB;
    this->viewColorA = viewColorA;
}

void FNode::SetLabel(QString viewLabel, int viewLayoutX, int viewLayoutY, int viewLayoutZ)
{
    this->viewLabel = viewLabel;
    this->viewLayoutX = viewLayoutX;
    this->viewLayoutY = viewLayoutY;
    this->viewLayoutZ = viewLayoutZ;
}
