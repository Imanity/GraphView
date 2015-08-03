#ifndef CONFERENCEDIALOG_H
#define CONFERENCEDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class conferenceDialog;
}

class conferenceDialog : public QDialog
{
    Q_OBJECT

public:
    int year;
    QString id, conferenceName, conferenceNameShort;

public:
    explicit conferenceDialog(QWidget *parent = 0);
    ~conferenceDialog();
    void refresh();

private:
    Ui::conferenceDialog *ui;
};

#endif // CONFERENCEDIALOG_H
