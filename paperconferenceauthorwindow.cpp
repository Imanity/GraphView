#include <QPainter>
#include <QKeyEvent>
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
        p.drawEllipse(graph.paperNodes[i].nowViewX - 4, graph.paperNodes[i].nowViewY - 4, 8, 8);
    }
    p.setBrush(Qt::red);
    for(int i = 0; i < graph.authorNodes.size(); ++i)
    {
        p.drawEllipse(graph.authorNodes[i].nowViewX - 4, graph.authorNodes[i].nowViewY - 4, 8, 8);
    }
    p.setBrush(Qt::green);
    for(int i = 0; i < graph.conferenceNodes.size(); ++i)
    {
        p.drawEllipse(graph.conferenceNodes[i].nowViewX - 4, graph.conferenceNodes[i].nowViewY - 4, 8, 8);
    }
    for(int i = 0; i < graph.directedEdges.size(); ++i)
    {
        line1_X = graph.getNode(graph.directedEdges[i].node1).nowViewX;
        line1_Y = graph.getNode(graph.directedEdges[i].node1).nowViewY;
        line2_X = graph.getNode(graph.directedEdges[i].node2).nowViewX;
        line2_Y = graph.getNode(graph.directedEdges[i].node2).nowViewY;
        p.drawLine(line1_X, line1_Y, line2_X, line2_Y);
    }
}

bool PaperConferenceAuthorWindow::event(QEvent *event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if(keyEvent->key() == Qt::Key_Up)
        {
            graph.moveNodes(0);
        }
        if(keyEvent->key() == Qt::Key_Down)
        {
            graph.moveNodes(1);
        }
        if(keyEvent->key() == Qt::Key_Left)
        {
            graph.moveNodes(2);
        }
        if(keyEvent->key() == Qt::Key_Right)
        {
            graph.moveNodes(3);
        }
    }
    update();
    return QWidget::event(event);
}
