#include "loaddialog.h"
#include "ui_loaddialog.h"
#include "paperconferenceauthorwindow.h"
#include "aboutdialog.h"

LoadDialog::LoadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadDialog)
{
    ui->setupUi(this);
    connect(ui->PCAGraphButton, SIGNAL(clicked()), this, SLOT(onPCAGraphButtonClicked()));
    connect(ui->aboutButton, SIGNAL(clicked()), this, SLOT(onAboutButtonClicked()));
}

LoadDialog::~LoadDialog()
{
    delete ui;
}

void LoadDialog::onPCAGraphButtonClicked()
{
    PaperConferenceAuthorWindow *newWindow = new PaperConferenceAuthorWindow();
    newWindow->show();
}

void LoadDialog::onAboutButtonClicked()
{
    aboutDialog *newWindow = new aboutDialog();
    newWindow->show();
}
