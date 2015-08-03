#include "paperdialog.h"
#include "ui_paperdialog.h"

paperDialog::paperDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::paperDialog)
{
    ui->setupUi(this);
}

paperDialog::~paperDialog()
{
    delete ui;
}

void paperDialog::refresh()
{
    ui->year->setText(QString::number(year));
    ui->authors->setText(authors);
    ui->dateFrom->setText(QString::number(dateFrom));
    ui->id->setText(id);
    ui->pageFrom->setText(QString::number(pageFrom));
    ui->pageTitle->setText(paperTitle);
    ui->pageTitleShort->setText(paperTitleShort);
}
