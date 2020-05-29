/*!
     Copyright 2020. Coding Studio. All rights reserved.
     BSD License Usage

     [Coding Studio]
     Git     : https://github.com/devghframework/OpenWorld2D
     email   : devlee.freebsd@gmail.com
     twitch  : https://www.twitch.tv/codingstudio
     youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber

     - 파일수정
        QT설치디렉토리 : Qt/5.14.2/clang_64/mkspecs/macx-clang/qmake.conf
        QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9
 */

#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
#ifdef DEBUG
#pragma region 전처리기
    qDebug("The path/name of this file is %s", __FILE__);
    qDebug("The current line is %d", __LINE__);
    qDebug("The current system date is %s", __DATE__);
    qDebug("The current system time is %s", __TIME__);
    #ifdef __STDC__
        qDebug("The compiler conforms with the ANSI C standard");
    #else
        qDebug("The compiler doesn't conform with the ANSI C standard");
    #endif
    #ifdef __cplusplus
        qDebug("The compiler is working with C++");
    #else
        qDebug("The compiler is working with C");
    #endif
#pragma endregion 전처리기
#endif

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
