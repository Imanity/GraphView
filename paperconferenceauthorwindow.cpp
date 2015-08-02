#include <QPainter>
#include <QKeyEvent>
#include <cmath>
#include "paperconferenceauthorwindow.h"
#include "ui_paperconferenceauthorwindow.h"

PaperConferenceAuthorWindow::PaperConferenceAuthorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PaperConferenceAuthorWindow)
{
    nowLayout = 1;
    timepast = 0;
    changeSpeed = 12.0;
    zoomRate = 1.0;
    centerX = 250;
    centerY = 250;
    shiftX = 0;
    shiftY = 0;
    highLightX = -1;
    highLightY = -1;
    highLightId = -1;
    pressX = -1;
    pressY = -1;
    tmpX = -1;
    tmpY = -1;
    isPressed = false;
    isDraged = false;
    mouseX = QCursor::pos().x();
    mouseY = QCursor::pos().y();
    timer = new QTimer(this);
    ui->setupUi(this);
    graph.readFile();
    connect(timer, SIGNAL(timeout()),this, SLOT(timerDraw()));
    connect(ui->initLayoutButton, SIGNAL(clicked()), this, SLOT(onInitLayoutClicked()));
    connect(ui->randomLayoutButton, SIGNAL(clicked()), this, SLOT(onRandomLayoutClicked()));
    connect(ui->FmmmLayoutButton, SIGNAL(clicked()), this, SLOT(onFmmmLayoutClicked()));
    connect(ui->circleLayoutButton, SIGNAL(clicked()), this, SLOT(onCircleLayoutClicked()));
    connect(ui->formLayoutButton, SIGNAL(clicked()), this, SLOT(onFormLayoutClicked()));
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
        line1_X = (graph.getNode(graph.directedEdges[i].node1).nowViewX - centerX) * zoomRate + centerX + shiftX;
        line1_Y = (graph.getNode(graph.directedEdges[i].node1).nowViewY - centerY) * zoomRate + centerY + shiftY;
        line2_X = (graph.getNode(graph.directedEdges[i].node2).nowViewX - centerX) * zoomRate + centerX + shiftX;
        line2_Y = (graph.getNode(graph.directedEdges[i].node2).nowViewY - centerY) * zoomRate + centerY + shiftY;
        p.drawLine(line1_X, line1_Y, line2_X, line2_Y);
    }
    int tmpX, tmpY;
    for(int i = 0; i < graph.paperNodes.size(); ++i)
    {
        tmpX = (graph.paperNodes[i].nowViewX - centerX) * zoomRate + centerX + shiftX;
        tmpY = (graph.paperNodes[i].nowViewY - centerY) * zoomRate + centerY + shiftY;
        p.drawEllipse(tmpX - 4, tmpY - 4, 8, 8);
    }
    p.setBrush(Qt::red);
    for(int i = 0; i < graph.authorNodes.size(); ++i)
    {
        tmpX = (graph.authorNodes[i].nowViewX - centerX) * zoomRate + centerX + shiftX;
        tmpY = (graph.authorNodes[i].nowViewY - centerY) * zoomRate + centerY + shiftY;
        p.drawEllipse(tmpX - 4, tmpY - 4, 8, 8);
    }
    p.setBrush(Qt::green);
    for(int i = 0; i < graph.conferenceNodes.size(); ++i)
    {
        tmpX = (graph.conferenceNodes[i].nowViewX - centerX) * zoomRate + centerX + shiftX;
        tmpY = (graph.conferenceNodes[i].nowViewY - centerY) * zoomRate + centerY + shiftY;
        p.drawEllipse(tmpX - 4, tmpY - 4, 8, 8);
    }
    p.setPen(Qt::black);
    p.setBrush(Qt::NoBrush);
    if(highLightId >= 0)
    {
        for(int i = 5; i <= 7; ++i)
        {
            p.drawEllipse(highLightX - i, highLightY - i, 2 * i, 2 * i);
        }
    }
}

