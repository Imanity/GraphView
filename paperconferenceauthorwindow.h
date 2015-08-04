#ifndef PAPERCONFERENCEAUTHORWINDOW_H
#define PAPERCONFERENCEAUTHORWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "Graph/fpaperconferenceauthorgraph.h"
#include "viewconst.h"
#include "forcebundle.h"

namespace Ui {
class PaperConferenceAuthorWindow;
}

class PaperConferenceAuthorWindow : public QMainWindow
{
    Q_OBJECT

private:
    int nodeAdjust, edgeAdjust;
    int minConnectivity;
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
    int theme;
    int language;
    ViewConst view;
    vector<double> operationX;
    vector<double> operationY;
    bool isOncePressed;

public:
    FPaperConferenceAuthorGraph graph;
    Forcebundle EdgeBundlingView;
    explicit PaperConferenceAuthorWindow(QWidget *parent = 0);
    ~PaperConferenceAuthorWindow();

private:
    Ui::PaperConferenceAuthorWindow *ui;
    void paintEvent(QPaintEvent *ev);
    bool event(QEvent *event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void getHighLight();
    void getGroupNodes();
    void resetGroupMove();
    void setPaperNode(int nodeId);
    void setConferenceNode(int nodeId);
    void setAuthorNode(int nodeId);
    void saveOperation();
    void loadOperation();
    void getEdgeBundling();

public slots:
    void onInitLayoutClicked();
    void onRandomLayoutClicked();
    void onFmmmLayoutClicked();
    void onCircleLayoutClicked();
    void onFormLayoutClicked();
    void timerDraw();
    void resetView();
    void adjustNode(int num);
    void adjustEdge(int num);
    void adjustconnectivity(int num);
    void loadLayout();
    void saveLayout();
    void setTheme(int theme);
    void setLanguage(int language);
    void showEdgeBundling();
};

#endif // PAPERCONFERENCEAUTHORWINDOW_H
