#ifndef TABLEFTDIALOG_H
#define TABLEFTDIALOG_H

#include "tabledialog.h"
#include <QDoubleSpinBox>

class TableFTDialog : public TableDialog
{
     Q_OBJECT
public:
    explicit TableFTDialog(QWidget *parent = 0);
    ~TableFTDialog();

    virtual double getM() const override;
private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    QDoubleSpinBox *m;
    QLabel *mLabel;
    QHBoxLayout *ml;
};

#endif // TABLEFTDIALOG_H
