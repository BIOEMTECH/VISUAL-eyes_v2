#-------------------------------------------------
#
# Project created by QtCreator 2021-12-02T14:23:14
#
#-------------------------------------------------

QT += core gui
QT += widgets
QT += sql
QT += network
QT += printsupport
CONFIG += debug_and_release_target
QTPLUGIN += qsqlmysql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
DEFINES += QT_NO_VERSION_TAGGING
TARGET = PETsys_app
TEMPLATE = app

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
#DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


INCLUDEPATH+=/usr/include/mysql \
       /usr/local/qwt-6.1.4/include \
       /usr/local/include/qtermwidget5 \
       /usr/local/include/qtermwidget5/extend \
       /usr/local/include/boost \
       /usr/local/include/opencv \
       /usr/include/iniparser \
       /home/bioemtech/root/include \
       /$$PWD/Window_Theme

LIBS+=-L/usr/local/Qt-5.11.3/lib -lQt5OpenGL

LIBS+=-L/usr/lib -lqtermwidget5
LIBS+=-L/usr/local/qwt-6.1.4/lib -lqwt
LIBS+=-L/usr/local/lib -lftd2xx

LIBS+=-L/usr/lib/x86_64-linux-gnu -liniparser
LIBS+=-L/home/bioemtech/boost_1_65_1/boost1.65_build/lib -lboost_regex

LIBS+=-L/home/bioemtech/root/lib -lSpectrum -lCore -lHist -lGpad -lMatrix -lMathCore -lRIO -lGraf -lImt -lThread  -lMultiProc -ltbb -lNet

LIBS += -L/home/bioemtech/opencv3.4/opencv/build/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_videoio
LIBS += -L/home/bioemtech/opencv3.4/opencv/build/lib -lopencv_imgcodecs -lopencv_highgui -lz
LIBS+=`pkg-config --cflags --libs gstreamer-1.0 gstreamer-app-1.0 gstreamer-riff-1.0 gstreamer-pbutils-1.0 gtk+-x11-2.0`
LIBS+=-L/usr/local/lib -lv4l1 -lv4l2 -lIlmImf -lImath -lIex -lHalf -lIlmThread -latk-1.0 -lgio-2.0 -lpangoft2-1.0 -lpangocairo-1.0 -lgdk_pixbuf-2.0 -lcairo -lpango-1.0 -lfontconfig -lgobject-2.0 -lfreetype -lgthread-2.0 -lglib-2.0 -ldc1394 -lavcodec -lavformat -lavutil -lswscale -lstdc++ -ldl -lm -lpthread -lrt -lgstreamer-1.0 -lgtk-x11-2.0 -lgdk-x11-2.0

SOURCES += \
        sources/isotope.cpp \
        sources/imageCapture.cpp \
        sources/main.cpp \
        sources/appWindow.cpp \
        sources/betaEye.cpp \
        sources/arduino.cpp \
        sources/CameraWorker.cpp \
        sources/PostProcessing.cpp \
        sources/Search.cpp \
        sources/operatorDialog.cpp \
        sources/detailsDialog.cpp \
        sources/mergedialog.cpp \
        sources/DAQcounter.cpp \
        sources/readRawDataPipe.cpp \
        sources/timeSettings.cpp \
        sources/continueStudy.cpp \
        sources/database_connection.cpp \
        sources/PETsysConnection.cpp \
        sources/PETsysWorker.cpp \
        sources/readinputinfo.cpp \
        sources/roiManager.cpp \
        sources/imageFusion.cpp \
        Window_Theme/framelesswindow/framelesswindow.cpp \
        Window_Theme/framelesswindow/windowdragger.cpp \
        sources/clickablelabel.cpp \
        sources/petsysDAQ.cpp \
        sources/temperatureControl.cpp \
        sources/castor.cpp \
        sources/gamma_eye.cpp \
        sources/gammacamera.cpp \
        sources/SPECTworker.cpp \
        sources/fpga.cpp \
        sources/udpServer.cpp \
        sources/rlDeconv.cpp \
        sources/calibrationTime.cpp \
        sources/calibrationDialog.cpp \
        sources/calibrationExit.cpp


HEADERS += \
        Includes/BasicExcel.hpp \
        Includes/ExcelFormat.h \
        Includes/ftd2xx.h \
        Includes/resizeExample.hpp \
        Includes/WinTypes.h \
        Includes/dicomEncoder.hpp \
        headers/database_connection.h \
        headers/appWindow.h \
        headers/betaEye.h \
        headers/CameraWorker.h \
        headers/arduino.h \
        headers/PostProcessing.h \
        headers/Search.h \
        headers/imageCapture.hpp \
        headers/operatorDialog.h \
        headers/detailsDialog.h \
        headers/mergedialog.h \
        headers/ColorMap.h \
        headers/DAQcounter.h \
        headers/continueStudy.h \
        headers/isotope.h \
        headers/readRawDataPipe.h \
        headers/timeSettings.h \
        headers/PETsysConnection.h \
        headers/PETsysWorker.h \
        headers/readinputinfo.h \
        headers/roiManager.hpp \
        headers/imageFusion.hpp \
        Window_Theme/framelesswindow/framelesswindow.h \
        Window_Theme/framelesswindow/windowdragger.h \
        headers/clickablelabel.h \
        headers/petsysDAQ.h \
        headers/veyesutils.h \
        headers/temperatureControl.h \
        headers/castor.h \
        headers/gamma_eye.h \
        headers/gammacamera.h \
        headers/SPECTworker.h \
        headers/fpga.h \
        headers/udpServer.h \
        headers/rlDeconv.hpp \
        headers/calibrationTime.h \
        headers/calibrationDialog.h \
        headers/calibrationExit.h


FORMS += \
        forms/appWindow.ui \
        forms/PostProcessing.ui \
        forms/Search.ui \
        forms/betaEye.ui \
        forms/gamma_eye.ui \
        forms/timeSettings.ui \
        forms/calibrationTime.ui \
        forms/operatorDialog.ui \
        forms/detailsDialog.ui \
        forms/calibrationDialog.ui \
        forms/mergedialog.ui \
        forms/calibrationExit.ui

RESOURCES += \
    qrc/icons.qrc \
    Window_Theme/framelesswindow.qrc

LIBS+=-L$$OUT_PWD/lib -ldicomEncoder -lExcelFormat
