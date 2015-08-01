#ifndef FNODE_H
#define FNODE_H

#include "ogdf/basic/Graph_d.h"
using namespace ogdf;

class FNode
{
public:
    int nodeId;                                         //点编号
    int viewColorR, viewColorG, viewColorB, viewColorA; //界面显示颜色
    char *viewLabel;                                    //界面显示标签
    int viewLayoutX, viewLayoutY, viewLayoutZ;          //预置界面显示位置
    int nowViewX, nowViewY;                             //当前显示位置
    int oldViewX, oldViewY;                             //旧显示位置
    int fmmmViewX, fmmmViewY;                           //energy-based布局
    node ogdfId;                                        //ogdf编号
public:
    FNode();
    void setColor(int viewColorR, int viewColorG, int viewColorB, int viewColorA);
    void SetLabel(char *viewLabel, int viewLayoutX, int viewLayoutY, int viewLayoutZ);
};

#endif // FNODE_H
