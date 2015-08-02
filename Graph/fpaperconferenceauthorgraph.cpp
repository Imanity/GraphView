#include <QFile>
#include <iostream>
#include <ctime>
#include <cmath>
#include "fpaperconferenceauthorgraph.h"

#ifdef Q_OS_WIN
#define ISWIN 1
#endif

#ifdef Q_OS_MAC
#define ISWIN 0
#endif

using namespace std;

FPaperConferenceAuthorGraph::FPaperConferenceAuthorGraph()
{
    nodeNum = 0;
    srand((unsigned)time(NULL));
    GA = GraphAttributes(graphView);
}

void FPaperConferenceAuthorGraph::readFile()
{
    QString lineStr;
    QStringList words;
    //读取节点信息
    QString fileName;
    if(ISWIN == 0) //Mac下文件读取
    {
        fileName = "/Users/imanity/Documents/Qt/GraphView/GraphData/PaperConferenceAuthorGraph/Nodes.txt";
    } else { //Windows下文件读取
        fileName = "E:/CppProjects/GraphView/GraphData/PaperConferenceAuthorGraph/Nodes.txt";
    }
    QFile inFile(fileName);
    if(!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        cout << "Open failed." << endl;
    }
    int year, dateFrom, pageFrom;
    char *authors, *id, *pageTitle, *pageTitleShort, *conferenceName, *conferenceNameShort, *authorName, *authorNameShort, *viewLabel;
    int viewColorR, viewColorG, viewColorB, viewColorA, viewLabelX, viewLabelY, viewLabelZ;
    while(!inFile.atEnd())
    {
        //获取nodeId
        lineStr = inFile.readLine();
        int nodeId = lineStr.toInt();
        //获取type
        lineStr = inFile.readLine();
        words = lineStr.split(": ");
        if(words[1] == "paper\n") //type为paper
        {
            //获取year
            lineStr = inFile.readLine();
            words = lineStr.split(": ");
            year = words[1].toInt();
            //获取authors
            lineStr = inFile.readLine();
            words = lineStr.split(": ");
            authors = words[1].toLatin1().data();
            //获取dateFrom
            lineStr = inFile.readLine();
            words = lineStr.split(": ");
            dateFrom = words[1].toInt();
            //获取id
            lineStr = inFile.readLine();
            words = lineStr.split(": ");
            id = words[1].toLatin1().data();
            //获取pageFrom
            lineStr = inFile.readLine();
            words = lineStr.split(": ");
            pageFrom = words[1].toInt();
            //获取pageTitle
            lineStr = inFile.readLine();
            words = lineStr.split(": ");
            pageTitle = words[1].toLatin1().data();
            //获取pageTitleShort
            lineStr = inFile.readLine();
            words = lineStr.split(": ");
            pageTitleShort = words[1].toLatin1().data();
            FPaperNode newNode(nodeId, year, authors, dateFrom, id, pageFrom, pageTitle, pageTitleShort);
            //获取viewColor
            lineStr = inFile.readLine();
            viewColorR = lineStr.section(QRegExp("[(,)]"), 1, 1).toInt();
            viewColorG = lineStr.section(QRegExp("[(,)]"), 2, 2).toInt();
            viewColorB = lineStr.section(QRegExp("[(,)]"), 3, 3).toInt();
            viewColorA = lineStr.section(QRegExp("[(,)]"), 4, 4).toInt();
            newNode.setColor(viewColorR, viewColorG, viewColorB, viewColorA);
            //获取viewLabel
            lineStr = inFile.readLine();
            words = lineStr.split(": ");
            viewLabel = words[1].toLatin1().data();
            lineStr = inFile.readLine();
            viewLabelX = lineStr.section(QRegExp("[(,)]"), 1, 1).toDouble() * 2 - 150;
            viewLabelY = lineStr.section(QRegExp("[(,)]"), 2, 2).toDouble() * 2 - 150;
            viewLabelZ = lineStr.section(QRegExp("[(,)]"), 3, 3).toDouble();
            newNode.SetLabel(viewLabel, viewLabelX, viewLabelY, viewLabelZ);
            newNode.ogdfId = graphView.newNode();
            newNode.nowViewX = newNode.viewLayoutX;
            newNode.nowViewY = newNode.viewLayoutY;
            GA.x(newNode.ogdfId) = viewLabelX;
            GA.y(newNode.ogdfId) = viewLabelY;
            paperNodes.push_back(newNode);
            nodeNum++;
        } else if(words[1] == "conference\n") //type为conference
        {
            //获取year
            lineStr = inFile.readLine();
            words = lineStr.split(": ");
            year = words[1].toInt();
            //获取id
            lineStr = inFile.readLine();
            words = lineStr.split(": ");
            id = words[1].toLatin1().data();
            //获取conferenceName
            lineStr = inFile.readLine();
            words = lineStr.split(": ");
            conferenceName = words[1].toLatin1().data();
            //获取conferenceNameShort
            lineStr = inFile.readLine();
            words = lineStr.split(": ");
            conferenceNameShort = words[1].toLatin1().data();
            FConferenceNode newNode(nodeId, year, id, conferenceName, conferenceNameShort);
            //获取viewColor
            lineStr = inFile.readLine();
            viewColorR = lineStr.section(QRegExp("[(,)]"), 1, 1).toInt();
            viewColorG = lineStr.section(QRegExp("[(,)]"), 2, 2).toInt();
            viewColorB = lineStr.section(QRegExp("[(,)]"), 3, 3).toInt();
            viewColorA = lineStr.section(QRegExp("[(,)]"), 4, 4).toInt();
            newNode.setColor(viewColorR, viewColorG, viewColorB, viewColorA);
            //获取viewLabel
            lineStr = inFile.readLine();
            words = lineStr.split(": ");
            viewLabel = words[1].toLatin1().data();
            lineStr = inFile.readLine();
            viewLabelX = lineStr.section(QRegExp("[(,)]"), 1, 1).toDouble() * 2 - 150;
            viewLabelY = lineStr.section(QRegExp("[(,)]"), 2, 2).toDouble() * 2 - 150;
            viewLabelZ = lineStr.section(QRegExp("[(,)]"), 3, 3).toDouble();
            newNode.SetLabel(viewLabel, viewLabelX, viewLabelY, viewLabelZ);
            newNode.ogdfId = graphView.newNode();
            newNode.nowViewX = newNode.viewLayoutX;
            newNode.nowViewY = newNode.viewLayoutY;
            GA.x(newNode.ogdfId) = viewLabelX;
            GA.y(newNode.ogdfId) = viewLabelY;
            conferenceNodes.push_back(newNode);
            nodeNum++;
        } else if(words[1] == "author\n") //author
        {
            //获取year
            lineStr = inFile.readLine();
            words = lineStr.split(": ");
            year = words[1].toInt();
            //获取id
            lineStr = inFile.readLine();
            words = lineStr.split(": ");
            id = words[1].toLatin1().data();
            //获取authorName
            lineStr = inFile.readLine();
            words = lineStr.split(": ");
            authorName = words[1].toLatin1().data();
            //获取authorNameShort
            lineStr = inFile.readLine();
            words = lineStr.split(": ");
            authorNameShort = words[1].toLatin1().data();
            FAuthorNode newNode(nodeId, year, id, authorName, authorNameShort);
            //获取viewColor
            lineStr = inFile.readLine();
            viewColorR = lineStr.section(QRegExp("[(,)]"), 1, 1).toInt();
            viewColorG = lineStr.section(QRegExp("[(,)]"), 2, 2).toInt();
            viewColorB = lineStr.section(QRegExp("[(,)]"), 3, 3).toInt();
            viewColorA = lineStr.section(QRegExp("[(,)]"), 4, 4).toInt();
            newNode.setColor(viewColorR, viewColorG, viewColorB, viewColorA);
            //获取viewLabel
            lineStr = inFile.readLine();
            words = lineStr.split(": ");
            viewLabel = words[1].toLatin1().data();
            lineStr = inFile.readLine();
            viewLabelX = lineStr.section(QRegExp("[(,)]"), 1, 1).toDouble() * 2 - 150;
            viewLabelY = lineStr.section(QRegExp("[(,)]"), 2, 2).toDouble() * 2 - 150;
            viewLabelZ = lineStr.section(QRegExp("[(,)]"), 3, 3).toDouble();
            newNode.SetLabel(viewLabel, viewLabelX, viewLabelY, viewLabelZ);
            newNode.ogdfId = graphView.newNode();
            newNode.nowViewX = newNode.viewLayoutX;
            newNode.nowViewY = newNode.viewLayoutY;
            GA.x(newNode.ogdfId) = viewLabelX;
            GA.y(newNode.ogdfId) = viewLabelY;
            authorNodes.push_back(newNode);
            nodeNum++;
        }
        lineStr = inFile.readLine(); //读取一空行
    }
    inFile.close();
    //读取边信息
    if(ISWIN == 0) //Mac下文件读取
    {
        fileName = "/Users/imanity/Documents/Qt/GraphView/GraphData/PaperConferenceAuthorGraph/Edges.txt";
    } else { //Windows下文件读取
        fileName = "E:/CppProjects/GraphView/GraphData/PaperConferenceAuthorGraph/Edges.txt";
    }
    QFile inFile2(fileName);
    if(!inFile2.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        cout << "Open failed." << endl;
    }
    int node1, node2;
    while(!inFile2.atEnd())
    {
        lineStr = inFile2.readLine();
        words = lineStr.split(" ");
        node1 = words[0].toInt();
        node2 = words[1].toInt();
        FDirectedEdge newEdge(node1, node2);
        graphView.newEdge(getOgdfId(node1), getOgdfId(node2));
        directedEdges.push_back(newEdge);
    }
    inFile2.close();
    resetStatus();
    getFmmmLayout();
    setCircle();
    setForm();
}

