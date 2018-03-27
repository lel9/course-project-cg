#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QAbstractButton>

#include "tracking/opencvfeatureparams.h"

namespace Ui {
class SettingDialog;
}

enum Button { Ok, Apply, Cansel, Unknown };

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = 0);
    ~SettingDialog();

    double getSpeed();
    double getScale();
    double getTimeScale();
    void setSpeed(double speed);

    CVFeatureParams getDetectorParams();

    Button button() const { return butt; }

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::SettingDialog *ui;
    Button butt;
};

#endif // SETTINGDIALOG_H
