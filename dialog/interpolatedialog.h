#ifndef INTERPOLATEDIALOG_H
#define INTERPOLATEDIALOG_H

#include "tabledialog.h"
#include <QSpinBox>

class InterpolateDialog : public TableDialog
{
    Q_OBJECT

public:
    explicit InterpolateDialog(QWidget *parent = 0);
    ~InterpolateDialog();

    virtual int getOrder() const override;

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    QSpinBox *Polinome;
    QLabel *PolinomeLabel;
    QHBoxLayout *l2;
};

#endif // INTERPOLATEDIALOG_H
