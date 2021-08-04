#include "initialview.h"
#include "ui_initialview.h"

#include "presentation.h"
#include <QScreen>
#include <QRect>
#include <QGraphicsDropShadowEffect>

InitialView::InitialView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InitialView)
{
    ui->setupUi(this);
    int shadowRadius = 30;
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int desktopWidth = screenGeometry.width();
    int desktopHeight = screenGeometry.height();
    int windowHeight = desktopHeight/10;
    int windowWidth = desktopWidth/4;
    int windowX = desktopWidth/2 - windowWidth/2;
    int windowY = desktopHeight/2 - windowHeight/2;
    this->setGeometry(windowX - shadowRadius, windowY - shadowRadius, windowWidth + (shadowRadius*2), windowHeight + (shadowRadius*2));
    this->ui->frame->setGeometry( shadowRadius, shadowRadius, windowWidth, windowHeight);
    shadow_effect=new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(QColor(0, 0, 0, 255));
    shadow_effect->setBlurRadius(shadowRadius);
    this->ui->centralwidget->setGraphicsEffect(shadow_effect);
    QString cornerRadius = QString::number(windowHeight/2);
    this->ui->frame->setStyleSheet(QString("border-top-left-radius : ") + cornerRadius + QString("; border-top-right-radius : ") + cornerRadius + QString("; border-bottom-right-radius : ") + cornerRadius + QString("; border-bottom-left-radius : ") + cornerRadius + QString("; background-color : rgb(32, 33, 36); "));
    this->ui->frame->setGeometry(shadowRadius, shadowRadius, windowWidth, windowHeight);
    this->ui->frame->setStyleSheet(QString("border-top-left-radius : ") + cornerRadius + QString("; border-top-right-radius : ") + cornerRadius + QString("; border-bottom-right-radius : ") + cornerRadius + QString("; border-bottom-left-radius : ") + cornerRadius + QString("; background-color : rgb(32, 33, 36); "));
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
}

InitialView::~InitialView()
{
    delete this->shadow_effect;
    delete ui;
}
