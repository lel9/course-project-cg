#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeWidget->setAnimated(true);
    ui->treeWidget->setEnabled(true);
    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->setHeaderLabels(QStringList() << "Открытые видеозаписи");

    manager = new SceneManager;
    connect(manager, SIGNAL(activeSceneStateChanged(State)),
            this, SLOT(setVideoButton(State)));

    manager->setMdiArea(ui->mdiArea);

    connect(ui->treeWidget, SIGNAL(deleteItem(int)),
            manager, SLOT(removeScene(int)));
    connect(ui->treeWidget, SIGNAL(changeActiveItem(int)),
            manager, SLOT(replaceActiveScene(int)));
    connect(ui->treeWidget, SIGNAL(showItem(int)),
            manager, SLOT(showScene(int)));
    connect(manager, SIGNAL(activeSceneChanged(int)),
            ui->treeWidget, SLOT(on_activeItemChanged(int)));

    contextMenu = new QMenu;
    contextMenu->addAction(ui->delPointAction);
    QAction *moveAction = new QAction(tr("Переместить"), this);
    contextMenu->addAction(moveAction);
    QAction *setAction = new QAction(tr("Настроить"), this);
    contextMenu->addAction(setAction);

    connect(moveAction, SIGNAL(triggered()), this, SLOT(movePointAction()));
    connect(setAction,  SIGNAL(triggered()), this, SLOT(setPointAction ()));

    settings = new SettingDialog;
    //animation = new Animation;

}

MainWindow::~MainWindow()
{
    delete manager;
    delete contextMenu;
    delete settings;
    //delete animation;
    delete ui;
}

#include <QFileDialog>
#include <QMessageBox>

#include "factories/video_scene_factory.h"
#include "factories/table_xt_factory.h"
#include "factories/table_vt_factory.h"
#include "factories/table_at_factory.h"
#include "factories/table_interpolate_factory.h"
#include "factories/table_middle_factory.h"
#include "factories/videoplayerfactory.h"
#include "factories/trackpointfactory.h"
#include "dialog/setpointdialog.h"
#include "dialog/settingdialog.h"

void MainWindow::on_openAction_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Открытие файла"),
                                                 QDir::currentPath());

    //QString filename = "D:\\cursovaya\\OpenCv\\video\\3.2.avi";
    if (!filename.isEmpty())
    {
        VideoPlayerFactory vpf;
        shared_ptr<SceneObject> player = vpf.create();

        VideoSceneFactory vsf(filename);
        shared_ptr<Scene> videoScene = vsf.create();

        if (!vsf.isCreated())
            return;

        videoScene->addChild(player);
        static_pointer_cast<VideoScene>(videoScene)->registerPlayer(player);
        connect(videoScene.get(), SIGNAL(updateCursorPos(QPointF)),
                this, SLOT(updateCursorInfo(QPointF)));

        if (videoScene->loadDataFromFile(filename))
        {
            manager->addScene(videoScene);
            manager->replaceActiveScene(videoScene);
            ui->treeWidget->addRoot(videoScene->objectName(), videoScene->id());
        }
        else
            QMessageBox::critical(nullptr, "Ошибка", "Не удалось открыть файл");
    }
}

void MainWindow::on_exitAction_triggered()
{
    close();
    exit(0);
}

void MainWindow::on_playAction_triggered()
{
    weak_ptr<VideoScene> scene = manager->activeScene();
    if (scene.expired())
        return;
    ui->menu->setEnabled(!ui->menu->isEnabled());
    scene.lock()->track();
}

void MainWindow::on_stopAction_triggered()
{
    weak_ptr<VideoScene> scene = manager->activeScene();
    if (scene.expired())
        return;
    scene.lock()->stop();
    ui->menu->setEnabled(true);
}

void MainWindow::on_goToNextFrameAction_triggered()
{
    weak_ptr<VideoScene> scene = manager->activeScene();
    if (scene.expired())
        return;
    scene.lock()->goToNextFrame();
}

void MainWindow::on_goToPrevFrameAction_triggered()
{
    weak_ptr<VideoScene> scene = manager->activeScene();
    if (scene.expired())
        return;
    scene.lock()->goToPrevFrame();
}

