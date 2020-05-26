/*!
     Copyright 2020. Coding Studio. All rights reserved.
     BSD License Usage

     [Coding Studio]
     email   : devlee.freebsd@gmail.com
     twitch  : https://www.twitch.tv/codingstudio
     youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "IsoMetric.h"
#include "maincamera.h"
#include "owdrawwidget.h"

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

void MainWindow::mornitoringTimer() {
    QPair<int, int> pair = this->m_ui->widgetOpenWorld->GetMainCamera()->GetIsoMetric()->GetCurrentMetricLocation();
    QString str;
    str = QString::number(pair.first) + ", " + QString::number(pair.second);
    this->m_ui->edtMetricLocation->setText(str);

    QRect rect = this->m_ui->widgetOpenWorld->GetMainCamera()->GetIsoMetric()->GetCurrentMetricPixel();
    str = QString::number(rect.x()) + ", " +
            QString::number(rect.y()) + ", " +
            QString::number(rect.width()) + ", " +
            QString::number(rect.height());
    this->m_ui->edtMetricPixel->setText(str);

    int data = this->m_ui->widgetOpenWorld->GetMainCamera()->GetTileMap()->GetDataMetricLocation(pair.first, pair.second);
    str = QString::number(data);
    this->m_ui->edtMetricData->setText(str);
}

void MainWindow::showEvent(QShowEvent *event)
{
#ifdef DEBUG
    qDebug("한글 깨짐 확인.");
#endif
}

void MainWindow::on_btnShowTileMap_clicked()
{
    this->m_ui->widgetOpenWorld->GetMainCamera()->OptionShowTileMap(true, false);
    this->m_ui->widgetOpenWorld->repaint();
}

void MainWindow::on_btnShowTileMapLine_clicked()
{
    this->m_ui->widgetOpenWorld->GetMainCamera()->OptionShowTileMap(true, true);
    this->m_ui->widgetOpenWorld->repaint();
}

void MainWindow::on_btnShowTileLine_clicked()
{
    this->m_ui->widgetOpenWorld->GetMainCamera()->OptionShowTileMap(false, true);
    this->m_ui->widgetOpenWorld->repaint();
}

void MainWindow::on_btnShowDataMap_clicked()
{
    this->m_ui->widgetOpenWorld->GetMainCamera()->OptionShowTileData(true);
    this->m_ui->widgetOpenWorld->repaint();
}

void MainWindow::on_cboBackgroundColor_currentIndexChanged(int index)
{
    QVariant variant = this->m_ui->cboBackgroundColor->itemData(index);
    QColor color = variant.value<QColor>();
    this->m_ui->widgetOpenWorld->GetMainCamera()->SetBackgroundColor(new QBrush(color));
    this->m_ui->widgetOpenWorld->repaint();
}
