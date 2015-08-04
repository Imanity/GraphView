#ifndef TOPICDIALOG_H
#define TOPICDIALOG_H

#include <QDialog>

namespace Ui {
class topicDialog;
}

class topicDialog : public QDialog
{
    Q_OBJECT

public:
    QString topicWords, topicDocuments;

public:
    explicit topicDialog(QWidget *parent = 0);
    ~topicDialog();
    void refresh();

private:
    Ui::topicDialog *ui;
};

#endif // TOPICDIALOG_H
