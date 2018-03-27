#ifndef QTVIDEOCANVAS_H
#define QTVIDEOCANVAS_H

#include "canvas.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTime>

#include "objects/videoitem.h"

class myGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    myGraphicsView();
    ~myGraphicsView();

    void setVideoItem(QGraphicsItem *videoItem);
    QGraphicsItem *videoItem() { return _videoItem; }

    void resizeEvent(QResizeEvent *event);
    void wheelEvent(QWheelEvent *);
    void mouseMoveEvent(QMouseEvent *event);

signals:
    void cursorMoved(QPointF);

private:
    QGraphicsItem *_videoItem;
};

class myVideoWidget : public QWidget
{
    Q_OBJECT

public:
    myVideoWidget(QWidget *parent = 0);
    ~myVideoWidget();

    QGraphicsScene *_scene;
    myGraphicsView *_view;
    QLabel *_timeLabel;
    QSlider *_slider;
    QHBoxLayout *_infoLayout;
    QVBoxLayout *_mainLayout;

    void closeEvent(QCloseEvent *);
};

class QtVideoCanvas : public Canvas
{
    Q_OBJECT

public:
    QtVideoCanvas();
    ~QtVideoCanvas();

    virtual void addItem(const shared_ptr<Item> &item) override;
    virtual void removeItem(const shared_ptr<Item> &item) override;

    virtual QWidget *widget() override { return _widget; }

    virtual void updateCurrentTime(const QTime &current) override;
    virtual void updateTotalTime(const QTime &duration) override;

    virtual void setEnabled(bool enable) override;

    virtual void registerVideoItem(const shared_ptr<Item> &item) override;
    virtual void setCursor(const QCursor &cursor) override;

private slots:
    void on_sliderReleased();

private:
    myVideoWidget *_widget;
    bool hasVideoItem;
};

#endif // QTVIDEOCANVAS_H
