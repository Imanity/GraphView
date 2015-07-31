#include <QFile>
#include <iostream>
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

}

void FPaperConferenceAuthorGraph::readFile()
{
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
    QString lineStr;
    QStringList words;
    int year, dateFrom, pageFrom;
    char *authors, *id, *pageTitle, *pageTitleShort, *conferenceName, *conferenceNameShort, *authorName, *authorNameShort, *viewLabel;
    int viewColorR, viewColorG, viewColorB, viewColorA, viewLabelX, viewLabelY, viewLabelZ;
    while(!inFile.atEnd())
    {
        //获取nodeId
        lineStr = inFile.readLine();
        int nodeId = lineStr.toInt();
        cout << nodeId << endl;
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
            viewLabelX = lineStr.section(QRegExp("[(,)]"), 1, 1).toDouble();
            viewLabelY = lineStr.section(QRegExp("[(,)]"), 2, 2).toDouble();
            viewLabelZ = lineStr.section(QRegExp("[(,)]"), 3, 3).toDouble();
            newNode.SetLabel(viewLabel, viewLabelX, viewLabelY, viewLabelZ);
            paperNodes.push_back(newNode);
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
            viewLabelX = lineStr.section(QRegExp("[(,)]"), 1, 1).toDouble();
            viewLabelY = lineStr.section(QRegExp("[(,)]"), 2, 2).toDouble();
            viewLabelZ = lineStr.section(QRegExp("[(,)]"), 3, 3).toDouble();
            newNode.SetLabel(viewLabel, viewLabelX, viewLabelY, viewLabelZ);
            conferenceNodes.push_back(newNode);
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
            viewLabelX = lineStr.section(QRegExp("[(,)]"), 1, 1).toDouble();
            viewLabelY = lineStr.section(QRegExp("[(,)]"), 2, 2).toDouble();
            viewLabelZ = lineStr.section(QRegExp("[(,)]"), 3, 3).toDouble();
            newNode.SetLabel(viewLabel, viewLabelX, viewLabelY, viewLabelZ);
            authorNodes.push_back(newNode);
        }
        lineStr = inFile.readLine(); //读取一空行
    }
    inFile.close();
}
