#ifndef PAPERCONFERENCEAUTHORWINDOW_H
#define PAPERCONFERENCEAUTHORWINDOW_H

#include <QMainWindow>
#include "Graph/fpaperconferenceauthorgraph.h"

namespace Ui {
class PaperConferenceAuthorWindow;
}

class PaperConferenceAuthorWindow : public QMainWindow
{
    Q_OBJECT

public:
    FPaperConferenceAuthorGraph graph;
    explicit PaperConferenceAuthorWindow(QWidget *parent = 0);
    ~PaperConferenceAuthorWindow();

private:
    Ui::PaperConferenceAuthorWindow *ui;
    void paintEvent(QPaintEvent *ev);
};

#endif // PAPERCONFERENCEAUTHORWINDOW_H
