#-------------------------------------------------
#
# Project created by QtCreator 2017-11-18T22:17:37
#
#-------------------------------------------------

QT       += core gui

CONFIG   += C++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MotionAnalize
TEMPLATE = app

RESOURCES += \
    icons.qrc


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog/mytreewidget.cpp \
    dialog/setpointdialog.cpp \
    dialog/settingdialog.cpp \
    dialog/tabledialog.cpp \
    factories/grayimagefactory.cpp \
    factories/namecreator.cpp \
    factories/scenefactory.cpp \
    factories/sceneobjectfactory.cpp \
    factories/table_at_factory.cpp \
    factories/table_vt_factory.cpp \
    factories/table_xt_factory.cpp \
    factories/tablefactory.cpp \
    factories/trackpointfactory.cpp \
    factories/video_scene_factory.cpp \
    factories/videoplayerfactory.cpp \
    objects/edge.cpp \
    objects/gray_image.cpp \
    objects/image.cpp \
    objects/item.cpp \
    objects/model.cpp \
    objects/opencvplayer.cpp \
    objects/opencvvideoplayer.cpp \
    objects/point3d.cpp \
    objects/scene_object.cpp \
    objects/trackpoint_item.cpp \
    objects/videoitem.cpp \
    objects/videoplayer.cpp \
    qcustomplot/qcustomplot.cpp \
    scenes/canvas.cpp \
    scenes/graphcanvas.cpp \
    scenes/qt_video_canvas.cpp \
    scenes/scene.cpp \
    scenes/tablecanvas.cpp \
    scenes/tablescene.cpp \
    scenes/tablext.cpp \
    scenes/video_scene.cpp \
    tracking/derivative.cpp \
    tracking/derivativecentral.cpp \
    tracking/gaussianblur.cpp \
    tracking/templatetracker.cpp \
    tracking/tracker.cpp \
    utils/converter.cpp \
    utils/matrix.cpp \
    utils/rect.cpp \
    utils/size.cpp \
    utils/transformmatrix.cpp \
    scene_manager.cpp \
    factories/modelfactory.cpp \
    utils/filereader.cpp \
    utils/file_reader_base.cpp \
    animation.cpp \
    objects/modelitem.cpp \
    objects/camera.cpp \
    factories/camera_factory.cpp \
    utils/matrix_set.cpp \
    objects/polygon.cpp \
    objects/cameraitem.cpp \
    utils/zbuffer.cpp \
    objects/material.cpp \
    objects/rgb.cpp \
    objects/light.cpp \
    objects/vertex.cpp \
    factories/table_interpolate_factory.cpp \
    dialog/interpolatedialog.cpp \
    scenes/animation_scene.cpp \
    scenes/animationcanvas.cpp \
    tracking/mathtable.cpp \
    tracking/gauss.cpp \
    factories/table_middle_factory.cpp \
    tracking/opencvtracker.cpp \
    objects/opencvimage.cpp \
    tracking/opencvdetector.cpp \
    tracking/opencvfeatureparams.cpp \
    dialog/graphdialog.cpp \
    factories/table_ft_factory.cpp \
    dialog/tableftdialog.cpp

HEADERS  += mainwindow.h \
    dialog/mytreewidget.h \
    dialog/setpointdialog.h \
    dialog/settingdialog.h \
    dialog/tabledialog.h \
    factories/grayimagefactory.h \
    factories/namecreator.h \
    factories/scenefactory.h \
    factories/sceneobjectfactory.h \
    factories/table_at_factory.h \
    factories/table_vt_factory.h \
    factories/table_xt_factory.h \
    factories/tablefactory.h \
    factories/trackpointfactory.h \
    factories/video_scene_factory.h \
    factories/videoplayerfactory.h \
    objects/edge.h \
    objects/gray_image.h \
    objects/image.h \
    objects/item.h \
    objects/model.h \
    objects/opencvplayer.h \
    objects/opencvvideoplayer.h \
    objects/point3d.h \
    objects/scene_object.h \
    objects/trackpoint_item.h \
    objects/videoitem.h \
    objects/videoplayer.h \
    qcustomplot/qcustomplot.h \
    scenes/canvas.h \
    scenes/graphcanvas.h \
    scenes/qt_video_canvas.h \
    scenes/scene.h \
    scenes/tablecanvas.h \
    scenes/tablescene.h \
    scenes/tablext.h \
    scenes/video_scene.h \
    tracking/derivative.h \
    tracking/derivativecentral.h \
    tracking/gaussianblur.h \
    tracking/templatetracker.h \
    tracking/tracker.h \
    utils/converter.h \
    utils/matrix.h \
    utils/rect.h \
    utils/size.h \
    utils/transformmatrix.h \
    scene_manager.h \
    factories/modelfactory.h \
    utils/filereader.h \
    utils/file_reader_base.h \
    animation.h \
    objects/modelitem.h \
    objects/camera.h \
    factories/camera_factory.h \
    utils/matrix_set.h \
    scenes/animationcanvas.h \
    animationscene.h \
    scenes/animation_scene.h \
    objects/polygon.h \
    objects/cameraitem.h \
    utils/zbuffer.h \
    objects/material.h \
    objects/rgb.h \
    objects/light.h \
    objects/vertex.h \
    factories/table_interpolate_factory.h \
    dialog/interpolatedialog.h \
    tracking/interpolator.h \
    tracking/mathtable.h \
    tracking/interpolator.hpp \
    tracking/gauss.h \
    factories/table_middle_factory.h \
    tracking/opencvtracker.h \
    objects/opencvimage.h \
    tracking/opencvdetector.h \
    tracking/opencvfeatureparams.h \
    dialog/graphdialog.h \
    factories/table_ft_factory.h \
    dialog/tableftdialog.h

FORMS    += mainwindow.ui \
    dialog/setpointdialog.ui \
    dialog/settingdialog.ui \
    dialog/tabledialog.ui \
    animation.ui \
    dialog/graphdialog.ui

LIBS += -L"C:/Qt/opencv/build/bin/"

LIBS += "C:\Qt\opencv\build\bin\libopencv_core320.dll"
LIBS += "C:\Qt\opencv\build\bin\libopencv_highgui320.dll"
LIBS += "C:\Qt\opencv\build\bin\libopencv_imgcodecs320.dll"
LIBS += "C:\Qt\opencv\build\bin\libopencv_imgproc320.dll"
LIBS += "C:\Qt\opencv\build\bin\libopencv_features2d320.dll"
LIBS += "C:\Qt\opencv\build\bin\libopencv_calib3d320.dll"
LIBS += "C:\Qt\opencv\build\bin\libopencv_video320.dll"
LIBS += "C:\Qt\opencv\build\bin\libopencv_videoio320.dll"

INCLUDEPATH += C:\Qt\opencv\build\install\include
DEPENDPATH += C:\Qt\opencv\build\install\include

QMAKE_CXXFLAGS_DEBUG += -g3 -pg
QMAKE_LFLAGS_DEBUG += -pg -lgmon