bool PaperConferenceAuthorWindow::event(QEvent *event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if(keyEvent->key() == Qt::Key_Up)
        {
            shiftY -= 8;
        }
        if(keyEvent->key() == Qt::Key_Down)
        {
            shiftY += 8;
        }
        if(keyEvent->key() == Qt::Key_Left)
        {
            shiftX -= 8;
        }
        if(keyEvent->key() == Qt::Key_Right)
        {
            shiftX += 8;
        }
        if(keyEvent->key() == Qt::Key_Plus)
        {
            zoomRate *= 1.11111111111;
        }
        if(keyEvent->key() == Qt::Key_Minus)
        {
            zoomRate *= 0.9;
        }
    }
    update();
    return QWidget::event(event);
}

void PaperConferenceAuthorWindow::mouseMoveEvent(QMouseEvent* event)
{
    mouseX = event->pos().x();
    mouseY = event->pos().y();
    if(highLightId != -1)
    {
        setCursor(Qt::PointingHandCursor);
    } else {
        setCursor(Qt::ArrowCursor);
    }
    if(isPressed)
    {
        shiftX = tmpX + mouseX - pressX;
        shiftY = tmpY + mouseY - pressY;
    }
    if(isDraged)
    {
        setCursor(Qt::SizeAllCursor);
        highLightX = mouseX;
        highLightY = mouseY;
        graph.getNode(highLightId).nowViewX = tmpX + (mouseX - ((tmpX - centerX) * zoomRate + shiftX + centerX)) / zoomRate;
        graph.getNode(highLightId).nowViewY = tmpY + (mouseY - ((tmpY - centerY) * zoomRate + shiftY + centerY)) / zoomRate;
        graph.getNode(highLightId).oldViewX = graph.getNode(highLightId).nowViewX;
        graph.getNode(highLightId).oldViewY = graph.getNode(highLightId).nowViewY;
    } else {
        getHighLight();
    }
}

void PaperConferenceAuthorWindow::mousePressEvent(QMouseEvent *event)
{
    pressX = event->pos().x();
    pressY = event->pos().y();
    if(highLightId == -1)
    {
        tmpX = shiftX;
        tmpY = shiftY;
        isPressed = true;
    } else {
        tmpX = (highLightX - shiftX - centerX) / zoomRate + centerX;
        tmpY = (highLightY - shiftY - centerY) / zoomRate + centerY;
        isDraged = true;
    }
}

void PaperConferenceAuthorWindow::mouseReleaseEvent(QMouseEvent *event)
{
    isPressed = false;
    isDraged = false;
}

