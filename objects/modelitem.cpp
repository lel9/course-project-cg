#include "modelitem.h"
#include "utils/matrix_set.h"

ModelItem::ModelItem()
{
    drawItems = new QGraphicsItemGroup;
}

QGraphicsItem* ModelItem::graphicsItem() const
{
    return drawItems;
}

/*QGraphicsItem *ModelItem::graphicsItem(const TransformMatrix &pv, const TransformMatrix &m)
{
    drawItems = new QGraphicsItemGroup;

    MatrixShift ms(_model->position3D());
    TransformMatrix pvm = pv * (ms.create() * m);

    for (const Edge &edge : _model->getEdges())
    {
        Point3D v1, v2;
        //try
        //{
            v1 = _model->getVertices().at(edge.v1());
            v2 = _model->getVertices().at(edge.v2());
        //}
        //catch (const std::out_of_range& )
        //{
        //    throw DrawException("no vertex");
        //}

        v1.transform(pvm);
        v2.transform(pvm);

        float X1, X2, Y1, Y2;
        X1 = v1.x()/v1.w();
        X2 = v2.x()/v2.w();
        Y1 = v1.y()/v1.w();
        Y2 = v2.y()/v2.w();

        QGraphicsItem *item = new QGraphicsLineItem(X1*_scale.x(), Y1*_scale.y(),
                                                    X2*_scale.x(), Y2*_scale.y());
        drawItems->addToGroup(item);
    }
    return drawItems;
}*/

