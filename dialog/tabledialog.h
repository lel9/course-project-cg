#ifndef TableDialog_H
#define TableDialog_H

#include <QDialog>
#include <QAbstractButton>
#include <QStringListModel>


namespace Ui {
class TableDialog;
}

#include "ui_tabledialog.h"

class TableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TableDialog(QWidget *parent = 0);
    ~TableDialog();

    virtual void setTableName(const QString &name);
    virtual QString getTableName();
    virtual void setPointList(const QVector<QString> &list);
    virtual QVector<int> getSelectedIndexes();
    virtual int getCheckedRadioButton();
    virtual int getOrder() const { return 0; }
    virtual double getM() const { return 0; }

    virtual void setMultiSelection(bool s);
    virtual void setGroupBoxTitle(const QString &title);

    virtual bool isOk() { return ok; }

    virtual void accept();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

protected:
    Ui::TableDialog *ui;
    bool ok;
};


#endif // TableDialog_H
