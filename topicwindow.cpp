#include <QPainter>
#include <QKeyEvent>
#include <cmath>
#include "topicwindow.h"
#include "ui_topicwindow.h"

TopicWindow::TopicWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TopicWindow)
{
    nowLayout = 3;
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
    isCtrled = false;
    isGroupDraged = false;
    upBorder = -1;
    downBorder = -1;
    leftBorder = -1;
    rightBorder = -1;
    isDisplayGroup = false;
    isGroupMove = false;
    mouseX = QCursor::pos().x();
    mouseY = QCursor::pos().y();
    timer = new QTimer(this);
    ui->setupUi(this);
    graph.readFile();
    connect(timer, SIGNAL(timeout()),this, SLOT(timerDraw()));
    connect(ui->randomLayoutButton, SIGNAL(clicked()), this, SLOT(onRandomLayoutClicked()));
    connect(ui->FmmmLayoutButton, SIGNAL(clicked()), this, SLOT(onFmmmLayoutClicked()));
    connect(ui->circleLayoutButton, SIGNAL(clicked()), this, SLOT(onCircleLayoutClicked()));
    connect(ui->formLayoutButton, SIGNAL(clicked()), this, SLOT(onFormLayoutClicked()));
}

TopicWindow::~TopicWindow()
{
    delete ui;
}

void TopicWindow::paintEvent(QPaintEvent *ev)
{
    QPainter p(this);
    int line1_X, line2_X, line1_Y, line2_Y;
    p.setPen(QColor(100, 100, 100));
    p.setBrush(Qt::yellow);
    for(int i = 0; i < graph.undirectedEdges.size(); ++i)
    {
        line1_X = (graph.getNode(graph.undirectedEdges[i].node1).nowViewX - centerX) * zoomRate + centerX + shiftX;
        line1_Y = (graph.getNode(graph.undirectedEdges[i].node1).nowViewY - centerY) * zoomRate + centerY + shiftY;
        line2_X = (graph.getNode(graph.undirectedEdges[i].node2).nowViewX - centerX) * zoomRate + centerX + shiftX;
        line2_Y = (graph.getNode(graph.undirectedEdges[i].node2).nowViewY - centerY) * zoomRate + centerY + shiftY;
        p.drawLine(line1_X, line1_Y, line2_X, line2_Y);
    }
    p.setBrush(Qt::red);
    int tmpX, tmpY;
    for(int i = 0; i < graph.topicNodes.size(); ++i)
    {
        tmpX = (graph.topicNodes[i].nowViewX - centerX) * zoomRate + centerX + shiftX;
        tmpY = (graph.topicNodes[i].nowViewY - centerY) * zoomRate + centerY + shiftY;
        p.drawEllipse(tmpX - 4, tmpY - 4, 8, 8);
    }
    p.setBrush(Qt::NoBrush);
    if(isGroupDraged)
    {
        p.setPen(QPen(Qt::green, 2));
        p.setBrush(QColor(0, 255, 100, 50));
        p.drawRect(leftBorder, upBorder, mouseX - leftBorder, mouseY - upBorder);
    }
    p.setBrush(Qt::NoBrush);
    if(isDisplayGroup)
    {
        p.setPen(Qt::green);
        for(int i = 0; i < groupNodes.size(); ++i)
        {
            tmpX = (graph.getNode(groupNodes[i]).nowViewX - centerX) * zoomRate + centerX + shiftX;
            tmpY = (graph.getNode(groupNodes[i]).nowViewY - centerY) * zoomRate + centerY + shiftY;
            for(int i = 5; i <= 7; ++i)
            {
                p.drawEllipse(tmpX - i, tmpY - i, 2 * i, 2 * i);
            }
        }
    } else if(highLightId >= 0)
    {
        p.setPen(Qt::black);
        for(int i = 5; i <= 7; ++i)
        {
            p.drawEllipse(highLightX - i, highLightY - i, 2 * i, 2 * i);
        }
    }
}