node FPaperConferenceAuthorGraph::getOgdfId(int nodeId)
{
    for(int i = 0; i < paperNodes.size(); ++i)
    {
        if(paperNodes[i].nodeId == nodeId)
        {
            return paperNodes[i].ogdfId;
        }
    }
    for(int i = 0; i < authorNodes.size(); ++i)
    {
        if(authorNodes[i].nodeId == nodeId)
        {
            return authorNodes[i].ogdfId;
        }
    }
    for(int i = 0; i < conferenceNodes.size(); ++i)
    {
        if(conferenceNodes[i].nodeId == nodeId)
        {
            return conferenceNodes[i].ogdfId;
        }
    }
}

FNode& FPaperConferenceAuthorGraph::getNode(int nodeId)
{
    for(int i = 0; i < paperNodes.size(); ++i)
    {
        if(paperNodes[i].nodeId == nodeId)
        {
            return paperNodes[i];
        }
    }
    for(int i = 0; i < authorNodes.size(); ++i)
    {
        if(authorNodes[i].nodeId == nodeId)
        {
            return authorNodes[i];
        }
    }
    for(int i = 0; i < conferenceNodes.size(); ++i)
    {
        if(conferenceNodes[i].nodeId == nodeId)
        {
            return conferenceNodes[i];
        }
    }
}

