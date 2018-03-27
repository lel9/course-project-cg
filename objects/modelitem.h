#ifndef MODELITEM_H
#define MODELITEM_H

#include "item.h"
#include "model.h"

class ModelItem : public Item
{
public:
    ModelItem();
    void setModel (const shared_ptr<Model> &model) { _model = model; }
    virtual QGraphicsItem* graphicsItem() const override;
    //virtual QGraphicsItem* graphicsItem(const TransformMatrix &pv,
    //                                     const TransformMatrix &m = TransformMatrix(1,1,1,1)) override;
private:
    shared_ptr<Model> _model;
    QGraphicsItemGroup *drawItems;
};

#endif // MODELITEM_H
