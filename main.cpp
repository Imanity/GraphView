#include <QObject>
#include <QApplication>
#include "loaddialog.h"
#include "paperconferenceauthorwindow.h"

int main(int argc,char* argv[]){
    QApplication app(argc, argv);
    LoadDialog dialog;
    dialog.show();
    return app.exec();
}
