#include "aboutdialog.h"
#include "ui_aboutdialog.h"

static const QString COPYRIGHT = QStringLiteral("Copyright 2013-2014 Christian Loose");
static const QString HOMEPAGE = QStringLiteral("<a href=\"http://cloose.github.io/CuteMarkEd\">http://cloose.github.io/CuteMarkEd</a>");

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    ui->messageLabel->setText(QString("<p><b><font size=\"5\">CuteMarkEd</font></b><br>Version %1</p>").arg(qApp->applicationVersion()));

    const QString description = QString("<p>%1<br>%2</p><p>%3</p>")
            .arg(tr("Qt-based, free and open source markdown editor with live HTML preview"))
            .arg(COPYRIGHT)
            .arg(HOMEPAGE);
    ui->descriptionLabel->setText(description);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