void MainWindow::setVideoButton(const State &state)
{
    switch(state)
    {
    case Pause:
        ui->playAction->setIcon(QIcon(":/images/images/control_play_blue_eye_4069.png"));
        ui->playAction->setText("Продолжить слежение");
        break;
    case Play:
        ui->playAction->setIcon(QIcon(":/images/images/control_pause_blue_8339.png"));
        ui->playAction->setText("Пауза");
        break;
    case Stop:
        ui->playAction->setIcon(QIcon(":/images/images/control_play_blue_eye_4069.png"));
        ui->playAction->setText("Начать слежение");
        ui->menu->setEnabled(true);
        if (!manager->activeScene().expired())
        {
            manager->activeScene().lock()->player().lock()->goToNextFrame();
            manager->activeScene().lock()->setEnabled(true);
            manager->activeScene().lock()->disconnectp();
        }
        break;
    default:
        break;
    }
}

void MainWindow::on_setPointAction_triggered()
{
    weak_ptr<VideoScene> scene = manager->activeScene();
    if (scene.expired())
        return;

    TrackPointFactory tpf(contextMenu);
    shared_ptr<TrackPoint> tpn = static_pointer_cast<TrackPoint>(tpf.create());
    scene.lock()->addChild(tpn);
}

void MainWindow::on_sidePanelAction_triggered()
{
    ui->treeWidget->setVisible(!ui->treeWidget->isVisible());
}

void MainWindow::on_delPointAction_triggered()
{
    weak_ptr<VideoScene> vscene = manager->activeScene();
    if (vscene.expired())
        return;

     QVector<shared_ptr<SceneObject>> sc = vscene.lock()->selectedChildren();
     if (sc.isEmpty())
     {
         QMessageBox::warning(this, "Ошибка", "Выделите точки, которые хотите удалить.");
         return;
     }

     if(QMessageBox::question(this, "Подтверждение",
                              "Удалить выделенные точки слежения?") == QMessageBox::Yes)
        for(int i = 0; i < sc.length(); i++)
            foreach (shared_ptr<Scene> scene, manager->scenes())
                scene->removeChild(sc[i]);

}

void MainWindow::movePointAction()
{
    weak_ptr<VideoScene> scene = manager->activeScene();
    if (scene.expired())
        return;

    QVector<shared_ptr<SceneObject>> children = scene.lock()->selectedChildren();
    if (children.empty())
        return;

    children.first()->item()->setMovable(true);
}

void MainWindow::setPointAction()
{
    weak_ptr<VideoScene> scene = manager->activeScene();
    if (scene.expired())
        return;

    QVector<shared_ptr<SceneObject>> children = scene.lock()->selectedChildren();
    if (children.empty())
        return;

    SetPointDialog dia(children.first(), this);
    dia.exec();
}

void MainWindow::on_actionXT_triggered()
{
    weak_ptr<VideoScene> scene = manager->activeScene();
    if (scene.expired())
        return;

    QVector<shared_ptr<SceneObject>> children = scene.lock()->getChildren();
    QVector<shared_ptr<SceneObject>> points;
    for(int i = 0; i < children.length(); i++)
        if (!children[i]->isVideo())
            points.push_back(children[i]);
    if (points.isEmpty())
    {
        QMessageBox::critical(this, "Ошибка", "Задайте хотя бы одну точку слежения!");
        return;
    }

    TableXTFactory txtf(points);
    shared_ptr<Scene> table = txtf.create();

    if (!txtf.isCreated())
        return;

    table->setTimeFormat(scene.lock()->timeFormat() + ".zzz");
    table->setParentId(scene.lock()->id());
    table->setScale(settings->getScale());
    table->setTimeScale(settings->getTimeScale());
    manager->addScene(table);
    ui->treeWidget->addChild(table->objectName(), table->id());

    weak_ptr<VideoPlayer> player =  scene.lock()->player();
    if (player.expired())
        return;
    connect(player.lock().get(), SIGNAL(positionChanged(qint64)),
            table.get(), SLOT(on_currentTimeChanged(qint64)));
}

void MainWindow::on_actionVT_triggered()
{
    if (manager->activeScene().expired())
        return;

    QVector<shared_ptr<Scene>> scenes = manager->scenes();
    QVector<shared_ptr<Scene>> XTScenes;
    foreach (shared_ptr<Scene> scene, scenes)
        if (scene->type() == XT && scene->parentId() == manager->activeScene().lock()->id())
            XTScenes.push_back(scene);

    if (XTScenes.isEmpty())
    {
        QMessageBox::critical(this, "Ошибка", "Добавьте хотя бы одну XT диаграмму для расчета!");
        return;
    }

    TableVTFactory tvtf(XTScenes);
    shared_ptr<Scene> table = tvtf.create();

    if (!tvtf.isCreated())
        return;

    table->setParentId(manager->activeScene().lock()->id());
    manager->addScene(table);
    ui->treeWidget->addChild(table->objectName(), table->id());
}

