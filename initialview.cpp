#include "initialview.h"
#include "ui_initialview.h"

#include "presentation.h"
#include "loadingview.h"
#include "bubblebutton.h"
#include <QScreen>
#include <QRect>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QTimer>

InitialView::InitialView(QWidget *parent, QWidget *loadingView) :
    QMainWindow(parent),
    ui(new Ui::InitialView)
{
    ui->setupUi(this);
    LoadingView *loadingViewPointer = (LoadingView *)loadingView;
    if(loadingViewPointer) loadingViewPointer->setInfo(QString("Creating initial view"));
    int shadowRadius = 30;
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    if(loadingViewPointer) loadingViewPointer->setInfo(QString("Extracting screen info"));
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int desktopWidth = screenGeometry.width();
    int desktopHeight = screenGeometry.height();
    int windowHeight = desktopHeight/10;
    int windowWidth = desktopWidth/4;
    int windowX = desktopWidth/2 - windowWidth/2;
    int windowY = desktopHeight/2 - windowHeight/2;
    if(loadingViewPointer) loadingViewPointer->setInfo(QString("Got screen info"));
    if(loadingViewPointer) loadingViewPointer->setInfo(QString("Setting initial view geometry"));
    this->setGeometry(windowX - shadowRadius, windowY - shadowRadius, windowWidth + (shadowRadius*2), windowHeight + (shadowRadius*2));
    this->ui->frame->setGeometry( shadowRadius, shadowRadius, windowWidth, windowHeight);
    if(loadingViewPointer) loadingViewPointer->setInfo(QString("Adding shadow to frame"));
    shadow_effect=new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(QColor(0, 0, 0, 255));
    shadow_effect->setBlurRadius(shadowRadius);
    this->ui->centralwidget->setGraphicsEffect(shadow_effect);
    QString cornerRadius = QString::number(windowHeight/2);
    this->ui->frame->setStyleSheet(QString("border-top-left-radius : ") + cornerRadius + QString("; border-top-right-radius : ") + cornerRadius + QString("; border-bottom-right-radius : ") + cornerRadius + QString("; border-bottom-left-radius : ") + cornerRadius + QString("; background-color : rgb(32, 33, 36); "));
    this->ui->frame->setGeometry(shadowRadius, shadowRadius, windowWidth, windowHeight);
    this->ui->frame->setStyleSheet(QString("border-top-left-radius : ") + cornerRadius + QString("; border-top-right-radius : ") + cornerRadius + QString("; border-bottom-right-radius : ") + cornerRadius + QString("; border-bottom-left-radius : ") + cornerRadius + QString("; background-color : rgb(32, 33, 36); "));
    if(loadingViewPointer) loadingViewPointer->setInfo(QString("Setting buttons for initial view"));
    this->ui->fullScreenViewButton->setGeometry(0, 0, windowWidth/2, windowHeight);
    this->ui->fullScreenViewButton->setStyleSheet(QString("QPushButton{border-top-left-radius : ") + cornerRadius + QString("; border-top-right-radius : 0") + QString("; border-bottom-right-radius : 0") + QString("; border-bottom-left-radius : ") + cornerRadius + QString("; background-color : rgb(32, 33, 36); border-right : 1px solid black;} QPushButton:hover{background-color : rgb(255,255, 255)} QPushButton:pressed{background-color : rgb(23, 100, 189)}"));
    this->ui->fullScreenViewButton->setText(QString(""));
    this->ui->fullScreenViewButton->setIcon(QIcon(QPixmap(QString(":/global/images/monitor.png"))));
    this->ui->fullScreenViewButton->setIconSize(QSize(48, 48));
    this->ui->bubbleViewButton->setGeometry(windowWidth/2, 0, windowWidth/2, windowHeight);
    this->ui->bubbleViewButton->setStyleSheet(QString("QPushButton{border-top-left-radius : 0") + QString("; border-top-right-radius : ") + cornerRadius + QString("; border-bottom-right-radius : ") + cornerRadius + QString("; border-bottom-left-radius : 0") + QString("; background-color : rgb(32, 33, 36); border-left : 1px solid black;} QPushButton:hover{background-color : rgb(255, 255, 255)} QPushButton:pressed{background-color : rgb(23, 100, 189)}"));
    this->ui->bubbleViewButton->setText(QString(""));
    this->ui->bubbleViewButton->setIcon(QIcon(QPixmap(QString(":/global/images/bubble.png"))));
    this->ui->bubbleViewButton->setIconSize(QSize(48, 48));
    if(loadingViewPointer) loadingViewPointer->setInfo(QString("Initial view created"));
}

InitialView::~InitialView()
{
    delete this->shadow_effect;
    delete ui;
}

void InitialView::on_fullScreenViewButton_clicked()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int desktopWidth = screenGeometry.width();
    int desktopHeight = screenGeometry.height();
    int windowHeight = desktopHeight/10;
    int windowWidth = desktopWidth/4;
    int windowX = desktopWidth/2 - windowWidth/2;
    int windowY = desktopHeight/2 - windowHeight/2;
    this->setGeometry(0, 0, desktopWidth, desktopHeight);
    this->ui->frame->setGeometry(windowX, windowY, windowWidth, windowHeight);
    this->ui->bubbleViewButton->hide();
    this->ui->fullScreenViewButton->hide();
    QPropertyAnimation *animation = new QPropertyAnimation(this->ui->frame, "geometry", this);
    animation->setDuration(500);
    animation->setStartValue(this->ui->frame->geometry());
    animation->setEndValue(screenGeometry);
    animation->start(QPropertyAnimation::DeleteWhenStopped);
    QTimer::singleShot(500, this, [=](){
        this->hide();
        Presentation::get(BubbleButton::get())->showFullScreenView();
        delete this;
    });
}

void InitialView::on_bubbleViewButton_clicked()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int desktopWidth = screenGeometry.width();
    int desktopHeight = screenGeometry.height();
    int windowHeight = desktopHeight/10;
    int windowWidth = desktopWidth/4;
    int windowX = desktopWidth/2 - windowWidth/2;
    int windowY = desktopHeight/2 - windowHeight/2;
    this->setGeometry(0, 0, desktopWidth, desktopHeight);
    this->ui->frame->setGeometry(windowX, windowY, windowWidth, windowHeight);
    this->ui->bubbleViewButton->hide();
    this->ui->fullScreenViewButton->hide();
    BubbleButton *bubbleButton = BubbleButton::get();
    QPropertyAnimation *animation = new QPropertyAnimation(this->ui->frame, "geometry", this);
    animation->setDuration(500);
    animation->setStartValue(this->ui->frame->geometry());
    animation->setEndValue(bubbleButton->geometry());
    animation->start(QPropertyAnimation::DeleteWhenStopped);
    QTimer::singleShot(500, this, [=](){
        this->hide();
        bubbleButton->show();
        delete this;
    });
}
