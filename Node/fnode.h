#ifndef FNODE_H
#define FNODE_H

#include <QString>
#include "ogdf/basic/Graph_d.h"
using namespace ogdf;

class FNode
{
public:
    int nodeId;                                         //点编号
    int viewColorR, viewColorG, viewColorB, viewColorA; //界面显示颜色
    QString viewLabel;                                  //界面显示标签
    double viewLayoutX, viewLayoutY, viewLayoutZ;       //预置界面显示位置
    double nowViewX, nowViewY;                          //当前显示位置
    double oldViewX, oldViewY;                          //旧显示位置
    double randomViewX, randomViewY;                    //随机布局
    double fmmmViewX, fmmmViewY;                        //energy-based布局
    double balloonViewX, balloonViewY;                  //balloon布局
    double circleViewX, circleViewY;                    //圆形均匀布局
    double formViewX, formViewY;                        //平铺布局
    node ogdfId;                                        //ogdf编号
    int connectivity;                                   //连通度
public:
    FNode();
    void setColor(int viewColorR, int viewColorG, int viewColorB, int viewColorA);
    void SetLabel(QString viewLabel, int viewLayoutX, int viewLayoutY, int viewLayoutZ);
};

#endif // FNODE_H
