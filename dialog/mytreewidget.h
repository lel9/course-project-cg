#ifndef MYTREEWIDGET_H
#define MYTREEWIDGET_H


#include <QAction>
#include <QTreeWidget>

class myTreeWidgetItem : public QTreeWidgetItem
{
    public:
    myTreeWidgetItem(int id) : _id(id) { }
    using QTreeWidgetItem::QTreeWidgetItem;

    ~myTreeWidgetItem() = default;

    void setId(int id) { _id = id; }
    int id() { return _id; }

private:
    int _id;
};

class myTreeWidget : public QTreeWidget
{
    Q_OBJECT

public:
    myTreeWidget(QWidget *parent = 0);

    ~myTreeWidget();

    void addRoot(const QString &name, int id);
    void addChild(const QString &name, int id);
    void showMenu(QTreeWidgetItem *item, QPoint pos);

signals:
    void deleteItem(int index);
    void changeActiveItem(int index);
    void showItem(int index);

public slots:
    void on_customContextMenuRequested(QPoint pos);
    void on_deleteActionClicked();
    void on_changeActionClicked();
    void on_showActionClicked();
    void on_activeItemChanged(int id);

private:
    myTreeWidgetItem *activeRoot;
    myTreeWidgetItem *selectedItem;

    QAction *deleteAction;
    QAction *changeAction;
    QAction *showAction;

    static const int root = QTreeWidgetItem::UserType;
    static const int child = QTreeWidgetItem::UserType + 1;
};

#endif // MYTREEWIDGET_H
