#include <QFile>
#include <QTextStream>
#include <iostream>
#include <ctime>
#include <cmath>
#include "ftopicgraph.h"

#ifdef Q_OS_WIN
#define ISWIN 1
#endif

#ifdef Q_OS_MAC
#define ISWIN 0
#endif

using namespace std;

FTopicGraph::FTopicGraph()
{
    nodeNum = 0;
    srand((unsigned)time(NULL));
    GA = GraphAttributes(graphView);
}

void FTopicGraph::readFile()
{
    QString lineStr;
    QStringList words;
    //读取节点信息
    QString fileName;
    if(ISWIN == 0) //Mac下文件读取
    {
        fileName = "/Users/imanity/Documents/Qt/GraphView/GraphData/TopicGraph/Nodes.txt";
    } else { //Windows下文件读取
        fileName = "E:/CppProjects/GraphView/GraphData/TopicGraph/Nodes.txt";
    }
    QFile inFile(fileName);
    if(!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        cout << "Open failed." << endl;
    }
    int nodeId;
    QString topicWords, topicDocuments;
    while(!inFile.atEnd())
    {
        //获取nodeId
        lineStr = inFile.readLine();
        nodeId = lineStr.toInt();
        //获取topicWords
        lineStr = inFile.readLine();
        words = lineStr.split(": ");
        topicWords = words[1].trimmed();
        //获取topicWords
        lineStr = inFile.readLine();
        words = lineStr.split(": ");
        topicDocuments = words[1].trimmed();
        //读取一空行
        lineStr = inFile.readLine();
        FTopicNode newNode(nodeId, topicWords, topicDocuments);
        newNode.ogdfId = graphView.newNode();
        topicNodes.push_back(newNode);
        nodeNum++;
    }
    inFile.close();
    //读取边信息
    if(ISWIN == 0) //Mac下文件读取
    {
        fileName = "/Users/imanity/Documents/Qt/GraphView/GraphData/TopicGraph/Edges.txt";
    } else { //Windows下文件读取
        fileName = "E:/CppProjects/GraphView/GraphData/TopicGraph/Edges.txt";
    }
    QFile inFile2(fileName);
    if(!inFile2.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        cout << "Open failed." << endl;
    }
    int node1, node2;
    double weight;
    while(!inFile2.atEnd())
    {
        lineStr = inFile2.readLine();
        words = lineStr.split(" ");
        node1 = words[0].toInt();
        node2 = words[1].toInt();
        getNode(node1).connectivity++;
        getNode(node2).connectivity++;
        weight = words[2].toDouble();
        FUndirectedEdge newEdge(node1, node2, weight);
        graphView.newEdge(getOgdfId(node1), getOgdfId(node2));
        undirectedEdges.push_back(newEdge);
    }
    inFile2.close();
    getFmmmLayout();
    setCircle();
    setForm();
    resetStatus();
    getMaxConnectivity();
}

node FTopicGraph::getOgdfId(int nodeId)
{
    for(int i = 0; i < topicNodes.size(); ++i)
    {
        if(topicNodes[i].nodeId == nodeId)
        {
            return topicNodes[i].ogdfId;
        }
    }
}

FNode& FTopicGraph::getNode(int nodeId)
{
    for(int i = 0; i < topicNodes.size(); ++i)
    {
        if(topicNodes[i].nodeId == nodeId)
        {
            return topicNodes[i];
        }
    }
}

void FTopicGraph::resetStatus()
{
    for(int i = 0; i < topicNodes.size(); ++i)
    {
        topicNodes[i].oldViewX = topicNodes[i].nowViewX;
        topicNodes[i].oldViewY = topicNodes[i].nowViewY;
    }
}

void FTopicGraph::getFmmmLayout()
{
    FMMMLayout fmmm;
    fmmm.call(GA);
    DRect rect = GA.boundingBox();
    double width = rect.width();
    double height = rect.height();
    for(int i = 0; i < topicNodes.size(); ++i)
    {
        topicNodes[i].fmmmViewX = GA.x(topicNodes[i].ogdfId) / width * 700 - 35;
        topicNodes[i].fmmmViewY = GA.y(topicNodes[i].ogdfId) / height * 700 - 35;
    }
}

