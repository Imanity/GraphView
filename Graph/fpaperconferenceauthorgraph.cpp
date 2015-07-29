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
    char *authors, *id;
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
        }
        break;
    }
    inFile.close();
}
