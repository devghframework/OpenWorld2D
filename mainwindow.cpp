/*!
     Copyright 2020. Coding Studio. All rights reserved.
     BSD License Usage

     [Coding Studio]
     Git     : https://github.com/devghframework/OpenWorld2D
     email   : devlee.freebsd@gmail.com
     twitch  : https://www.twitch.tv/codingstudio
     youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber

     아래와 같은 오류가 발생한다면 qmake.conf에 문구를 추가한다.
     "Undefined symbols for architecture x86_64"

     QT설치디렉토리 : Qt/5.14.2/clang_64/mkspecs/macx-clang/qmake.conf
     QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "IsoMetric.h"
#include "maincamera.h"
#include "owdrawwidget.h"

#include <QDebug>
#include <QMainWindow>
#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QString>
#include <QPixmap>
#include <QImageReader>
#include <QMouseEvent>
#include <QPoint>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QTimer>
#include <QFileDialog>
#include <QItemEditorFactory>

#define DEBUG

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
{
    this->m_ui->setupUi(this);

    setMouseTracking(true);

    this->m_ui->cboBackgroundColor->addItem("Black", QColor(Qt::black));
    this->m_ui->cboBackgroundColor->addItem("White", QColor(Qt::white));
    this->m_ui->cboBackgroundColor->addItem("Red", QColor(Qt::red));
    this->m_ui->cboBackgroundColor->addItem("Green", QColor(Qt::green));
    this->m_ui->cboBackgroundColor->addItem("Blue", QColor(Qt::blue));

    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(mornitoringTimer()));
    this->timer->start(1000);
}

MainWindow::~MainWindow()
{
    this->timer->stop();
    delete this->m_ui;
}

void MainWindow::mornitoringTimer()
{
    // 화면내 매트릭 위치
    QPoint point = this->m_ui->widgetOpenWorld->GetMainCamera()->GetIsoMetric()->GetCurrentMetricLocation();
    QString str;
    str = QString::number(point.x()) + ", " + QString::number(point.y());
    this->m_ui->edtMetricLocation->setText(str);

    // 매트릭 위치의 픽셀 데이타
    QRect rect = this->m_ui->widgetOpenWorld->GetMainCamera()->GetIsoMetric()->GetCurrentMetricPixel();
    str = QString::number(rect.x()) + ", " +
            QString::number(rect.y()) + ", " +
            QString::number(rect.width()) + ", " +
            QString::number(rect.height());
    this->m_ui->edtMetricPixel->setText(str);

    // 화면 가장자리 터치 이벤트
    int borderDir = this->m_ui->widgetOpenWorld->GetBorderToucDir();
    auto metaEnum = QMetaEnum::fromType<TileMap::BORDER_DIR>();
    str = metaEnum.valueToKey(borderDir);
    this->m_ui->edtBorderTouchDir->setText(str);

    // 매트릭 데이타내의 좌표
    QPoint *dataPoint = this->m_ui->widgetOpenWorld->GetMainCamera()->GetTileMap()->GetMetricDataLocation(point.x(), point.y());
    if(dataPoint != nullptr) {
        str = QString("%1, %2").arg(dataPoint->x()).arg(dataPoint->y());
        this->m_ui->edtMetricDataLocation->setText(str);

        // 매트릭 위치의 데이타
        int data = this->m_ui->widgetOpenWorld->GetMainCamera()->GetTileMap()->GetDataMetricDataLocation(dataPoint->x(), dataPoint->y());
        str = QString::number(data);
        this->m_ui->edtMetricData->setText(str);
    }
}


void MainWindow::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);

#ifdef DEBUG
    qDebug("한글 깨짐 확인.");
#endif
}


void MainWindow::on_cboBackgroundColor_currentIndexChanged(int index)
{
    QVariant variant = this->m_ui->cboBackgroundColor->itemData(index);
    QColor color = variant.value<QColor>();
    this->m_ui->widgetOpenWorld->GetMainCamera()->SetBackgroundColor(new QBrush(color));
    this->m_ui->widgetOpenWorld->repaint();
}


void MainWindow::on_btnLoadBackgroundImage_clicked()
{
    QString sModulePath = QCoreApplication::applicationDirPath();

    QString strFilter = "이미지 파일 (*.bmp *.png *.jpeg *.jpg *.gif) ;; All files (*.*)";
    QString strFileName = QFileDialog::getOpenFileName(this, "Open a file", sModulePath , strFilter);

    if(QString(strFileName).isEmpty()==false) {
        this->m_ui->widgetOpenWorld->GetMainCamera()->GetTileMap()->SetTileImage(strFileName.toUtf8());
        this->m_ui->widgetOpenWorld->GetMainCamera()->GetTileMap()->OptionShowDefaultTileMapImage(false);
        this->m_ui->widgetOpenWorld->GetMainCamera()->GetTileMap()->OptionScroll(this->m_ui->chkScroll->isChecked());
        this->m_ui->widgetOpenWorld->repaint();
    }
}


void MainWindow::on_chkScroll_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    this->m_ui->widgetOpenWorld->GetMainCamera()->GetTileMap()->OptionScroll(this->m_ui->chkScroll->isChecked());
}


void MainWindow::on_chkShowTileMap_stateChanged(int arg1)
{
    Q_UNUSED(arg1);

    this->m_ui->widgetOpenWorld->GetMainCamera()->OptionShowTileMap(this->m_ui->chkShowTileMap->isChecked(), false);
    this->m_ui->widgetOpenWorld->repaint();
}


void MainWindow::on_chkShowTileLine_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    this->m_ui->widgetOpenWorld->GetMainCamera()->OptionShowTileMap(false, this->m_ui->chkShowTileLine->isChecked());
    this->m_ui->widgetOpenWorld->repaint();
}


void MainWindow::on_chkShowTileMapLine_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    this->m_ui->widgetOpenWorld->GetMainCamera()->OptionShowTileMap(this->m_ui->chkShowTileMapLine->isChecked(), this->m_ui->chkShowTileMapLine->isChecked());
    this->m_ui->widgetOpenWorld->repaint();
}


void MainWindow::on_chkShowDataMap_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    this->m_ui->widgetOpenWorld->GetMainCamera()->OptionShowTileData(this->m_ui->chkShowDataMap->isChecked());
    this->m_ui->widgetOpenWorld->repaint();
}
