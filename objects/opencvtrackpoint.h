#ifndef OPENCVTRACKPOINT_H
#define OPENCVTRACKPOINT_H

#include "scene_object.h"
#include "tracking/opencvtracker.h"

#include "opencv2/imgproc.hpp"
using namespace cv;

class OpenCVTrackPoint : public SceneObject
{
public:
    OpenCVTrackPoint();
    ~OpenCVTrackPoint();

    void setStartFrame(Image *img) override;
    virtual void findObjectPos(Image *img) override;

    virtual Tracker* tracker() override { return _tracker; }

private:
    Tracker *_tracker;
};

#endif // OPENCVTRACKPOINT_H
