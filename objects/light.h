#ifndef LIGHT_H
#define LIGHT_H

#include "scene_object.h"

enum LightType { PointSource, Ambient };

class Light : public SceneObject
{
public:
    Light();
    Light(const Point3D &pos, float intensity, const LightType &type = Ambient);

    void setIntensity(float intensity) { _intensity = intensity; }
    float intensity() const { return _intensity; }

    void setType(const LightType &type) { _type = type; }
    LightType type() const { return _type; }


protected:
    float _intensity;
    LightType _type;
};

#endif // LIGHT_H
