#include "topicdialog.h"
#include "ui_topicdialog.h"

topicDialog::topicDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::topicDialog)
{
    ui->setupUi(this);
}

topicDialog::~topicDialog()
{
    delete ui;
}

void topicDialog::refresh()
{
    ui->topicWords->setText(topicWords);
    ui->topicDocuments->setText(topicDocuments);
}