void PaperConferenceAuthorWindow::wheelEvent(QWheelEvent *event)
{
    double numDegrees = event->delta() / 8.0;
    double numSteps = numDegrees / 15.0;
    double factor = pow(1.05, numSteps);
    zoomRate *= factor;
    shiftX += (1 - factor) * (mouseX - centerX - shiftX);
    shiftY += (1 - factor) * (mouseY - centerY - shiftY);
    getHighLight();
    event->accept();
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
    case 4:
        for(int i = 0; i < graph.paperNodes.size(); ++i)
        {
            graph.paperNodes[i].nowViewX = (graph.paperNodes[i].circleViewX - graph.paperNodes[i].oldViewX) / changeSpeed * timepast + graph.paperNodes[i].oldViewX;
            graph.paperNodes[i].nowViewY = (graph.paperNodes[i].circleViewY - graph.paperNodes[i].oldViewY) / changeSpeed * timepast + graph.paperNodes[i].oldViewY;
        }
        for(int i = 0; i < graph.authorNodes.size(); ++i)
        {
            graph.authorNodes[i].nowViewX = (graph.authorNodes[i].circleViewX - graph.authorNodes[i].oldViewX) / changeSpeed * timepast + graph.authorNodes[i].oldViewX;
            graph.authorNodes[i].nowViewY = (graph.authorNodes[i].circleViewY - graph.authorNodes[i].oldViewY) / changeSpeed * timepast + graph.authorNodes[i].oldViewY;
        }
        for(int i = 0; i < graph.conferenceNodes.size(); ++i)
        {
            graph.conferenceNodes[i].nowViewX = (graph.conferenceNodes[i].circleViewX - graph.conferenceNodes[i].oldViewX) / changeSpeed * timepast + graph.conferenceNodes[i].oldViewX;
            graph.conferenceNodes[i].nowViewY = (graph.conferenceNodes[i].circleViewY - graph.conferenceNodes[i].oldViewY) / changeSpeed * timepast + graph.conferenceNodes[i].oldViewY;
        }
        break;
    case 5:
        for(int i = 0; i < graph.paperNodes.size(); ++i)
        {
            graph.paperNodes[i].nowViewX = (graph.paperNodes[i].formViewX - graph.paperNodes[i].oldViewX) / changeSpeed * timepast + graph.paperNodes[i].oldViewX;
            graph.paperNodes[i].nowViewY = (graph.paperNodes[i].formViewY - graph.paperNodes[i].oldViewY) / changeSpeed * timepast + graph.paperNodes[i].oldViewY;
        }
        for(int i = 0; i < graph.authorNodes.size(); ++i)
        {
            graph.authorNodes[i].nowViewX = (graph.authorNodes[i].formViewX - graph.authorNodes[i].oldViewX) / changeSpeed * timepast + graph.authorNodes[i].oldViewX;
            graph.authorNodes[i].nowViewY = (graph.authorNodes[i].formViewY - graph.authorNodes[i].oldViewY) / changeSpeed * timepast + graph.authorNodes[i].oldViewY;
        }
        for(int i = 0; i < graph.conferenceNodes.size(); ++i)
        {
            graph.conferenceNodes[i].nowViewX = (graph.conferenceNodes[i].formViewX - graph.conferenceNodes[i].oldViewX) / changeSpeed * timepast + graph.conferenceNodes[i].oldViewX;
            graph.conferenceNodes[i].nowViewY = (graph.conferenceNodes[i].formViewY - graph.conferenceNodes[i].oldViewY) / changeSpeed * timepast + graph.conferenceNodes[i].oldViewY;
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

void PaperConferenceAuthorWindow::onCircleLayoutClicked()
{
    nowLayout = 4;
    timer->start(40);
}

void PaperConferenceAuthorWindow::onFormLayoutClicked()
{
    nowLayout = 5;
    timer->start(40);
}

void PaperConferenceAuthorWindow::getHighLight()
{
    highLightId = -1;
    double dis_2 = 64.0;
    vector<int> nearByNodes;
    vector<double> distance_2;
    for(int i = 0; i < graph.paperNodes.size(); ++i)
    {
        double x = mouseX - ((graph.paperNodes[i].nowViewX - centerX) * zoomRate + centerX + shiftX);
        double y = mouseY - ((graph.paperNodes[i].nowViewY - centerY) * zoomRate + centerY + shiftY);
        if(x * x + y * y <= dis_2)
        {
            nearByNodes.push_back(graph.paperNodes[i].nodeId);
            distance_2.push_back(x * x + y * y);
        }
    }
    for(int i = 0; i < graph.authorNodes.size(); ++i)
    {
        double x = mouseX - ((graph.authorNodes[i].nowViewX - centerX) * zoomRate + centerX + shiftX);
        double y = mouseY - ((graph.authorNodes[i].nowViewY - centerY) * zoomRate + centerY + shiftY);
        if(x * x + y * y <= dis_2)
        {
            nearByNodes.push_back(graph.authorNodes[i].nodeId);
            distance_2.push_back(x * x + y * y);
        }
    }
    for(int i = 0; i < graph.conferenceNodes.size(); ++i)
    {
        double x = mouseX - ((graph.conferenceNodes[i].nowViewX - centerX) * zoomRate + centerX + shiftX);
        double y = mouseY - ((graph.conferenceNodes[i].nowViewY - centerY) * zoomRate + centerY + shiftY);
        if(x * x + y * y <= dis_2)
        {
            nearByNodes.push_back(graph.conferenceNodes[i].nodeId);
            distance_2.push_back(x * x + y * y);
        }
    }
    double minDis_2 = -1;
    if(!nearByNodes.empty())
    {
        for(int i = 0; i < nearByNodes.size(); ++i)
        {
            if(distance_2[i] < minDis_2 || minDis_2 == -1)
            {
                minDis_2 = distance_2[i];
                highLightId = nearByNodes[i];
                highLightX = (graph.getNode(nearByNodes[i]).nowViewX - centerX) * zoomRate + centerX + shiftX;
                highLightY = (graph.getNode(nearByNodes[i]).nowViewY - centerY) * zoomRate + centerY + shiftY;
            }
        }
    }
    if(highLightId == -1)
    {
        highLightX = -1;
        highLightY = -1;
    }
}
