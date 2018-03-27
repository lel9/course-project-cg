#include "graphdialog.h"
#include "ui_graphdialog.h"

GraphDialog::GraphDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphDialog),
    ok(false)
{
    ui->setupUi(this);
    this->setWindowTitle("Свойства");
}

GraphDialog::~GraphDialog()
{
    delete ui;
}

double GraphDialog::xStart() const
{
    return ui->xBegin->value();
}

double GraphDialog::xStop() const
{
    return ui->xEnd->value();
}

double GraphDialog::yStart() const
{
    return ui->yBegin->value();
}

double GraphDialog::yStop() const
{
    return ui->yEnd->value();
}

QString GraphDialog::xLabel() const
{
    return ui->xLabel->text();
}

QString GraphDialog::yLabel() const
{
    return ui->yLabel->text();
}

void GraphDialog::setXLabel(QString label)
{
    ui->xLabel->setText(label);
}

void GraphDialog::setYLabel(QString label)
{
    ui->yLabel->setText(label);
}

void GraphDialog::setXRange(double lower, double upper)
{
    ui->xBegin->setValue(lower);
    ui->xEnd->setValue(upper);
}

void GraphDialog::setYRange(double lower, double upper)
{
    ui->yBegin->setValue(lower);
    ui->yEnd->setValue(upper);
}


void GraphDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    if (ui->buttonBox->standardButton(button) == QDialogButtonBox::Ok)
    {
        ok = true;
    }
}
