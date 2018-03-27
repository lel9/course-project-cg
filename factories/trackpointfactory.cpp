#include "trackpointfactory.h"
#include "objects/trackpoint_item.h"
#include "namecreator.h"

TrackPointFactory::TrackPointFactory(QMenu *menu) :
    _contextMenu(menu)
{

}

shared_ptr<SceneObject> TrackPointFactory::create()
{
    shared_ptr<TrackPoint> trackPoint = make_shared<TrackPoint>();
    shared_ptr<TrackPointItem> item = make_shared<TrackPointItem>(_contextMenu);
    item->setColor(getRandomColor());
    trackPoint->setItem(item);
    trackPoint->setObjectName(NameCreator::getInstance().createPointName());

    return trackPoint;
}

QColor TrackPointFactory::getRandomColor()
{
    QColor color;
    color.setRed(qrand() % 256);
    color.setGreen(qrand() % 256);
    color.setBlue(qrand() % 256);
    return color;
}

