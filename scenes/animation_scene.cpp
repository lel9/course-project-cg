#include "animation_scene.h"

AnimationScene::AnimationScene() :
    dir(Down)
{

}

Type AnimationScene::type()
{
    return Animate;
}

#include "utils/zbuffer.h"

void AnimationScene::addModel(const shared_ptr<SceneObject> &model)
{
    shared_ptr<Model> workModel = static_pointer_cast<Model> (model);
    models << workModel;
    Scene::addChild(model);
}

void AnimationScene::registerCamera(const shared_ptr<SceneObject> &camera)
{
    activeCamera.reset();
    activeCamera = static_pointer_cast<Camera>(camera);
    Scene::addChild(camera);
}

void AnimationScene::addLight(const shared_ptr<SceneObject> &light)
{
    lights << static_pointer_cast<Light>(light);
    Scene::addChild(light);
}

void AnimationScene::clear()
{
    _children.clear();
}

void AnimationScene::renderModels()
{
    if (activeCamera.expired())
        return;
    shared_ptr<Camera> workCamera = activeCamera.lock();
    ZBuffer zBuffer;
    zBuffer.setImage(workCamera->item()->image());
    zBuffer.setCamera(workCamera);

    for (weak_ptr<Light> &light : lights)
        if (!light.expired())
            zBuffer.addLightSource(light.lock());

    for (weak_ptr<Model> &model : models)
        if (!model.expired())
            zBuffer.renderModel(model.lock());

    _canvas->update();
}

void AnimationScene::moveModels()
{
    for (weak_ptr<Model> &model : models)
    {
        if (!model.expired())
        {
            shared_ptr<Model> wmodel = model.lock();
            if (wmodel->isMovingModel())
            {
                TransformMatrix m;
                if (wmodel->position3D().y() <= -1)
                    dir = Up;
                if (wmodel->position3D().y() >= 4.5)
                    dir = Down;
                if (dir == Up)
                    m = MatrixShift(Point3D(0,0.4,0)).create();
                if (dir == Down)
                    m = MatrixShift(Point3D(0,-0.85,0)).create();

                wmodel->transform(m);
            }
        }
    }
}
