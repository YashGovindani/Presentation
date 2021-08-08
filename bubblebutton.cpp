#include "bubblebutton.h"
#include "loadingview.h"
#include <QScreen>
#include <QRect>
#include <QIcon>
#include <QPixmap>
#include <QSize>
#include <QGuiApplication>
#include <QPainter>
#include <QPropertyAnimation>
#include <QTimer>

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
    cornerRadius = QString::number(radius);
    this->setGeometry(desktopWidth - windowWidth -5, desktopHeight/2 - windowHeight/2, windowWidth, windowHeight);
    if(loadingViewPointer) loadingViewPointer->setInfo(QString("Adding shadow to view"));
    if(loadingViewPointer) loadingViewPointer->setInfo(QString("Setting buttons for bubble view"));
    this->setStyleSheet(QString("QPushButton{border-top-left-radius : ") + cornerRadius + QString("; border-top-right-radius : ") + cornerRadius + QString("; border-bottom-right-radius : ") + cornerRadius + QString("; border-bottom-left-radius : ") + cornerRadius + QString("; background-color : rgb(32, 33, 36);} QPushButton:hover{background-color : rgb(255,255, 255)}"));
    this->setIcon(QIcon(QPixmap(QString(":/bubble/images/p.png"))));
    this->setIconSize(QSize(30,30));
    this->setText(QString(""));
    if(loadingViewPointer) loadingViewPointer->setInfo(QString("Bubble view created"));
    connect(this, &BubbleButton::clicked, this, &BubbleButton::onClick);
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
    moved = false;
    this->setStyleSheet(QString("QPushButton{border-top-left-radius : ") + cornerRadius + QString("; border-top-right-radius : ") + cornerRadius + QString("; border-bottom-right-radius : ") + cornerRadius + QString("; border-bottom-left-radius : ") + cornerRadius + QString("; background-color : rgb(23, 100, 189);}"));
}

void BubbleButton::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    buttonX += mouseEvent->x() - startX;
    buttonY += mouseEvent->y() - startY;
    move(buttonX, buttonY);
    moved = true;
}

void BubbleButton::mouseReleaseEvent(QMouseEvent *)
{
    if(!moved) clicked();
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int desktopWidth = screenGeometry.width();
    int newX = (this->x()>=desktopWidth/2)?desktopWidth - width() - 5: 5;
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry", this);
    animation->setDuration(500);
    animation->setStartValue(this->geometry());
    animation->setEndValue(QRect(newX, y(), width(), height()));
    animation->start();
    QTimer::singleShot(500, this, [=](){
        delete animation;
        this->setStyleSheet(QString("QPushButton{border-top-left-radius : ") + cornerRadius + QString("; border-top-right-radius : ") + cornerRadius + QString("; border-bottom-right-radius : ") + cornerRadius + QString("; border-bottom-left-radius : ") + cornerRadius + QString("; background-color : rgb(32, 33, 36);} QPushButton:hover{background-color : rgb(255,255, 255)}"));
    });
}

void BubbleButton::onClick()
{
    // to do something
}

BubbleButton::~BubbleButton()
{
}
