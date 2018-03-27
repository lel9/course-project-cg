#include "animation.h"
#include "ui_animation.h"

#include "objects/model.h"
#include "objects/camera.h"
#include "factories/modelfactory.h"
#include "factories/camera_factory.h"

#include "scenes/animationcanvas.h"

#include <qmath.h>

Animation::Animation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Animation)
{
    ui->setupUi(this);

    animationScene = new AnimationScene;
    AnimationCanvas *canvas = new AnimationCanvas;
    animationScene->setCanvas(canvas);
    connect(canvas, SIGNAL(cameraMoved(float,float)), this, SLOT(transformCamera(float, float)));

    ui->horizontalLayout->addWidget(canvas->widget());

    timer.setInterval(50);
    connect(&timer, SIGNAL(timeout()), this, SLOT(moveModel()));
}

Animation::~Animation()
{
    delete animationScene;
    delete ui;
}

void Animation::transformCamera(float dx, float dy)
{
    bool a = timer.isActive();
    if (a)
        timer.stop();

    weak_ptr<Camera> camera = animationScene->camera();
    if (camera.expired())
        return;

    shared_ptr<Camera> activeCamera = camera.lock();
    activeCamera->transform(MatrixRotateY(qDegreesToRadians(-dx/2)).create());
    activeCamera->transform(MatrixRotateX(qDegreesToRadians(dy/2)).create());
    animationScene->renderModels();

    if (a)
        timer.start();
}

void Animation::moveModel()
{
    animationScene->moveModels();
    animationScene->renderModels();
}

void Animation::on_pushButton_clicked()
{
    timer.stop();
    animationScene->clear();

    ModelFactory f1("D:\\cursovaya\\corpus.obj", "D:\\cursovaya\\corpus.mtl", false);
    shared_ptr<SceneObject> model1 = f1.create();
    ModelFactory f2("D:\\cursovaya\\state.obj", "D:\\cursovaya\\state.mtl", false);
    shared_ptr<SceneObject> model2 = f2.create();
    TransformMatrix m = MatrixShift(Point3D(0,4.5,0)).create();
    ModelFactory f3("D:\\cursovaya\\move1.obj", "D:\\cursovaya\\move1.mtl", true);
    shared_ptr<SceneObject> model3 = f3.create();
    model3->transform(m);
    ModelFactory f4("D:\\cursovaya\\move2.obj", "D:\\cursovaya\\move2.mtl", true);
    shared_ptr<SceneObject> model4 = f4.create();
    model4->transform(m);
    ModelFactory f5("D:\\cursovaya\\move3.obj", "D:\\cursovaya\\move3.mtl", true);
    shared_ptr<SceneObject> model5 = f5.create();
    model5->transform(m);

    CameraFactory fc("D:\\oop\\lr3\\oop_lab3\\camera.txt");
    shared_ptr<SceneObject> camera = fc.create();

    animationScene->registerCamera(camera);
    animationScene->addModel(model1);
    animationScene->addModel(model2);
    animationScene->addModel(model3);
    animationScene->addModel(model4);
    animationScene->addModel(model5);

    shared_ptr<Light> al = make_shared<Light>(Point3D(0,0,0), 0.7);
    al->setItem(make_shared<Item>());
    animationScene->addLight(al);

    shared_ptr<Light> pl = make_shared<Light>(Point3D(10,10,5), 3, PointSource);
    pl->setItem(make_shared<Item>());
    animationScene->addLight(pl);
    shared_ptr<Light> pl1 = make_shared<Light>(Point3D(-11,10,5), 3, PointSource);
    pl1->setItem(make_shared<Item>());
    animationScene->addLight(pl1);
    shared_ptr<Light> pl2 = make_shared<Light>(Point3D(1,5,15), 2, PointSource);
    pl2->setItem(make_shared<Item>());
    animationScene->addLight(pl2);

    animationScene->renderModels();

    ui->pushButton->setEnabled(false);
}

void Animation::on_pushButton_2_clicked()
{
    if (timer.isActive())
    {
        ui->pushButton_2->setText("Начать");
        timer.stop();
    }
    else
    {
        ui->pushButton_2->setText("Остановить");
        timer.start();
    }
}

void Animation::closeEvent(QCloseEvent *)
{
    timer.stop();
}
