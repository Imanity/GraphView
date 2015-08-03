#ifndef PAPERDIALOG_H
#define PAPERDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class paperDialog;
}

class paperDialog : public QDialog
{
    Q_OBJECT

public:
    int year, dateFrom, pageFrom;
    QString authors, id, paperTitle, paperTitleShort;

public:
    explicit paperDialog(QWidget *parent = 0);
    ~paperDialog();
    void refresh();

private:
    Ui::paperDialog *ui;
};

#endif // PAPERDIALOG_H
