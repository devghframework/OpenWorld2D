################################################################################################
##     Copyright 2020. Coding Studio. All rights reserved.                                    ##
##     BSD License Usage                                                                      ##
##                                                                                            ##
##     [Coding Studio]                                                                        ##
##     Git     : https://github.com/devghframework/OpenWorld2D                                ##
##     email   : devlee.freebsd@gmail.com                                                     ##
##     twitch  : https://www.twitch.tv/codingstudio                                           ##
##     youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber  ##
################################################################################################

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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
    isometric.cpp \
    main.cpp \
    maincamera.cpp \
    mainwindow.cpp \
    owdrawwidget.cpp \
    tilemap.cpp

HEADERS += \
    IsoMetric.h \
    isometric.h \
    maincamera.h \
    mainwindow.h \
    owdrawwidget.h \
    tilemap.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    OpenWorld2d_ko_KR.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
