#include "light.h"

Light::Light()
{

}

Light::Light(const Point3D &pos, float intensity, const LightType &type) :
    SceneObject(pos),
    _intensity(intensity),
    _type(type)

{

}

