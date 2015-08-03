#ifndef AUTHORDIALOG_H
#define AUTHORDIALOG_H

#include <QDialog>

namespace Ui {
class authorDialog;
}

class authorDialog : public QDialog
{
    Q_OBJECT

public:
    int year;
    QString id, authorName, authorNameShort;

public:
    explicit authorDialog(QWidget *parent = 0);
    ~authorDialog();
    void refresh();

private:
    Ui::authorDialog *ui;
};

#endif // AUTHORDIALOG_H