bool TopicWindow::event(QEvent *event)
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
        if(keyEvent->key() == Qt::Key_Control)
        {
            isCtrled = true;
        }
    } else if(event->type() == QEvent::KeyRelease)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if(keyEvent->key() == Qt::Key_Control)
        {
            isCtrled = false;
        }
    }
    update();
    return QWidget::event(event);
}

void TopicWindow::mouseMoveEvent(QMouseEvent* event)
{
    mouseX = event->pos().x();
    mouseY = event->pos().y();
    if(highLightId != -1)
    {
        setCursor(Qt::PointingHandCursor);
        //显示信息
        ui->nodeId->setText("<b>nodeId: </b>" + QString::number(graph.getNode(highLightId).nodeId));
        ui->textEdit->setText("<b>topicWords:</b><br>" + graph.getTopicWords(highLightId));
    } else {
        setCursor(Qt::ArrowCursor);
        //清空信息
        ui->nodeId->setText("<b>nodeId: </b>");
    }
    if(isPressed)
    {
        setCursor(Qt::SizeAllCursor);
        shiftX = tmpX + mouseX - pressX;
        shiftY = tmpY + mouseY - pressY;
    }
    if(isDisplayGroup && isGroupMove)
    {
        setCursor(Qt::SizeAllCursor);
        for(int i = 0; i < groupNodes.size(); ++i)
        {
            graph.getNode(groupNodes[i]).nowViewX = groupNodesTmpX[i] + (mouseX - pressX) / zoomRate;
            graph.getNode(groupNodes[i]).nowViewY = groupNodesTmpY[i] + (mouseY - pressY) / zoomRate;
            graph.getNode(groupNodes[i]).oldViewX = graph.getNode(groupNodes[i]).nowViewX;
            graph.getNode(groupNodes[i]).oldViewY = graph.getNode(groupNodes[i]).nowViewY;
        }
    }else if(isDraged)
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

void TopicWindow::mousePressEvent(QMouseEvent *event)
{
    pressX = event->pos().x();
    pressY = event->pos().y();
    if(isCtrled)
    {
        upBorder = pressY;
        leftBorder = pressX;
        isGroupDraged = true;
    } else if(isDisplayGroup)
    {
        isGroupMove = true;
    } else if(highLightId == -1)
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

void TopicWindow::mouseReleaseEvent(QMouseEvent *event)
{
    for(int i = 0; i < groupNodes.size(); ++i)
    {
        groupNodesTmpX[i] = graph.getNode(groupNodes[i]).nowViewX;
        groupNodesTmpY[i] = graph.getNode(groupNodes[i]).nowViewY;
    }
    if(event->pos().x() == pressX && event->pos().y() == pressY)
    {
        isDisplayGroup = false;
    }
    if(isGroupDraged)
    {
        downBorder = event->pos().y();
        rightBorder = event->pos().x();
        getGroupNodes();
    }
    isPressed = false;
    isDraged = false;
    isCtrled = false;
    isGroupDraged = false;
    isGroupMove = false;
    upBorder = -1;
    downBorder = -1;
    leftBorder = -1;
    rightBorder = -1;
}

void TopicWindow::wheelEvent(QWheelEvent *event)
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

void TopicWindow::timerDraw()
{
    timepast++;
    switch(nowLayout)
    {
    case 1:
        for(int i = 0; i < graph.topicNodes.size(); ++i)
        {
            graph.topicNodes[i].nowViewX = (graph.topicNodes[i].randomViewX - graph.topicNodes[i].oldViewX) / changeSpeed * timepast + graph.topicNodes[i].oldViewX;
            graph.topicNodes[i].nowViewY = (graph.topicNodes[i].randomViewY - graph.topicNodes[i].oldViewY) / changeSpeed * timepast + graph.topicNodes[i].oldViewY;
        }
        break;
    case 2:
        for(int i = 0; i < graph.topicNodes.size(); ++i)
        {
            graph.topicNodes[i].nowViewX = (graph.topicNodes[i].fmmmViewX - graph.topicNodes[i].oldViewX) / changeSpeed * timepast + graph.topicNodes[i].oldViewX;
            graph.topicNodes[i].nowViewY = (graph.topicNodes[i].fmmmViewY - graph.topicNodes[i].oldViewY) / changeSpeed * timepast + graph.topicNodes[i].oldViewY;
        }
        break;
    case 3:
        for(int i = 0; i < graph.topicNodes.size(); ++i)
        {
            graph.topicNodes[i].nowViewX = (graph.topicNodes[i].circleViewX - graph.topicNodes[i].oldViewX) / changeSpeed * timepast + graph.topicNodes[i].oldViewX;
            graph.topicNodes[i].nowViewY = (graph.topicNodes[i].circleViewY - graph.topicNodes[i].oldViewY) / changeSpeed * timepast + graph.topicNodes[i].oldViewY;
        }
        break;
    case 4:
        for(int i = 0; i < graph.topicNodes.size(); ++i)
        {
            graph.topicNodes[i].nowViewX = (graph.topicNodes[i].formViewX - graph.topicNodes[i].oldViewX) / changeSpeed * timepast + graph.topicNodes[i].oldViewX;
            graph.topicNodes[i].nowViewY = (graph.topicNodes[i].formViewY - graph.topicNodes[i].oldViewY) / changeSpeed * timepast + graph.topicNodes[i].oldViewY;
        }
        break;
    default:
        break;
    }
    if(timepast >= changeSpeed)
    {
        resetGroupMove();
        timepast = 0;
        graph.resetStatus();
        timer->stop();
    }
    update();
}

void TopicWindow::onRandomLayoutClicked()
{
    nowLayout = 1;
    graph.setRandom();
    timer->start(40);
}

void TopicWindow::onFmmmLayoutClicked()
{
    nowLayout = 2;
    timer->start(40);
}

void TopicWindow::onCircleLayoutClicked()
{
    nowLayout = 3;
    timer->start(40);
}

void TopicWindow::onFormLayoutClicked()
{
    nowLayout = 4;
    timer->start(40);
}

void TopicWindow::getHighLight()
{
    highLightId = -1;
    double dis_2 = 64.0;
    vector<int> nearByNodes;
    vector<double> distance_2;
    for(int i = 0; i < graph.topicNodes.size(); ++i)
    {
        double x = mouseX - ((graph.topicNodes[i].nowViewX - centerX) * zoomRate + centerX + shiftX);
        double y = mouseY - ((graph.topicNodes[i].nowViewY - centerY) * zoomRate + centerY + shiftY);
        if(x * x + y * y <= dis_2)
        {
            nearByNodes.push_back(graph.topicNodes[i].nodeId);
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

void TopicWindow::getGroupNodes()
{
    double tmpX, tmpY;
    groupNodes.clear();
    groupNodesTmpX.clear();
    groupNodesTmpY.clear();
    double swapTmp;
    if(leftBorder > rightBorder)
    {
        swapTmp = rightBorder;
        rightBorder = leftBorder;
        leftBorder = swapTmp;
    }
    if(upBorder > downBorder)
    {
        swapTmp = downBorder;
        downBorder = upBorder;
        upBorder = swapTmp;
    }
    for(int i = 0; i < graph.topicNodes.size(); ++i)
    {
        tmpX = (graph.topicNodes[i].nowViewX - centerX) * zoomRate + centerX + shiftX;
        tmpY = (graph.topicNodes[i].nowViewY - centerY) * zoomRate + centerY + shiftY;
        if(tmpX >= leftBorder && tmpX <= rightBorder)
        {
            if(tmpY >= upBorder && tmpY <= downBorder)
            {
                groupNodes.push_back(graph.topicNodes[i].nodeId);
                groupNodesTmpX.push_back(graph.topicNodes[i].nowViewX);
                groupNodesTmpY.push_back(graph.topicNodes[i].nowViewY);
            }
        }
    }
    if(!groupNodes.empty())
    {
        isDisplayGroup = true;
    } else {
        isDisplayGroup = false;
    }
}

void TopicWindow::resetGroupMove()
{
    for(int i = 0; i < groupNodes.size(); ++i)
    {
        groupNodesTmpX[i] = graph.getNode(groupNodes[i]).nowViewX;
        groupNodesTmpY[i] = graph.getNode(groupNodes[i]).nowViewY;
    }
}
