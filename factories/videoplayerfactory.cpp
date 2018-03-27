#include "videoplayerfactory.h"
#include "objects/opencvvideoplayer.h"
#include "objects/videoitem.h"

VideoPlayerFactory::VideoPlayerFactory()
{

}

shared_ptr<SceneObject> VideoPlayerFactory::create()
{
    shared_ptr<OpenCVVideoPlayer> player = make_shared<OpenCVVideoPlayer>();
    shared_ptr<OpenCVVideoItem> item = make_shared<OpenCVVideoItem>();
    player->setItem(item);

    return player;
}
