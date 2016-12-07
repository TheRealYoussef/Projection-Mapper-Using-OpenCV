#-------------------------------------------------
#
# Project created by QtCreator 2016-12-06T13:11:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Projection-Mapper
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ccl.cpp \
    corresponder.cpp

HEADERS  += mainwindow.h \
    ccl.h \
    corresponder.h

FORMS    += mainwindow.ui

LIBS += -L/usr/local/lib -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_ocl -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab -lrt -lpthread -lm -ldl
