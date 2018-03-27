#ifndef VIDEO_SCENE_H
#define VIDEO_SCENE_H

#include "scene.h"
#include "videocanvas.h"
#include "objects/videoplayer.h"

class VideoScene : public Scene
{
    Q_OBJECT

public:
    VideoScene();
    virtual ~VideoScene();

    virtual void setCanvas(Canvas *canvas);

    virtual void addChild(const shared_ptr<SceneObject> &child) override;
    virtual Type type() override { return Video; }
    virtual shared_ptr<Scene> clone() override { return make_shared<VideoScene>(); }
    virtual bool loadDataFromFile(const QString &filename) override;
    virtual bool save(QString &) override { return true; }

    virtual void track();
    virtual void stop();
    virtual void goToNextFrame();
    virtual void goToPrevFrame();    

    virtual void registerPlayer(const shared_ptr<SceneObject> &player);

    virtual void setFPS(double fps);
    virtual double FPS();
    virtual bool isPlaying();

    void disconnectp();

    virtual weak_ptr<VideoPlayer> player() { return _player; }

signals:
    void playerChanged(shared_ptr<VideoPlayer> player);

public slots:
    void setVideoPosition(qint64 pos);

private slots:
    void updateTrackPoint(Image *img);
    void setVideoDuration(qint64 duration);
    void on_videoPositionChanged(qint64 pos);


protected:
    weak_ptr<VideoPlayer> _player;
};

#endif // VIDEO_SCENE_H
