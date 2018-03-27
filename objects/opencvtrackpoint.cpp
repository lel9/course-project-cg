#include "opencvtrackpoint.h"

OpenCVTrackPoint::OpenCVTrackPoint()
{
    _tracker = new OpenCVTracker;
}

void OpenCVTrackPoint::setStartFrame(Image *img)
{
    //_tracker->setStartConfig(img, point);
}

void OpenCVTrackPoint::findObjectPos(Image *img)
{
    //point = _tracker->track(img);
}

