#include "baselight.h"

BaseLight::BaseLight() :
    _intensity(0)
{

}

BaseLight::BaseLight(float intensity, const Point3D &pos) :
    _intensity(intensity),
    SceneObject(pos)

{

}

