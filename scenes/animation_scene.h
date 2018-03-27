#ifndef ANIMATIONSCENE_H
#define ANIMATIONSCENE_H

#include "scene.h"
#include "objects/model.h"
#include "objects/camera.h"
#include "objects/light.h"

enum Direction { Up, Down };

class AnimationScene : public Scene
{
    Q_OBJECT

public:
    AnimationScene();
    Type type() override;

    virtual shared_ptr<Scene> clone() override {return make_shared<AnimationScene>(); }

    void addModel(const shared_ptr<SceneObject> &model);
    void registerCamera (const shared_ptr<SceneObject> &camera);
    void addLight(const shared_ptr<SceneObject> &light);

    void clear();

    void renderModels();
    void moveModels();

    weak_ptr<Camera> camera() { return activeCamera; }
    QVector<weak_ptr<Model>> model() { return models; }

private:
    QVector<weak_ptr<Model>> models;
    QVector<weak_ptr<Light>> lights;
    weak_ptr<Camera> activeCamera;

    Direction dir;

};

#endif // ANIMATIONSCENE_H
