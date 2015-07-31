#include <QPainter>
#include "paperconferenceauthorwindow.h"
#include "ui_paperconferenceauthorwindow.h"

PaperConferenceAuthorWindow::PaperConferenceAuthorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PaperConferenceAuthorWindow)
{
    ui->setupUi(this);
    this->resize(500, 500);
    graph.readFile();
}

PaperConferenceAuthorWindow::~PaperConferenceAuthorWindow()
{
    delete ui;
}

void PaperConferenceAuthorWindow::paintEvent(QPaintEvent *ev)
{
    QPainter p(this);
    int line1_X, line2_X, line1_Y, line2_Y;
    p.setBrush(Qt::yellow);
    for(int i = 0; i < graph.paperNodes.size(); ++i)
    {
        p.drawEllipse(graph.paperNodes[i].viewLayoutX - 4, graph.paperNodes[i].viewLayoutY - 4, 8, 8);
    }
    p.setBrush(Qt::red);
    for(int i = 0; i < graph.authorNodes.size(); ++i)
    {
        p.drawEllipse(graph.authorNodes[i].viewLayoutX - 4, graph.authorNodes[i].viewLayoutY - 4, 8, 8);
    }
    p.setBrush(Qt::green);
    for(int i = 0; i < graph.conferenceNodes.size(); ++i)
    {
        p.drawEllipse(graph.conferenceNodes[i].viewLayoutX - 4, graph.conferenceNodes[i].viewLayoutY - 4, 8, 8);
    }
    for(int i = 0; i < graph.directedEdges.size(); ++i)
    {
        line1_X = graph.getNode(graph.directedEdges[i].node1).viewLayoutX;
        line1_Y = graph.getNode(graph.directedEdges[i].node1).viewLayoutY;
        line2_X = graph.getNode(graph.directedEdges[i].node2).viewLayoutX;
        line2_Y = graph.getNode(graph.directedEdges[i].node2).viewLayoutY;
        p.drawLine(line1_X, line1_Y, line2_X, line2_Y);
    }
}
