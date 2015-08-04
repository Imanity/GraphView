#ifndef VIEWCONST_H
#define VIEWCONST_H

#include <QColor>
#include <QString>

class ViewConst
{
public:
    QColor backGroundColor[2];
    QColor directedEdgeColor[2];
    QColor unDirectedEdgeColor[2];
    QColor labelColor[2];
    QString status[2];
    QString dragStatus[2];
    QString label1[2];
    QString label2[2];
    QString label3[2];
    QString label4[2];
    QString label5[2];
    QString group1[2];
    QString group2[2];
    QString group3[2];
    QString Radio1[2];
    QString Radio2[2];
    QString Radio3[2];
    QString Radio4[2];
    QString Button1[2];
    QString Button2[2];
    QString Button3[2];
    QString Button4[2];
public:
    ViewConst();
};

#endif // VIEWCONST_H
