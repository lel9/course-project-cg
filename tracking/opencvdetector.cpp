#include "opencvdetector.h"

OpenCVDetector::OpenCVDetector(const CVFeatureParams &params) :
    _params(params)
{

}

std::vector<mPointF> OpenCVDetector::find(Image *img) const
{
    OpenCVImage *cvImg = static_cast<OpenCVImage*>(img);
    cv::Mat frame, gray;
    cvImg->mat().copyTo(frame);
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    std::vector<cv::Point2f> res;
    cv::goodFeaturesToTrack(gray, res, _params._maxCorners, _params._qualityLevel,
                            _params._minDistance, cv::noArray(), _params._blockSize);

    std::vector<mPointF> wres;
    for (auto p : res)
        wres.push_back(mPointF(p.x, p.y));
    return wres;
}

