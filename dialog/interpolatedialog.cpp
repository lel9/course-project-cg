#include "interpolatedialog.h"
#include <QMessageBox>

InterpolateDialog::InterpolateDialog(QWidget *parent) :
    TableDialog(parent)
{
    Polinome = new QSpinBox;
    Polinome->setRange(2,10);
    PolinomeLabel = new QLabel("Степень полинома");
    l2 = new QHBoxLayout;
    l2->addWidget(Polinome);
    l2->addWidget(PolinomeLabel);
    ui->verticalLayoutMain->addLayout(l2);

    setGroupBoxTitle("Выберите диаграмму для аппроксимации");
}

InterpolateDialog::~InterpolateDialog()
{
    delete Polinome;
    delete PolinomeLabel;
    delete l2;
}

int InterpolateDialog::getOrder() const
{
    return Polinome->value();
}

void InterpolateDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    if (ui->buttonBox->standardButton(button) == QDialogButtonBox::Ok)
    {
        if (getSelectedIndexes().isEmpty())
            QMessageBox::warning(this, "Ошибка", "Выберите хотя бы одну диаграмму!");
        else
            ok = true;
    }
}