void MainWindow::on_actionAT_triggered()
{
    if (manager->activeScene().expired())
        return;

    QVector<shared_ptr<Scene>> scenes = manager->scenes();
    QVector<shared_ptr<Scene>> XVTScenes;
    foreach (shared_ptr<Scene> scene, scenes)
        if ((scene->type() == XT) && scene->parentId() ==
                manager->activeScene().lock()->id())
            XVTScenes.push_back(scene);

    if (XVTScenes.isEmpty())
    {
        QMessageBox::critical(this, "Ошибка", "Добавьте хотя бы одну XT диаграмму для расчета!");
        return;
    }

    TableATFactory tatf(XVTScenes);
    shared_ptr<Scene> table = tatf.create();

    if (!tatf.isCreated())
        return;

    table->setParentId(manager->activeScene().lock()->id());
    table->setScale(settings->getScale());
    manager->addScene(table);
    ui->treeWidget->addChild(table->objectName(), table->id());
}

void MainWindow::on_settingsAction_triggered()
{
    weak_ptr<VideoScene> ascene = manager->activeScene();
    if (!ascene.expired())
        settings->setSpeed(ascene.lock()->FPS());

    settings->exec();
    if (settings->button() == Apply)
    {
        if (!ascene.expired())
            ascene.lock()->setFPS(settings->getSpeed());
        double coordScale = settings->getScale();
        double timeScale = settings->getTimeScale();
        foreach (shared_ptr<Scene> scene, manager->scenes())
        {
            if (scene->parentId() == ascene.lock()->id())
            {
                scene->setScale(coordScale);
                scene->setTimeScale(timeScale);
                scene->update();
            }
        }
    }
}

void MainWindow::on_saveDiaAction_triggered()
{
    QString filename = QFileDialog::getExistingDirectory(this,
                       "Выберите папку для сохранения", QDir::currentPath());
    if (!filename.isEmpty())
    {
        QString message;
        foreach (shared_ptr<Scene> scene, manager->scenes())
            if (!scene->save(filename))
                message += scene->objectName() + '\n';
        if (!message.isEmpty())
            QMessageBox::warning(this, "Ошибка сохранения",
                                 "Не удалось сохранить файлы: \n" + message);
        else
            QMessageBox::information(this, "Подтверждение", "Данные успешно сохранены.");
    }
}

void MainWindow::on_crossCursor_triggered()
{
    weak_ptr<VideoScene> scene = manager->activeScene();
    if (!scene.expired())
        scene.lock()->setCursor(QCursor(Qt::CrossCursor));
}

void MainWindow::on_arrowCursor_triggered()
{
    weak_ptr<VideoScene> scene = manager->activeScene();
    if (!scene.expired())
        scene.lock()->setCursor(QCursor(Qt::ArrowCursor));
}

void MainWindow::updateCursorInfo(QPointF pos)
{
    ui->statusBar->showMessage(QString::number(pos.x()) + ", " +
                               QString::number(pos.y()));
}

//void MainWindow::on_showAnimationAction_triggered()
//{
//    animation->show();
//}

void MainWindow::on_aboutAuthorAction_triggered()
{
    QMessageBox::information(this, "Об авторе", "Автор программы: Яковлева Ольга Викторовна,\n"
                                                "e-mail: olg-199774@mail.ru\n"
                                                "телефон: 8-917-512-54-96");
}

void MainWindow::on_aboutProgAction_triggered()
{
    QMessageBox::information(this, "О программе", "Разработано с использованием Qt Creator 3.5.1");
}

//void MainWindow::on_InterpolateAction_triggered()
//{
//    if (manager->activeScene().expired())
//        return;

//    QVector<shared_ptr<Scene>> scenes = manager->scenes();
//    QVector<shared_ptr<Scene>> XVATScenes;
//    foreach (shared_ptr<Scene> scene, scenes)
//        if ((scene->type() == XT || scene->type() == VT || scene->type() == AT)
//                && scene->parentId() == manager->activeScene().lock()->id())
//            XVATScenes.push_back(scene);