void FPaperConferenceAuthorGraph::resetStatus()
{
    for(int i = 0; i < paperNodes.size(); ++i)
    {
        paperNodes[i].oldViewX = paperNodes[i].nowViewX;
        paperNodes[i].oldViewY = paperNodes[i].nowViewY;
    }
    for(int i = 0; i < authorNodes.size(); ++i)
    {
        authorNodes[i].oldViewX = authorNodes[i].nowViewX;
        authorNodes[i].oldViewY = authorNodes[i].nowViewY;
    }
    for(int i = 0; i < conferenceNodes.size(); ++i)
    {
        conferenceNodes[i].oldViewX = conferenceNodes[i].nowViewX;
        conferenceNodes[i].oldViewY = conferenceNodes[i].nowViewY;
    }
}

void FPaperConferenceAuthorGraph::getFmmmLayout()
{
    FMMMLayout fmmm;
    fmmm.call(GA);
    DRect rect = GA.boundingBox();
    double width = rect.width();
    double height = rect.height();
    for(int i = 0; i < paperNodes.size(); ++i)
    {
        paperNodes[i].fmmmViewX = GA.x(paperNodes[i].ogdfId) / width * 500 - 20;
        paperNodes[i].fmmmViewY = GA.y(paperNodes[i].ogdfId) / height * 500 - 20;
    }
    for(int i = 0; i < authorNodes.size(); ++i)
    {
        authorNodes[i].fmmmViewX = GA.x(authorNodes[i].ogdfId) / width * 500 - 20;
        authorNodes[i].fmmmViewY = GA.y(authorNodes[i].ogdfId) / height * 500 - 20;
    }
    for(int i = 0; i < conferenceNodes.size(); ++i)
    {
        conferenceNodes[i].fmmmViewX = GA.x(conferenceNodes[i].ogdfId) / width * 500 - 20;
        conferenceNodes[i].fmmmViewY = GA.y(conferenceNodes[i].ogdfId) / height * 500 - 20;
    }
}

