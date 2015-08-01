#include <QPainter>
#include <QKeyEvent>
#include "paperconferenceauthorwindow.h"
#include "ui_paperconferenceauthorwindow.h"

PaperConferenceAuthorWindow::PaperConferenceAuthorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PaperConferenceAuthorWindow)
{
    nowLayout = 1;
    timepast = 0;
    changeSpeed = 12.0;
    timer = new QTimer(this);
    ui->setupUi(this);
    graph.readFile();
    connect(timer, SIGNAL(timeout()),this, SLOT(timerDraw()));
    connect(ui->initLayoutButton, SIGNAL(clicked()), this, SLOT(onInitLayoutClicked()));
    connect(ui->randomLayoutButton, SIGNAL(clicked()), this, SLOT(onRandomLayoutClicked()));
    connect(ui->FmmmLayoutButton, SIGNAL(clicked()), this, SLOT(onFmmmLayoutClicked()));
}

PaperConferenceAuthorWindow::~PaperConferenceAuthorWindow()
{
    delete ui;
}

void PaperConferenceAuthorWindow::paintEvent(QPaintEvent *ev)
{
    QPainter p(this);
    int line1_X, line2_X, line1_Y, line2_Y;
    p.setPen(QColor(100, 100, 100));
    p.setBrush(Qt::yellow);
    for(int i = 0; i < graph.directedEdges.size(); ++i)
    {
        line1_X = graph.getNode(graph.directedEdges[i].node1).nowViewX;
        line1_Y = graph.getNode(graph.directedEdges[i].node1).nowViewY;
        line2_X = graph.getNode(graph.directedEdges[i].node2).nowViewX;
        line2_Y = graph.getNode(graph.directedEdges[i].node2).nowViewY;
        p.drawLine(line1_X, line1_Y, line2_X, line2_Y);
    }
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

void PaperConferenceAuthorWindow::timerDraw()
{
    timepast++;
    switch(nowLayout)
    {
    case 1:
        for(int i = 0; i < graph.paperNodes.size(); ++i)
        {
            graph.paperNodes[i].nowViewX = (graph.paperNodes[i].viewLayoutX - graph.paperNodes[i].oldViewX) / changeSpeed * timepast + graph.paperNodes[i].oldViewX;
            graph.paperNodes[i].nowViewY = (graph.paperNodes[i].viewLayoutY - graph.paperNodes[i].oldViewY) / changeSpeed * timepast + graph.paperNodes[i].oldViewY;
        }
        for(int i = 0; i < graph.authorNodes.size(); ++i)
        {
            graph.authorNodes[i].nowViewX = (graph.authorNodes[i].viewLayoutX - graph.authorNodes[i].oldViewX) / changeSpeed * timepast + graph.authorNodes[i].oldViewX;
            graph.authorNodes[i].nowViewY = (graph.authorNodes[i].viewLayoutY - graph.authorNodes[i].oldViewY) / changeSpeed * timepast + graph.authorNodes[i].oldViewY;
        }
        for(int i = 0; i < graph.conferenceNodes.size(); ++i)
        {
            graph.conferenceNodes[i].nowViewX = (graph.conferenceNodes[i].viewLayoutX - graph.conferenceNodes[i].oldViewX) / changeSpeed * timepast + graph.conferenceNodes[i].oldViewX;
            graph.conferenceNodes[i].nowViewY = (graph.conferenceNodes[i].viewLayoutY - graph.conferenceNodes[i].oldViewY) / changeSpeed * timepast + graph.conferenceNodes[i].oldViewY;
        }
        break;
    case 2:
        for(int i = 0; i < graph.paperNodes.size(); ++i)
        {
            graph.paperNodes[i].nowViewX = (graph.paperNodes[i].randomViewX - graph.paperNodes[i].oldViewX) / changeSpeed * timepast + graph.paperNodes[i].oldViewX;
            graph.paperNodes[i].nowViewY = (graph.paperNodes[i].randomViewY - graph.paperNodes[i].oldViewY) / changeSpeed * timepast + graph.paperNodes[i].oldViewY;
        }
        for(int i = 0; i < graph.authorNodes.size(); ++i)
        {
            graph.authorNodes[i].nowViewX = (graph.authorNodes[i].randomViewX - graph.authorNodes[i].oldViewX) / changeSpeed * timepast + graph.authorNodes[i].oldViewX;
            graph.authorNodes[i].nowViewY = (graph.authorNodes[i].randomViewY - graph.authorNodes[i].oldViewY) / changeSpeed * timepast + graph.authorNodes[i].oldViewY;
        }
        for(int i = 0; i < graph.conferenceNodes.size(); ++i)
        {
            graph.conferenceNodes[i].nowViewX = (graph.conferenceNodes[i].randomViewX - graph.conferenceNodes[i].oldViewX) / changeSpeed * timepast + graph.conferenceNodes[i].oldViewX;
            graph.conferenceNodes[i].nowViewY = (graph.conferenceNodes[i].randomViewY - graph.conferenceNodes[i].oldViewY) / changeSpeed * timepast + graph.conferenceNodes[i].oldViewY;
        }
        break;
    case 3:
        for(int i = 0; i < graph.paperNodes.size(); ++i)
        {
            graph.paperNodes[i].nowViewX = (graph.paperNodes[i].fmmmViewX - graph.paperNodes[i].oldViewX) / changeSpeed * timepast + graph.paperNodes[i].oldViewX;
            graph.paperNodes[i].nowViewY = (graph.paperNodes[i].fmmmViewY - graph.paperNodes[i].oldViewY) / changeSpeed * timepast + graph.paperNodes[i].oldViewY;
        }
        for(int i = 0; i < graph.authorNodes.size(); ++i)
        {
            graph.authorNodes[i].nowViewX = (graph.authorNodes[i].fmmmViewX - graph.authorNodes[i].oldViewX) / changeSpeed * timepast + graph.authorNodes[i].oldViewX;
            graph.authorNodes[i].nowViewY = (graph.authorNodes[i].fmmmViewY - graph.authorNodes[i].oldViewY) / changeSpeed * timepast + graph.authorNodes[i].oldViewY;
        }
        for(int i = 0; i < graph.conferenceNodes.size(); ++i)
        {
            graph.conferenceNodes[i].nowViewX = (graph.conferenceNodes[i].fmmmViewX - graph.conferenceNodes[i].oldViewX) / changeSpeed * timepast + graph.conferenceNodes[i].oldViewX;
            graph.conferenceNodes[i].nowViewY = (graph.conferenceNodes[i].fmmmViewY - graph.conferenceNodes[i].oldViewY) / changeSpeed * timepast + graph.conferenceNodes[i].oldViewY;
        }
        break;
    default:
        break;
    }
    if(timepast >= changeSpeed)
    {
        timepast = 0;
        graph.resetStatus();
        timer->stop();
    }
    update();
}

void PaperConferenceAuthorWindow::onInitLayoutClicked()
{
    nowLayout = 1;
    timer->start(40);
}

void PaperConferenceAuthorWindow::onRandomLayoutClicked()
{
    nowLayout = 2;
    graph.setRandom();
    timer->start(40);
}

void PaperConferenceAuthorWindow::onFmmmLayoutClicked()
{
    nowLayout = 3;
    timer->start(40);
}
