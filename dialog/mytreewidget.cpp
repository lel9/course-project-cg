#include "mytreewidget.h"
#include <QMenu>


myTreeWidget::myTreeWidget(QWidget *parent) :
    QTreeWidget(parent), activeRoot(nullptr)
{

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(on_customContextMenuRequested(QPoint)));

    deleteAction = new QAction(tr("Удалить"), 0);
    showAction   = new QAction(tr("Показать/Скрыть"), 0);
    changeAction = new QAction(tr("Сделать активной видеозаписью"), 0);

    connect(deleteAction, SIGNAL(triggered(bool)),
            this, SLOT(on_deleteActionClicked()));
    connect(changeAction, SIGNAL(triggered(bool)),
            this, SLOT(on_changeActionClicked()));
    connect(showAction, SIGNAL(triggered(bool)),
            this, SLOT(on_showActionClicked()));
}

myTreeWidget::~myTreeWidget()
{
    delete deleteAction;
    delete showAction;
    delete changeAction;
}

void myTreeWidget::addRoot(const QString &name, int id)
{
    myTreeWidgetItem *item = new myTreeWidgetItem(this, root);
    item->setText(0, name);
    item->setId(id);
    item->setWhatsThis(0, name);

    if (activeRoot)
        activeRoot->setTextColor(0, Qt::black);

    activeRoot = item;
    activeRoot->setExpanded(true);
    activeRoot->setTextColor(0, Qt::red);
}

void myTreeWidget::addChild(const QString &name, int id)
{
    if (activeRoot)
    {
        myTreeWidgetItem *item = new myTreeWidgetItem(activeRoot, child);
        item->setText(0, name);
        item->setId(id);
    }
}

void myTreeWidget::showMenu(QTreeWidgetItem *item, QPoint pos)
{
    QMenu menu;

    switch(item->type())
    {
    case root:
        menu.addAction(changeAction);
    case child:
        menu.addAction(showAction);
        menu.addAction(deleteAction);
        break;
    }

    menu.exec(pos);
}

void myTreeWidget::on_customContextMenuRequested(QPoint pos)
{
    QTreeWidgetItem *item = itemAt(pos);
    if (item)
    {
        selectedItem = static_cast<myTreeWidgetItem*>(item);
        showMenu(item, mapToGlobal(pos));
    }
}

void myTreeWidget::on_deleteActionClicked()
{
    emit deleteItem(selectedItem->id());
    for (int i = 0; i < selectedItem->childCount(); i++)
        selectedItem->removeChild(selectedItem->child(i));
    if (selectedItem == activeRoot)
        activeRoot = nullptr;
    delete selectedItem;
}

void myTreeWidget::on_changeActionClicked()
{
    emit changeActiveItem(selectedItem->id());
}

void myTreeWidget::on_showActionClicked()
{
    emit showItem(selectedItem->id());
}

void myTreeWidget::on_activeItemChanged(int id)
{
    if (activeRoot)
        activeRoot->setTextColor(0, Qt::black);

    QTreeWidgetItemIterator it(this);
    while (*it)
    {
        if (static_cast<myTreeWidgetItem*>((*it))->id() == id)
        {
            activeRoot = static_cast<myTreeWidgetItem*>((*it));
            activeRoot->setTextColor(0, Qt::red);
            break;
        }
        ++it;
    }
}
