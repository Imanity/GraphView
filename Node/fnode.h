#ifndef FNODE_H
#define FNODE_H


class FNode
{
public:
    int nodeId;                                         //点编号
    int viewColorR, viewColorG, viewColorB, viewColorA; //界面显示颜色
    char *viewLabel;                                    //界面显示标签
    int viewLayoutX, viewLayoutY, viewLayoutZ;          //界面显示位置
public:
    FNode();
};

#endif // FNODE_H
