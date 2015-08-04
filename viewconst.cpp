#include "viewconst.h"

ViewConst::ViewConst()
{
    backGroundColor[0] = Qt::white;
    backGroundColor[1] = Qt::black;
    directedEdgeColor[0] = QColor(100, 100, 100);
    directedEdgeColor[1] = QColor(0, 255, 0);
    unDirectedEdgeColor[0] = QColor(0, 0, 0);
    unDirectedEdgeColor[1] = QColor(0, 255, 0);
    labelColor[0] = Qt::black;
    labelColor[1] = Qt::white;
    status[0] = QStringLiteral("按下Ctrl键以使用扩展功能");
    status[1] = "Press Ctrl to activate extra function.";
    dragStatus[0] = QStringLiteral("拖动以框选节点，单击节点以查看信息");
    dragStatus[1] = "Drag to select nodes. Press the node to edit it.";
    label1[0] = QStringLiteral("节点筛选：");
    label1[1] = "Node Select:";
    label2[0] = QStringLiteral("点半径：");
    label2[1] = "Node Radius:";
    label3[0] = QStringLiteral("线宽度：");
    label3[1] = "Edge Width:";
    label4[0] = QStringLiteral("视觉主题：");
    label4[1] = "Theme:";
    label5[0] = QStringLiteral("文字语言：");
    label5[1] = "Language:";
    group1[0] = QStringLiteral("选择布局");
    group1[1] = "Select layout";
    group2[0] = QStringLiteral("视图设置");
    group2[1] = "View Setting";
    group3[0] = QStringLiteral("Node信息");
    group3[1] = "Node Info";
    Radio1[0] = QStringLiteral("随机布局");
    Radio1[1] = "Random Layout";
    Radio2[0] = QStringLiteral("圆形均匀布局");
    Radio2[1] = "Circular Layout";
    Radio3[0] = QStringLiteral("平铺布局");
    Radio3[1] = "Grid Layout";
    Radio4[0] = QStringLiteral("初始布局");
    Radio4[1] = "Initial Layout";
    Button1[0] = QStringLiteral("保存布局");
    Button1[1] = "Save Layout";
    Button2[0] = QStringLiteral("读取布局");
    Button2[1] = "Load Layout";
    Button3[0] = QStringLiteral("恢复视图");
    Button3[1] = "recover Layout";
}
