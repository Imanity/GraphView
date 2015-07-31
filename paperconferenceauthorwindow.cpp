#include <QPainter>
#include "paperconferenceauthorwindow.h"
#include "ui_paperconferenceauthorwindow.h"

PaperConferenceAuthorWindow::PaperConferenceAuthorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PaperConferenceAuthorWindow)
{
    ui->setupUi(this);
    graph.readFile();
}

PaperConferenceAuthorWindow::~PaperConferenceAuthorWindow()
{
    delete ui;
}

void PaperConferenceAuthorWindow::paintEvent(QPaintEvent *ev)
{
    QPainter p(this);
    //画点
    for(int i = 0; i < graph.paperNodes.size(); ++i)
    {
        p.drawPoint(graph.paperNodes[i].viewLayoutX, graph.paperNodes[i].viewLayoutY);
    }
    for(int i = 0; i < graph.conferenceNodes.size(); ++i)
    {
        p.drawPoint(graph.conferenceNodes[i].viewLayoutX, graph.conferenceNodes[i].viewLayoutY);
    }
    for(int i = 0; i < graph.authorNodes.size(); ++i)
    {
        p.drawPoint(graph.authorNodes[i].viewLayoutX, graph.authorNodes[i].viewLayoutY);
    }
    //画边
    for(int i = 0; i < graph.directedEdges.size(); ++i)
    {
        int node1_X = 0, node1_Y = 0;
        int node2_X = 0, node2_Y = 0;
        //寻找node1
        for(int j = 0; j < graph.paperNodes.size(); ++j)
        {
            if(graph.paperNodes[j].nodeId == graph.directedEdges[i].node1)
            {
                node1_X = graph.paperNodes[j].viewLayoutX;
                node1_Y = graph.paperNodes[j].viewLayoutY;
            }
        }
        for(int j = 0; j < graph.conferenceNodes.size(); ++j)
        {
            if(graph.conferenceNodes[j].nodeId == graph.directedEdges[i].node1)
            {
                node1_X = graph.conferenceNodes[j].viewLayoutX;
                node1_Y = graph.conferenceNodes[j].viewLayoutY;
            }
        }
        for(int j = 0; j < graph.authorNodes.size(); ++j)
        {
            if(graph.authorNodes[j].nodeId == graph.directedEdges[i].node1)
            {
                node1_X = graph.authorNodes[j].viewLayoutX;
                node1_Y = graph.authorNodes[j].viewLayoutY;
            }
        }
        //寻找node2
        for(int j = 0; j < graph.paperNodes.size(); ++j)
        {
            if(graph.paperNodes[j].nodeId == graph.directedEdges[i].node2)
            {
                node2_X = graph.paperNodes[j].viewLayoutX;
                node2_Y = graph.paperNodes[j].viewLayoutY;
            }
        }
        for(int j = 0; j < graph.conferenceNodes.size(); ++j)
        {
            if(graph.conferenceNodes[j].nodeId == graph.directedEdges[i].node2)
            {
                node2_X = graph.conferenceNodes[j].viewLayoutX;
                node2_Y = graph.conferenceNodes[j].viewLayoutY;
            }
        }
        for(int j = 0; j < graph.authorNodes.size(); ++j)
        {
            if(graph.authorNodes[j].nodeId == graph.directedEdges[i].node2)
            {
                node2_X = graph.authorNodes[j].viewLayoutX;
                node2_Y = graph.authorNodes[j].viewLayoutY;
            }
        }
        p.drawLine(node1_X, node1_Y, node2_X, node2_Y);
    }
}
