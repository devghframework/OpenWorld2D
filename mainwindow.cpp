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
#include "isometric/isometric.h"
#include "camera/maincamera.h"
#include "openworldwidget/owdrawwidget.h"

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


/*!
 * \brief MainWindow::MainWindow 어플리케이션 생성자
 * \param parent
 */
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
    this->timer->start(500);
}


/*!
 * \brief MainWindow::~MainWindow 객체 소멸자
 */
MainWindow::~MainWindow()
{
    this->timer->stop();
    delete this->m_ui;
}


/*!
 * \brief MainWindow::mornitoringTimer 모니터링 타이머 함수
 * 모니터링 내용
 * 1. 화면내 매트릭 좌표
 * 2. 매트릭 위치의 픽셀 데이타
 * 3. 화면 가장자리 터치 이벤트
 * 4. 매트릭 데이타내의 좌표
 * 5. 매트릭 데이타 좌표의 데이타
 */
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


/*!
 * \brief MainWindow::showEvent 윈도우 Show event
 * \param event
 */
void MainWindow::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);

#ifdef DEBUG
    qDebug("한글이 깨지는지 확인하는 문자열 == No problem if you see this string.");
#endif
}


/*!
 * \brief MainWindow::on_cboBackgroundColor_currentIndexChanged 배경색 선택 콤보박스 인덱스 변경 함수
 * \param index
 */
void MainWindow::on_cboBackgroundColor_currentIndexChanged(int index)
{
    QVariant variant = this->m_ui->cboBackgroundColor->itemData(index);
    QColor color = variant.value<QColor>();
    this->m_ui->widgetOpenWorld->GetMainCamera()->SetBackgroundColor(new QBrush(color));
    this->m_ui->widgetOpenWorld->repaint();
}


/*!
 * \brief MainWindow::on_btnLoadBackgroundImage_clicked 타일이미지를 파일로 부터 로딩하는 함수
 */
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


/*!
 * \brief MainWindow::on_chkShowDefaultTileMap_stateChanged 기본 타일맵 이미지 보여주기 여부 콤보박스 상태변경 이벤트
 * \param arg1
 */
void MainWindow::on_chkShowDefaultTileMap_stateChanged(int arg1)
{
    Q_UNUSED(arg1);

    this->m_ui->widgetOpenWorld->GetMainCamera()->OptionShowDefaultTileMapImage(this->m_ui->chkShowDefaultTileMap->isChecked());
    this->m_ui->widgetOpenWorld->repaint();
}


/*!
 * \brief MainWindow::on_chkShowTileLine_stateChanged 타일맵 라인 보여주기 여부 콤보박스 상태변경 이벤트
 * \param arg1
 */
void MainWindow::on_chkShowTileLine_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    this->m_ui->widgetOpenWorld->GetMainCamera()->OptionShowTileMapLine(this->m_ui->chkShowTileLine->isChecked());
    this->m_ui->widgetOpenWorld->repaint();
}


/*!
 * \brief MainWindow::on_chkShowDataMap_stateChanged 데이타맵 보여주기 여부 콤보박스 상태변경 이벤트
 * 사용자 타일맵 이미지를 불러와야 작동 한다.
 * \param arg1
 */
void MainWindow::on_chkShowDataMap_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    this->m_ui->widgetOpenWorld->GetMainCamera()->OptionShowTileData(this->m_ui->chkShowDataMap->isChecked());
    this->m_ui->widgetOpenWorld->repaint();
}


/*!
 * \brief MainWindow::on_chkScroll_stateChanged 스크롤 가능 여부 콤보박스 상태 변경 이벤트
 * \param arg1
 */
void MainWindow::on_chkScroll_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    this->m_ui->widgetOpenWorld->GetMainCamera()->GetTileMap()->OptionScroll(this->m_ui->chkScroll->isChecked());
}


/*!
 * \brief MainWindow::on_btnFadeIn_clicked 페이드인 버튼 클릭
 */
void MainWindow::on_btnFadeIn_clicked()
{
    this->m_ui->widgetOpenWorld->FadeIn();
}


/*!
 * \brief MainWindow::on_btnFadeOut_clicked 페이드 아웃 버튼 클릭
 */
void MainWindow::on_btnFadeOut_clicked()
{
    this->m_ui->widgetOpenWorld->FadeOut();
}


/*!
 * \brief MainWindow::on_btnViewCharactor_clicked
 */
void MainWindow::on_btnViewCharactor_clicked()
{
    this->m_ui->widgetOpenWorld->GetMainCamera()->GetObjectCreator()->Create(1);
    this->m_ui->widgetOpenWorld->repaint();
}
