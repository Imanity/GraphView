#ifndef TOPICWINDOW_H
#define TOPICWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "Graph/ftopicgraph.h"

namespace Ui {
class TopicWindow;
}

class TopicWindow : public QMainWindow
{
    Q_OBJECT

private:
    int timepast;
    QTimer* timer;
    int nowLayout;
    double changeSpeed;
    double zoomRate;
    double centerX, centerY;
    double shiftX, shiftY;
    double mouseX, mouseY;
    double pressX, pressY;
    double tmpX, tmpY;
    bool isPressed;
    bool isDraged;
    bool isCtrled;
    bool isGroupDraged;
    bool isGroupMove;
    double upBorder, downBorder, leftBorder, rightBorder;
    vector<int> groupNodes;
    vector<double> groupNodesTmpX;
    vector<double> groupNodesTmpY;
    bool isDisplayGroup;
    double highLightX, highLightY, highLightId;

public:
    FTopicGraph graph;
    explicit TopicWindow(QWidget *parent = 0);
    ~TopicWindow();

private:
    Ui::TopicWindow *ui;
    void paintEvent(QPaintEvent *ev);
    bool event(QEvent *event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void getHighLight();
    void getGroupNodes();
    void resetGroupMove();

public slots:
    void onRandomLayoutClicked();
    void onFmmmLayoutClicked();
    void onCircleLayoutClicked();
    void onFormLayoutClicked();
    void timerDraw();
};

#endif // TOPICWINDOW_H
