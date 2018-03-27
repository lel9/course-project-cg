#include "settingdialog.h"
#include "ui_settingdialog.h"

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog),
    butt(Cansel)
{
    ui->setupUi(this);
    this->setWindowTitle("Параметры");
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

double SettingDialog::getSpeed()
{
    return ui->doubleSpinBoxSpeed->value();
}

double SettingDialog::getScale()
{
    return ui->doubleSpinBoxSm->value()/ui->doubleSpinBoxPks->value();
}

double SettingDialog::getTimeScale()
{
    return ui->doubleSpinBoxFrm->value()/ui->doubleSpinBoxSec->value();
}

void SettingDialog::setSpeed(double speed)
{
    ui->doubleSpinBoxSpeed->setValue(speed);
}

CVFeatureParams SettingDialog::getDetectorParams()
{
    CVFeatureParams params;
    params._maxCorners = ui->maxCorners->value();
    params._qualityLevel = ui->qualityLevel->value();
    params._minDistance = ui->minDistance->value();
    params._blockSize = ui->blockSize->value();
    return params;
}


void SettingDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    switch(ui->buttonBox->standardButton(button))
    {
    case QDialogButtonBox::Ok:
        butt = Ok;
        break;
    case QDialogButtonBox::Apply:
        butt = Apply;
        close();
        break;
    case QDialogButtonBox::Cancel:
        butt = Cansel;
        break;
    default:
        butt = Unknown;
    }
}
