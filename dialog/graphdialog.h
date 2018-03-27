#ifndef GRAPHDIALOG_H
#define GRAPHDIALOG_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class GraphDialog;
}

class GraphDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GraphDialog(QWidget *parent = 0);
    ~GraphDialog();

    bool isOk() { return ok; }

    QString xLabel() const;
    QString yLabel() const;

    double xStart() const;
    double xStop() const;
    double yStart() const;
    double yStop() const;

    void setXLabel(QString label);
    void setYLabel(QString label);
    void setXRange(double lower, double upper);
    void setYRange(double lower, double upper);

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::GraphDialog *ui;
    bool ok;
};

#endif // GRAPHDIALOG_H
