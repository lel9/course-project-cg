#include "tableftdialog.h"
#include <QMessageBox>

TableFTDialog::TableFTDialog(QWidget *parent) :
    TableDialog(parent)
{
    m = new QDoubleSpinBox;
    m->setRange(0,1000000);
    m->setValue(22.4);
    mLabel = new QLabel("Масса бабы, кг");
    ml = new QHBoxLayout;
    ml->addWidget(m);
    ml->addWidget(mLabel);
    ui->verticalLayoutMain->addLayout(ml);

    setGroupBoxTitle("Выберите диаграмму для расчета силы");
}

TableFTDialog::~TableFTDialog()
{
    delete m;
    delete mLabel;
    delete ml;
}

double TableFTDialog::getM() const
{
    return m->value();
}

void TableFTDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    if (ui->buttonBox->standardButton(button) == QDialogButtonBox::Ok)
    {
        if (getSelectedIndexes().isEmpty())
            QMessageBox::warning(this, "Ошибка", "Выберите диаграмму для расчета!");
        else
            ok = true;
    }
}
