#include "scene_manager.h"
#include <QMdiArea>

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{
    if (!_activeScene.expired())
        _activeScene.lock()->stop();

    _scenes.clear();
}

void SceneManager::addScene(const shared_ptr<Scene> &scene)
{
    _scenes.push_back(scene);

    QWidget *widget = scene->widget();
    QMdiSubWindow *window = new myMdiSubWindow(widget);
    mdiArea->addSubWindow(window);
    widget->show();
}

void SceneManager::removeScene(int id)
{
    foreach(shared_ptr<Scene> scene, _scenes)
        if (scene->id() == id || scene->parentId() == id)
        {
            QList<QMdiSubWindow*> list = mdiArea->subWindowList();
            foreach (QMdiSubWindow *window, list)
                if (window->widget() == scene->widget())
                    window->close();

            _scenes.removeOne(scene);
            if (!_activeScene.expired() && scene == _activeScene.lock())
                getNewActiveScene();
        }

}

void SceneManager::replaceActiveScene(shared_ptr<Scene> scene)
{
    if (scene->type() != Video)
        return;

    if (!_activeScene.expired())
    {
        shared_ptr<VideoScene> oldScene = _activeScene.lock();
        oldScene->setEnabled(false);
        oldScene->setCursor(QCursor(Qt::ArrowCursor));
        weak_ptr<VideoPlayer> player = oldScene->player();
        if (player.expired())
        {
            shared_ptr<VideoPlayer> vplayer = player.lock();
            QObject::disconnect(vplayer.get(), SIGNAL(mediaStateChanged(State)),
                                this, SIGNAL(activeSceneStateChanged(State)));
        }
        _activeScene.reset();
    }

    shared_ptr<VideoScene> vscene = static_pointer_cast<VideoScene>(scene);
    _activeScene = vscene;
    QObject::connect(vscene.get(), SIGNAL(playerChanged(shared_ptr<VideoPlayer>)),
                     this, SLOT(on_scenePlayerChanged(shared_ptr<VideoPlayer>)));
    scene->setEnabled(true);

    if (!vscene->player().expired())
    {
        shared_ptr<VideoPlayer> vplayer = vscene->player().lock();
        QObject::connect(vplayer.get(), SIGNAL(mediaStateChanged(State)),
                         this, SIGNAL(activeSceneStateChanged(State)));
    }
}

void SceneManager::replaceActiveScene(int id)
{
    foreach(shared_ptr<Scene> scene, _scenes)
        if (scene->id() == id)
        {
            replaceActiveScene(scene);
            emit activeSceneChanged(scene->id());
        }
}

void SceneManager::showScene(int id)
{
    foreach(shared_ptr<Scene> scene, _scenes)
        if (scene->id() == id)
        {
            QList<QMdiSubWindow*> list = mdiArea->subWindowList();
            foreach (QMdiSubWindow *window, list)
                if (window->widget() == scene->widget())
                    window->setVisible(!window->isVisible());
        }
}


weak_ptr<VideoScene> SceneManager::activeScene()
{
    return _activeScene;
}

void SceneManager::on_scenePlayerChanged(shared_ptr<VideoPlayer> player)
{
    if (_activeScene.expired())
        return;

    shared_ptr<VideoScene> vscene = _activeScene.lock();
    if (QObject::sender() == vscene.get())
    {
        if (!vscene->player().expired())
        {
            shared_ptr<VideoPlayer> vplayer = vscene->player().lock();
            QObject::disconnect(vplayer.get(), SIGNAL(mediaStateChanged(State)),
                             this, SIGNAL(activeSceneStateChanged(State)));
            QObject::disconnect(vplayer.get(), SIGNAL(positionChanged(qint64)),
                             this, SIGNAL(activeScenePositionChanged(qint64)));
            QObject::disconnect(vplayer.get(), SIGNAL(durationChanged(qint64)),
                             this, SIGNAL(activeSceneDurationChanged(qint64)));
        }

        QObject::connect(player.get(), SIGNAL(mediaStateChanged(State)),
                         this, SIGNAL(activeSceneStateChanged(State)));
        QObject::connect(player.get(), SIGNAL(positionChanged(qint64)),
                         this, SIGNAL(activeScenePositionChanged(qint64)));
        QObject::connect(player.get(), SIGNAL(durationChanged(qint64)),
                         this, SIGNAL(activeSceneDurationChanged(qint64)));
    }
}

void SceneManager::getNewActiveScene()
{
    foreach (shared_ptr<Scene> scene, _scenes)
        if (scene->type() == Video)
        {
            replaceActiveScene(scene);
            emit activeSceneChanged(scene->id());
        }
}