void FPaperConferenceAuthorGraph::changeToFmmmLayout()
{
    for(int i = 0; i < paperNodes.size(); ++i)
    {
        paperNodes[i].nowViewX = paperNodes[i].fmmmViewX;
        paperNodes[i].nowViewY = paperNodes[i].fmmmViewY;
    }
    for(int i = 0; i < authorNodes.size(); ++i)
    {
        authorNodes[i].nowViewX = authorNodes[i].fmmmViewX;
        authorNodes[i].nowViewY = authorNodes[i].fmmmViewY;
    }
    for(int i = 0; i < conferenceNodes.size(); ++i)
    {
        conferenceNodes[i].nowViewX = conferenceNodes[i].fmmmViewX;
        conferenceNodes[i].nowViewY = conferenceNodes[i].fmmmViewY;
    }
}

void FPaperConferenceAuthorGraph::setRandom()
{
    for(int i = 0; i < paperNodes.size(); ++i)
    {
        paperNodes[i].randomViewX = (double)rand() / (double)RAND_MAX * 500;
        paperNodes[i].randomViewY = (double)rand() / (double)RAND_MAX * 500;
    }
    for(int i = 0; i < authorNodes.size(); ++i)
    {
        authorNodes[i].randomViewX = (double)rand() / (double)RAND_MAX * 500;
        authorNodes[i].randomViewY = (double)rand() / (double)RAND_MAX * 500;
    }
    for(int i = 0; i < conferenceNodes.size(); ++i)
    {
        conferenceNodes[i].randomViewX = (double)rand() / (double)RAND_MAX * 500;
        conferenceNodes[i].randomViewY = (double)rand() / (double)RAND_MAX * 500;
    }
}

void FPaperConferenceAuthorGraph::setCircle()
{
    double step = 2 * 3.1415926536 / nodeNum;
    double currentAngle = 0;
    for(int i = 0; i < paperNodes.size(); ++i)
    {
        paperNodes[i].circleViewX = 250 + 200 * cos(currentAngle);
        paperNodes[i].circleViewY = 250 + 200 * sin(currentAngle);
        currentAngle += step;
    }
    for(int i = 0; i < authorNodes.size(); ++i)
    {
        authorNodes[i].circleViewX = 250 + 200 * cos(currentAngle);
        authorNodes[i].circleViewY = 250 + 200 * sin(currentAngle);
        currentAngle += step;
    }
    for(int i = 0; i < conferenceNodes.size(); ++i)
    {
        conferenceNodes[i].circleViewX = 250 + 200 * cos(currentAngle);
        conferenceNodes[i].circleViewY = 250 + 200 * sin(currentAngle);
        currentAngle += step;
    }
}

void FPaperConferenceAuthorGraph::setForm()
{
    int columnNum = (int)sqrt(nodeNum);
    double step = 500.0 / (columnNum + 1);
    double currentX = 0, currentY = 0;
    currentY += step;
    for(int i = 0; i < paperNodes.size(); ++i)
    {
        currentX += step;
        if(currentX >= 500)
        {
            currentX = step;
            currentY += step;
        }
        paperNodes[i].formViewX = currentX;
        paperNodes[i].formViewY = currentY;
    }
    for(int i = 0; i < authorNodes.size(); ++i)
    {
        currentX += step;
        if(currentX >= 500)
        {
            currentX = step;
            currentY += step;
        }
        authorNodes[i].formViewX = currentX;
        authorNodes[i].formViewY = currentY;
    }
    for(int i = 0; i < conferenceNodes.size(); ++i)
    {
        currentX += step;
        if(currentX >= 500)
        {
            currentX = step;
            currentY += step;
        }
        conferenceNodes[i].formViewX = currentX;
        conferenceNodes[i].formViewY = currentY;
    }
}
