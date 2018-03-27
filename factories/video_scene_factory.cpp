#include "video_scene_factory.h"
#include "scenes/qt_video_canvas.h"
#include "scenes/video_scene.h"

VideoSceneFactory::VideoSceneFactory(const QString &filename) :
    _title(filename)
{

}

shared_ptr<Scene> VideoSceneFactory::create()
{
    video = make_unique<VideoScene>();
    createCanvas();
    video->setObjectName(_title);
    video->setId(NameCreator::getInstance().createSceneId());
    _isCreated = true;

    return std::move(video);
}

Canvas *VideoSceneFactory::createCanvas()
{
    QtVideoCanvas *canvas = new QtVideoCanvas;
    canvas->widget()->setWindowTitle(_title);
    video->setCanvas(canvas);
    return canvas;
}

