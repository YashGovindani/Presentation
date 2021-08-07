#include "bubblebutton.h"
#include "loadingview.h"
#include <QScreen>
#include <QRect>
#include <QIcon>
#include <QPixmap>
#include <QSize>
#include <QGuiApplication>
#include <QPainter>

BubbleButton * BubbleButton::bubbleButton;

BubbleButton::BubbleButton(QWidget *loadingView):QPushButton()
{
    LoadingView *loadingViewPointer = (LoadingView *)loadingView;
    if(loadingViewPointer) loadingViewPointer->setInfo(QString("Creating bubble view"));
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAttribute(Qt::WA_Hover);
    if(loadingViewPointer) loadingViewPointer->setInfo(QString("Extracting screen info"));
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int desktopWidth = screenGeometry.width();
    int desktopHeight = screenGeometry.height();
    if(loadingViewPointer) loadingViewPointer->setInfo(QString("Got screen info"));
    if(loadingViewPointer) loadingViewPointer->setInfo(QString("Setting bubble view geometry"));
    int windowHeight = (desktopHeight<desktopWidth)?desktopHeight/20:desktopWidth/20;
    if(windowHeight % 2 != 0) windowHeight+=1;
    int windowWidth = windowHeight;
    int radius = windowHeight/2;
    QString cornerRadius = QString::number(radius);
    this->setGeometry(desktopWidth - windowWidth -5, desktopHeight/2 - windowHeight/2, windowWidth, windowHeight);
    if(loadingViewPointer) loadingViewPointer->setInfo(QString("Adding shadow to view"));
    if(loadingViewPointer) loadingViewPointer->setInfo(QString("Setting buttons for bubble view"));
    this->setStyleSheet(QString("QPushButton{border-top-left-radius : ") + cornerRadius + QString("; border-top-right-radius : ") + cornerRadius + QString("; border-bottom-right-radius : ") + cornerRadius + QString("; border-bottom-left-radius : ") + cornerRadius + QString("; background-color : rgb(32, 33, 36);} QPushButton:hover{background-color : rgb(255,255, 255)} QPushButton:pressed{background-color : rgb(23, 100, 189)}"));
    this->setIcon(QIcon(QPixmap(QString(":/bubble/images/p.png"))));
    this->setIconSize(QSize(30,30));
    this->setText(QString(""));
    if(loadingViewPointer) loadingViewPointer->setInfo(QString("Bubble view created"));
}

BubbleButton *BubbleButton::get(QWidget *loadingView)
{
    if(!bubbleButton) bubbleButton = new BubbleButton(loadingView);
    return bubbleButton;
}

void BubbleButton::mousePressEvent(QMouseEvent *mouseEvent)
{
    startX = mouseEvent->x();
    startY = mouseEvent->y();
    buttonX = x();
    buttonY = y();
}

void BubbleButton::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    buttonX += mouseEvent->x() - startX;
    buttonY += mouseEvent->y() - startY;
    move(buttonX, buttonY);
}

BubbleButton::~BubbleButton()
{
}
