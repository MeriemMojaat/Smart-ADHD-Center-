QT       += core gui  serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Atelier_Arduino_v2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

QT+= core gui charts network multimediawidgets serialport

QT       += core gui sql network multimedia multimediawidgets charts printsupport widgets axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT+= charts network
QT       += core gui
QT+=sql

QT       += core gui multimediawidgets multimedia


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += console

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    connection.cpp \
    importvideolink.cpp \
    main.cpp \
    mainwindow.cpp \
    playerframe.cpp \
    resource.cpp \
    smtp.cpp

HEADERS += \
    CONNECTION.h \
    arduino.h \
    mainwindow.h \
    playerframe.h \
    resource.h \
    smtp.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ui_icons/Add File.png \
    ui_icons/Music Record_96px.png \
    ui_icons/Mute_48px.png \
    ui_icons/Voice_48px.png \
    ui_icons/blue-music.jpg \
    ui_icons/exit_48px.png \
    ui_icons/fastforward.png \
    ui_icons/file.png \
    ui_icons/gradient_blue.png \
    ui_icons/mediaplayer.png \
    ui_icons/pause.png \
    ui_icons/play.png \
    ui_icons/sound.png \
    ui_icons/speedup.png \
    ui_icons/stop.png
