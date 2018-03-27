#ifndef BASELIGHT_H
#define BASELIGHT_H

#include "scene_object.h"

class BaseLight : public SceneObject
{
public:
    BaseLight();
    BaseLight(float intensity, const Point3D &pos);

    void setIntensity(float intensity) { _intensity = intensity; }
    float intensity() const { return _intensity; }

protected:
    float _intensity;
};

#endif // BASELIGHT_H
