#ifndef VIDEOSCENEFACTORY_H
#define VIDEOSCENEFACTORY_H

#include "scenefactory.h"
#include "scenes/video_scene.h"

class VideoSceneFactory : public SceneFactory
{
private:
    QString _title;
    unique_ptr<VideoScene> video;

public:
    VideoSceneFactory(const QString &filename);
    ~VideoSceneFactory() = default;
    virtual shared_ptr<Scene> create();
    virtual Canvas *createCanvas();
};

#endif // VIDEOSCENEFACTORY_H
