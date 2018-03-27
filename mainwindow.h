#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSlider>

#include "scene_manager.h"
#include "dialog/settingdialog.h"
#include "animation.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_openAction_triggered();
    void on_saveDiaAction_triggered();
    void on_exitAction_triggered();

    void on_playAction_triggered();
    void on_stopAction_triggered();
    void on_goToNextFrameAction_triggered();
    void on_goToPrevFrameAction_triggered();

    void on_setPointAction_triggered();
    void on_delPointAction_triggered();
    void movePointAction();
    void setPointAction();

    void on_actionXT_triggered();
    void on_actionVT_triggered();
    void on_actionAT_triggered();

    void on_settingsAction_triggered();
    void on_crossCursor_triggered();
    void on_arrowCursor_triggered();

    void on_sidePanelAction_triggered();

private slots:
    void setVideoButton(const State &state);
    void updateCursorInfo(QPointF pos);
    //void on_showAnimationAction_triggered();

    void on_aboutAuthorAction_triggered();
    void on_aboutProgAction_triggered();

    //void on_InterpolateAction_triggered();


    //void on_action_triggered();

    void on_detectAction_triggered();

    void on_actionFT_triggered();

private:
    Ui::MainWindow *ui;

    SceneManager *manager;
    QMenu *contextMenu;
    SettingDialog *settings;

    //Animation *animation;
};

#endif // MAINWINDOW_H
