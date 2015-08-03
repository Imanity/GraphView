#include "authordialog.h"
#include "ui_authordialog.h"

authorDialog::authorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::authorDialog)
{
    ui->setupUi(this);
}

authorDialog::~authorDialog()
{
    delete ui;
}

void authorDialog::refresh()
{
    ui->year->setText(QString::number(year));
    ui->id->setText(id);
    ui->authorName->setText(authorName);
    ui->authorNameShort->setText(authorNameShort);
}
