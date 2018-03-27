#include "qt_video_canvas.h"
#include "objects/trackpoint_item.h"
#include "utils/converter.h"

QtVideoCanvas::QtVideoCanvas() :
    hasVideoItem(false)
{
    _widget = new myVideoWidget;
    connect(_widget->_slider, SIGNAL(sliderReleased()),
            this, SLOT(on_sliderReleased()));
    connect(_widget->_view, SIGNAL(cursorMoved(QPointF)),
            this, SIGNAL(updateCursorPos(QPointF)));
}

QtVideoCanvas::~QtVideoCanvas()
{
    delete _widget;
}

void QtVideoCanvas::addItem(const shared_ptr<Item> &item)
{
    QGraphicsItem *graphicsItem = item->graphicsItem();
    _widget->_scene->addItem(graphicsItem);

    if (hasVideoItem)
    {
        graphicsItem->setPos(_widget->_view->videoItem()->boundingRect().width()/2,
                            _widget->_view->videoItem()->boundingRect().height()/2);
        graphicsItem->setParentItem(_widget->_view->videoItem());
    }

    Canvas::addItem(item);
}

void QtVideoCanvas::removeItem(const shared_ptr<Item> &item)
{
    _widget->_scene->removeItem(item->graphicsItem());
    Canvas::removeItem(item);
}

void QtVideoCanvas::registerVideoItem(const shared_ptr<Item> &item)
{
    QGraphicsItem *grItem = item->graphicsItem();
    _widget->_view->setSceneRect(grItem->boundingRect());
    _widget->_view->setVideoItem(grItem);
    hasVideoItem = true;
}

void QtVideoCanvas::setCursor(const QCursor &cursor)
{
    if (hasVideoItem)
        _widget->_view->videoItem()->setCursor(cursor);
}

void QtVideoCanvas::updateCurrentTime(const QTime &current)
{
    _widget->_timeLabel->setText(current.toString(_timeFormat) + " / " +
                                 _totalTime.toString(_timeFormat));
    _widget->_slider->setValue(TimeConverter::QTimeToSec(current));
    Canvas::updateCurrentTime(current);
}

void QtVideoCanvas::updateTotalTime(const QTime &duration)
{
    _timeFormat = "mm:ss";
    if (duration.hour())
        _timeFormat = "hh:mm:ss";

    _widget->_timeLabel->setText(duration.toString(_timeFormat));
    _widget->_slider->setRange(0, TimeConverter::QTimeToSec(duration));
    Canvas::updateTotalTime(duration);
}

void QtVideoCanvas::setEnabled(bool enable)
{
    _widget->_slider->setEnabled(enable);
    Canvas::setEnabled(enable);
}

void QtVideoCanvas::on_sliderReleased()
{
    emit sliderReleased(_widget->_slider->value()*1000);
}

myVideoWidget::myVideoWidget(QWidget *parent) :
    QWidget(parent)
{
    _scene = new QGraphicsScene;
    _view = new myGraphicsView;
    _view->setScene(_scene);

    _infoLayout = new QHBoxLayout;
    _timeLabel = new QLabel;
    _slider = new QSlider(Qt::Horizontal);
    _infoLayout->addWidget(_slider);
    _infoLayout->addWidget(_timeLabel);

    _mainLayout = new QVBoxLayout;
    _mainLayout->addWidget(_view);
    _mainLayout->addLayout(_infoLayout);

    this->setLayout(_mainLayout);
}

myVideoWidget::~myVideoWidget()
{
    delete _scene;
    delete _view;
    delete _infoLayout;
    delete _mainLayout;
}

void myVideoWidget::closeEvent(QCloseEvent *)
{
    this->hide();
}

#include <QResizeEvent>
#include <QTransform>

myGraphicsView::myGraphicsView() :
    _videoItem(nullptr)
{
    this->viewport()->setMouseTracking(true);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

myGraphicsView::~myGraphicsView()
{

}

void myGraphicsView::setVideoItem(QGraphicsItem *videoItem)
{
    _videoItem = videoItem;
}

void myGraphicsView::resizeEvent(QResizeEvent *event)
{
    // вызов родительского метода ДО выполнения метода потомка,
    // иначе ломается центрирование
    QGraphicsView::resizeEvent(event);

    if (_videoItem)
    {
        qreal s;
        QRectF bRect = _videoItem->boundingRect();
        qreal bRectHeight = bRect.height();
        qreal bRectWidth = bRect.width();

        QSize newSize = event->size();
        int newHeight = newSize.height();
        int newWidth = newSize.width();

        qreal sh = newHeight/bRectHeight;
        qreal sw = newWidth/bRectWidth;
        if (sh < sw)
            s = sh;
        else
            s = sw;

        qreal x = bRectWidth / 2;
        qreal y = bRectHeight / 2;
        _videoItem->setTransform(QTransform().translate(x, y).scale(s,s).translate(-x, -y));
        this->centerOn(x, y);
    }
}

void myGraphicsView::wheelEvent(QWheelEvent *)
{
    // ничего не делаем
}

void myGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
    if (_videoItem && _videoItem->isUnderMouse() &&
            _videoItem->cursor().shape() == Qt::CrossCursor)
        emit cursorMoved(_videoItem->mapFromScene(mapToScene(mapFromGlobal(cursor().pos()))));
}

/*#include <QTransform>
void myGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if (_point && _videoItem && _videoItem->isUnderMouse())
    {
        QPointF p = mapToScene(event->pos());
        _point->setPos(mapToParent(p.toPoint()));
        this->setCursor(Qt::CrossCursor);
    }
    else
        this->setCursor(Qt::ArrowCursor);
}

void myGraphicsView::mousePressEvent(QMouseEvent *)
{
    if (_point && _videoItem && _videoItem->isUnderMouse())
    {
        _point->show();
        _point = nullptr;
        this->setCursor(Qt::ArrowCursor);
    }
}*/
