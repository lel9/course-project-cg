#ifndef OPENCVDETECTOR_H
#define OPENCVDETECTOR_H

#include <vector>

#include <opencv2/imgproc.hpp>

#include "utils/point.h"
#include "objects/opencvimage.h"
#include "tracking/opencvfeatureparams.h"

class OpenCVDetector
{
public:
    OpenCVDetector(const CVFeatureParams &params);
    std::vector<mPointF> find(Image *img) const;

private:
    CVFeatureParams _params;
};

#endif // OPENCVDETECTOR_H
