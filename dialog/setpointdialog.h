#ifndef SETPOINTDIALOG_H
#define SETPOINTDIALOG_H

#include <QDialog>
#include <QAbstractButton>

#include "objects/trackpoint_item.h"

namespace Ui {
class SetPointDialog;
}

class SetPointDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetPointDialog(shared_ptr<SceneObject> point, QWidget *parent = 0);
    ~SetPointDialog();

public slots:
    virtual void accept() override;
private slots:
    void on_buttonBox_clicked(QAbstractButton *button);
    //void on_checkBoxGauss_clicked();
    void on_colorPushButton_clicked();
    void setColorWidget(const QColor &color);

private:
    Ui::SetPointDialog *ui;
    shared_ptr<SceneObject> _point;

    bool ok;
};

#endif // SETPOINTDIALOG_H
