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

QT += charts
QT+= core gui charts network multimediawidgets serialport

QT       += core gui sql network multimedia multimediawidgets charts printsupport widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


QT       += core gui  \
    quick
QT       +=sql

QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets quickwidgets
QT += widgets quickwidgets

TARGET = CRUUD
TEMPLATE = app

CONFIG += c++11

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
    DuMesengerConnectionDialog.cpp \
    appointment.cpp \
    arduino.cpp \
    authentication.cpp \
    camera.cpp \
    connection.cpp \
    employee.cpp \
    event.cpp \
    excel.cpp \
    main.cpp \
    mainwindow.cpp \
    patient.cpp \
    playerframe.cpp \
    qrcode.cpp \
    resource.cpp \
    smtp.cpp \
    treatment.cpp \
    widget.cpp

HEADERS += \
    DuMesengerConnectionDialog.h \
    appointment.h \
    arduino.h \
    authentication.h \
    camera.h \
    connection.h \
    employee.h \
    event.h \
    excel.h \
    mainwindow.h \
    patient.h \
    playerframe.h \
    qrcode.h \
    resource.h \
    smtp.h \
    treatment.h \
    widget.h

FORMS += \
    DuMesengerConnectionDialog.ui \
    authentication.ui \
    camera.ui \
    mainwindow.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