void FTopicGraph::changeToFmmmLayout()
{
    for(int i = 0; i < topicNodes.size(); ++i)
    {
        topicNodes[i].nowViewX = topicNodes[i].fmmmViewX;
        topicNodes[i].nowViewY = topicNodes[i].fmmmViewY;
    }
}

void FTopicGraph::setRandom()
{
    for(int i = 0; i < topicNodes.size(); ++i)
    {
        topicNodes[i].randomViewX = (double)rand() / (double)RAND_MAX * 700;
        topicNodes[i].randomViewY = (double)rand() / (double)RAND_MAX * 700;
    }
}

void FTopicGraph::setCircle()
{
    double step = 2 * 3.1415926536 / nodeNum;
    double currentAngle = 0;
    for(int i = 0; i < topicNodes.size(); ++i)
    {
        topicNodes[i].circleViewX = 350 + 280 * cos(currentAngle);
        topicNodes[i].circleViewY = 350 + 280 * sin(currentAngle);
        topicNodes[i].nowViewX = topicNodes[i].circleViewX;
        topicNodes[i].nowViewY = topicNodes[i].circleViewY;
        currentAngle += step;
    }
}

void FTopicGraph::setForm()
{
    int columnNum = (int)sqrt(nodeNum);
    double step = 700.0 / (columnNum + 1);
    double currentX = 0, currentY = 0;
    currentY += step;
    for(int i = 0; i < topicNodes.size(); ++i)
    {
        currentX += step;
        if(currentX >= 700)
        {
            currentX = step;
            currentY += step;
        }
        topicNodes[i].formViewX = currentX;
        topicNodes[i].formViewY = currentY;
    }
}

QString FTopicGraph::getTopicWords(int nodeId)
{
    for(int i = 0; i < topicNodes.size(); ++i)
    {
        if(topicNodes[i].nodeId == nodeId)
        {
            return topicNodes[i].topicWords;
        }
    }
}

QString FTopicGraph::getTopicDocuments(int nodeId)
{
    for(int i = 0; i < topicNodes.size(); ++i)
    {
        if(topicNodes[i].nodeId == nodeId)
        {
            return topicNodes[i].topicDocuments;
        }
    }
}

void FTopicGraph::getMaxConnectivity()
{
    for(int i = 0; i < topicNodes.size(); ++i)
    {
        if(topicNodes[i].connectivity >= maxConnectivity)
        {
            maxConnectivity = topicNodes[i].connectivity;
        }
    }
}

void FTopicGraph::saveLayout()
{
    QString fileName;
    if(ISWIN == 0) //Mac下文件读取
    {
        fileName = "/Users/imanity/Documents/Qt/GraphView/GraphData/TopicGraph/Layout.save";
    } else { //Windows下文件读取
        fileName = "E:/CppProjects/GraphView/GraphData/TopicGraph/Layout.save";
    }
    QFile outFile(fileName);
    if(!outFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        cout << "Open failed." << endl;
    }
    QTextStream out(&outFile);
    for(int i = 0; i < topicNodes.size(); ++i)
    {
        out << topicNodes[i].nowViewX << endl << topicNodes[i].nowViewY << endl;
    }
}

void FTopicGraph::loadLayout()
{
    QString fileName;
    if(ISWIN == 0) //Mac下文件读取
    {
        fileName = "/Users/imanity/Documents/Qt/GraphView/GraphData/TopicGraph/Layout.save";
    } else { //Windows下文件读取
        fileName = "E:/CppProjects/GraphView/GraphData/TopicGraph/Layout.save";
    }
    QFile inFile(fileName);
    if(!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        cout << "Open failed." << endl;
    }
    QTextStream in(&inFile);
    QString line;
    for(int i = 0; i < topicNodes.size(); ++i)
    {
        line = in.readLine().trimmed();
        topicNodes[i].nowViewX = line.toDouble();
        line = in.readLine().trimmed();
        topicNodes[i].nowViewY = line.toDouble();
    }
    resetStatus();
}