//    if (XVATScenes.isEmpty())
//    {
//        QMessageBox::critical(this, "Ошибка", "Добавьте хотя бы одну диаграмму для расчета!");
//        return;
//    }

//    TableInterpolateFactory tif(XVATScenes);
//    shared_ptr<Scene> table = tif.create();

//    if (!tif.isCreated())
//        return;

//    table->setParentId(manager->activeScene().lock()->id());
//    table->setScale(settings->getScale());
//    manager->addScene(table);
//    ui->treeWidget->addChild(table->objectName(), table->id());

//    const QVector<double> coefs = table->getApprCoef(0);
//    if (coefs.length() < 2)
//        return;
//    QString text = "y = " + QString::number(coefs[0]) + " + " + QString::number(coefs[1]) + "*x";
//    for (int i = 2; i < coefs.size(); i++)
//        text += " + " + QString::number(coefs[i]) + "*x^" + QString::number(i);
//    QMessageBox::information(this, "Коэффициенты", text);
//}

//void MainWindow::on_action_triggered()
//{
//    if (manager->activeScene().expired())
//        return;

//    QVector<shared_ptr<Scene>> scenes = manager->scenes();
//    QVector<shared_ptr<Scene>> XVATScenes;
//    foreach (shared_ptr<Scene> scene, scenes)
//        if ((scene->type() == XT || scene->type() == VT || scene->type() == AT)
//                && scene->parentId() == manager->activeScene().lock()->id())
//            XVATScenes.push_back(scene);

//    if (XVATScenes.isEmpty())
//    {
//        QMessageBox::critical(this, "Ошибка", "Добавьте хотя бы одну диаграмму для расчета!");
//        return;
//    }

//    TableMiddleFactory tif(XVATScenes);
//    shared_ptr<Scene> table = tif.create();

//    if (!tif.isCreated())
//        return;

//    table->setParentId(manager->activeScene().lock()->id());
//    manager->addScene(table);
//    ui->treeWidget->addChild(table->objectName(), table->id());
//}

#include "tracking/opencvdetector.h"

void MainWindow::on_detectAction_triggered()
{
    if (manager->activeScene().expired())
        return;

    shared_ptr<VideoScene> vscene = manager->activeScene().lock();

    if (vscene->player().expired())
        return;

    if (vscene->getChildren().length() > 1 &&
            QMessageBox::question(this, "Подверждение", "Удалить текущие точки перед поиском?")
            == QMessageBox::Yes)
    {
        auto sc = vscene->getChildren();
        for(int i = 0; i < sc.length(); i++)
            foreach (shared_ptr<Scene> scene, manager->scenes())
                if (!sc[i]->isVideo())
                    scene->removeChild(sc[i]);
    }

    shared_ptr<VideoPlayer> player = vscene->player().lock();
    OpenCVDetector detector(settings->getDetectorParams());
    vector<mPointF> features = detector.find(player->currentFrame());

    TrackPointFactory tpf(contextMenu);
    for (auto f : features)
    {
        shared_ptr<TrackPoint> tpn = static_pointer_cast<TrackPoint>(tpf.create());
        vscene->addChild(tpn);
        auto size = tpn->item()->size();
        tpn->item()->setPosition(QPointF(f.x()-size.width()/2., f.y()-size.height()/2.));
    }
}

#include "factories/table_ft_factory.h"
void MainWindow::on_actionFT_triggered()
{
    if (manager->activeScene().expired())
        return;

    QVector<shared_ptr<Scene>> scenes = manager->scenes();
    QVector<shared_ptr<Scene>> ATScenes;
    foreach (shared_ptr<Scene> scene, scenes)
        if ((scene->type() == AT || scene->type() == XT) && scene->parentId() ==
                manager->activeScene().lock()->id())
            ATScenes.push_back(scene);

    if (ATScenes.isEmpty())
    {
        QMessageBox::critical(this, "Ошибка", "Добавьте хотя бы одну XT или AT диаграмму для расчета!");
        return;
    }

    TableFTFactory tftf(ATScenes);
    shared_ptr<Scene> table = tftf.create();

    if (!tftf.isCreated())
        return;

    table->setParentId(manager->activeScene().lock()->id());
    table->setScale(settings->getScale());
    manager->addScene(table);
    ui->treeWidget->addChild(table->objectName(), table->id());
}
