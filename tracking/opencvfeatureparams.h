#ifndef OPENCVFEATUREPARAMS_H
#define OPENCVFEATUREPARAMS_H


struct CVFeatureParams
{
    CVFeatureParams() { }
    CVFeatureParams(int maxCorners, double qualityLevel, double minDistance, int blockSize) :
        _maxCorners(maxCorners), _qualityLevel(qualityLevel), _minDistance(minDistance), _blockSize(blockSize)
    { }
    int _maxCorners;
    double _qualityLevel;
    double _minDistance;
    int _blockSize;
};

#endif // OPENCVFEATUREPARAMS_H
