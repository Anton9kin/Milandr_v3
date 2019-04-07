#-------------------------------------------------
#
# Project created by QtCreator 2019-03-13T11:57:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Milandr
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    targetdialog.cpp \
    classes/processor.cpp \
    utils/utils.cpp \
    mcuconfiguration.cpp \
    classes/ui/configbutton.cpp \
    aboutdialog.cpp \
    classes/ui/customview.cpp \
    widgets/pinouts.cpp \
    classes/ui/pin.cpp \
    classes/ui/package.cpp \
    classes/ui/package_h16_48_1b.cpp \
    classes/ui/package_lqfp48.cpp \
    classes/ui/package_h18_64_1b.cpp

HEADERS += \
        mainwindow.h \
    targetdialog.h \
    classes/processor.h \
    utils/utils.h \
    mcuconfiguration.h \
    classes/ui/configbutton.h \
    aboutdialog.h \
    classes/ui/customview.h \
    widgets/pinouts.h \
    classes/ui/pin.h \
    classes/ui/package.h \
    classes/ui/package_h16_48_1b.h \
    classes/ui/package_lqfp48.h \
    classes/ui/package_h18_64_1b.h

FORMS += \
        mainwindow.ui \
    targetdialog.ui \
    mcuconfiguration.ui \
    aboutdialog.ui \
    widgets/pinouts.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc
