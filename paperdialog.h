#ifndef PAPERDIALOG_H
#define PAPERDIALOG_H

#include <QDialog>

namespace Ui {
class paperDialog;
}

class paperDialog : public QDialog
{
    Q_OBJECT

public:
    explicit paperDialog(QWidget *parent = 0);
    ~paperDialog();

private:
    Ui::paperDialog *ui;
};

#endif // PAPERDIALOG_H
