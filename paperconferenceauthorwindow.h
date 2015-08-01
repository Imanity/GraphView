#ifndef PAPERCONFERENCEAUTHORWINDOW_H
#define PAPERCONFERENCEAUTHORWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "Graph/fpaperconferenceauthorgraph.h"

namespace Ui {
class PaperConferenceAuthorWindow;
}

class PaperConferenceAuthorWindow : public QMainWindow
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

public:
    FPaperConferenceAuthorGraph graph;
    explicit PaperConferenceAuthorWindow(QWidget *parent = 0);
    ~PaperConferenceAuthorWindow();

private:
    Ui::PaperConferenceAuthorWindow *ui;
    void paintEvent(QPaintEvent *ev);
    bool event(QEvent *event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

public slots:
    void onInitLayoutClicked();
    void onRandomLayoutClicked();
    void onFmmmLayoutClicked();
    void onCircleLayoutClicked();
    void onFormLayoutClicked();
    void timerDraw();
};

#endif // PAPERCONFERENCEAUTHORWINDOW_H
