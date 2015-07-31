#-------------------------------------------------
#
# Project created by QtCreator 2015-07-29T01:01:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GraphView
TEMPLATE = app


SOURCES += main.cpp \
    Graph/fgraph.cpp \
    Graph/fpaperconferenceauthorgraph.cpp \
    Graph/ftopicgraph.cpp \
    Node/fnode.cpp \
    Node/fpapernode.cpp \
    Node/fconferencenode.cpp \
    Node/fauthornode.cpp \
    Node/ftopicnode.cpp \
    Edge/fedge.cpp \
    Edge/fdirectededge.cpp \
    Edge/fundirectededge.cpp \
    paperconferenceauthorwindow.cpp \
    loaddialog.cpp \
    aboutdialog.cpp

HEADERS  += \
    Graph/fgraph.h \
    Graph/fpaperconferenceauthorgraph.h \
    Graph/ftopicgraph.h \
    Node/fnode.h \
    Node/fpapernode.h \
    Node/fconferencenode.h \
    Node/fauthornode.h \
    Node/ftopicnode.h \
    Edge/fedge.h \
    Edge/fdirectededge.h \
    Edge/fundirectededge.h \
    paperconferenceauthorwindow.h \
    loaddialog.h \
    aboutdialog.h

FORMS    += \
    paperconferenceauthorwindow.ui \
    loaddialog.ui \
    aboutdialog.ui

win32 {
    LIBS += "D:/Program Files/OGDF/x64/Debug/ogdf.lib"
    LIBS += "D:/Program Files/OGDF/x64/Debug/coin.lib"
    INCLUDEPATH += "D:/Program Files/OGDF/include"
}

unix {
    LIBS += "/Users/Imanity/Documents/OGDF/_release/libOGDF.a"
    LIBS += "/Users/Imanity/Documents/OGDF/_release/libCOIN.a"
    INCLUDEPATH += "/Users/Imanity/Documents/OGDF/include"
}

RESOURCES += \
    resource.qrc
