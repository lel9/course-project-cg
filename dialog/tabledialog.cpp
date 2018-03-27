#include "tabledialog.h"
#include <QMessageBox>

TableDialog::TableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableDialog),
    ok(false)
{
    ui->setupUi(this);
    this->setWindowTitle("Настройка диаграммы");
}

TableDialog::~TableDialog()
{
    delete ui;
}

void TableDialog::setTableName(const QString &name)
{
    ui->lineEdit->setText(name);
}

QString TableDialog::getTableName()
{
    return ui->lineEdit->text();
}

void TableDialog::setPointList(const QVector<QString> &list)
{
    foreach (QString name, list)
        ui->allPointList->addItem(name);
}

QVector<int> TableDialog::getSelectedIndexes()
{
    QVector<int> result;
    for (int i = 0; i < ui->allPointList->count(); i++)
        if (ui->allPointList->item(i)->isSelected())
            result << i;
    return result;
}

int TableDialog::getCheckedRadioButton()
{
    if (ui->radioButton->isChecked())
        return 0;
    if (ui->radioButton_2->isChecked())
        return 1;
    return -1;
}

void TableDialog::setMultiSelection(bool s)
{
    if (s)
        ui->allPointList->setSelectionMode(QAbstractItemView::MultiSelection);
    else
        ui->allPointList->setSelectionMode(QAbstractItemView::SingleSelection);
}

void TableDialog::setGroupBoxTitle(const QString &title)
{
    ui->groupBox_2->setTitle(title);
}

void TableDialog::accept()
{
    if (ok)
        QDialog::accept();
}


void TableDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    if (ui->buttonBox->standardButton(button) == QDialogButtonBox::Ok)
    {
        if (getSelectedIndexes().isEmpty())
            QMessageBox::warning(this, "Ошибка", "Выберите хотя бы одну точку!");
        else
            ok = true;
    }
}
