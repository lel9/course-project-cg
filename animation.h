#ifndef ANIMATION_H
#define ANIMATION_H

#include <QWidget>
#include <QTimer>

#include "scenes/animation_scene.h"

namespace Ui {
class Animation;
}

class Animation : public QWidget
{
    Q_OBJECT

public:
    explicit Animation(QWidget *parent = 0);
    ~Animation();


private slots:
    void transformCamera(float dx, float dy);
    void moveModel();

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void closeEvent(QCloseEvent *);

private:
    Ui::Animation *ui;
    AnimationScene *animationScene;

    QTimer timer;
};

#endif // ANIMATION_H
