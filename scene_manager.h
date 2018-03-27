#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "scenes/video_scene.h"

#include <QObject>
#include <QMdiSubWindow>

class myMdiSubWindow : public QMdiSubWindow
{
public:
    myMdiSubWindow(QWidget *widget) { this->setWidget(widget); }
    ~myMdiSubWindow() = default;
    void closeEvent(QCloseEvent *)
    {
        this->setVisible(false);
    }
};

class SceneManager : public QObject
{
    Q_OBJECT

public:
    explicit SceneManager();
    SceneManager(const SceneManager &) = delete;
    SceneManager & operator=(const SceneManager &) = delete;
    ~SceneManager();

    QVector<shared_ptr<Scene>> scenes() { return _scenes; }

    weak_ptr<VideoScene> activeScene();

    void setMdiArea(QMdiArea *area) { mdiArea = area; }

public slots:
    void addScene(const shared_ptr<Scene> &scene);
    void removeScene(int id);
    void replaceActiveScene(shared_ptr<Scene> scene);
    void replaceActiveScene(int id);
    void showScene(int id);

signals:
    void activeSceneStateChanged(const State &state);
    void activeSceneChanged(int id);

private slots:
    void on_scenePlayerChanged(shared_ptr<VideoPlayer> player);
    void getNewActiveScene();

private:
    QVector<shared_ptr<Scene>> _scenes;
    weak_ptr<VideoScene> _activeScene;

    QMdiArea *mdiArea;
};

#endif // SCENEMANAGER_H
