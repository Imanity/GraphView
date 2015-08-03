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
