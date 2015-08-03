#include "conferencedialog.h"
#include "ui_conferencedialog.h"

conferenceDialog::conferenceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::conferenceDialog)
{
    ui->setupUi(this);
}

conferenceDialog::~conferenceDialog()
{
    delete ui;
}

void conferenceDialog::refresh()
{
    ui->year->setText(QString::number(year));
    ui->id->setText(id);
    ui->conferenceName->setText(conferenceName);
    ui->conferenceNameShort->setText(conferenceNameShort);
}
