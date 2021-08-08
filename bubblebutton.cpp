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
#include <math.h>
#include <QDebug>

void onBackToApplicationButtonClicked()
{}

void onScreenshotButtonClicked()
{}

void onNewBoardButtonClicked()
{}

void onQuitButtonClicked()
{}

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
    int smallButtonRadius = (radius*2)/3;
    int smallButtonWidth = smallButtonRadius*2;
    int smallButtonHeight = smallButtonWidth;
    int smallButtonX = x() + radius - smallButtonRadius;
    int smallButtonY = y() + radius -smallButtonRadius;
    QString smallButtonCornerRadius = QString::number(smallButtonRadius);
    QString smallButtonStyleSheet = QString("QPushButton{border-top-left-radius : ") + smallButtonCornerRadius + QString("; border-top-right-radius : ") + smallButtonCornerRadius + QString("; border-bottom-right-radius : ") + smallButtonCornerRadius + QString("; border-bottom-left-radius : ") + smallButtonCornerRadius + QString("; background-color : rgb(32, 33, 36);} QPushButton:hover{background-color : rgb(255,255, 255)}");
    newBoardButton.setStyleSheet(smallButtonStyleSheet);
    newBoardButton.setIcon(QIcon(QPixmap(QString(":/bubble/images/board.png"))));
    newBoardButton.setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    newBoardButton.setAttribute(Qt::WA_TranslucentBackground);
    newBoardButton.setGeometry(smallButtonX, smallButtonY, smallButtonWidth, smallButtonHeight);
    newBoardButton.setClickEvent(onNewBoardButtonClicked);
    screenshotButton.setStyleSheet(smallButtonStyleSheet);
    screenshotButton.setIcon(QIcon(QPixmap(QString(":/bubble/images/screenshot.png"))));
    screenshotButton.setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    screenshotButton.setAttribute(Qt::WA_TranslucentBackground);
    screenshotButton.setGeometry(smallButtonX, smallButtonY, smallButtonWidth, smallButtonHeight);
    screenshotButton.setClickEvent(onScreenshotButtonClicked);
    backToApplicationButton.setStyleSheet(smallButtonStyleSheet);
    backToApplicationButton.setIcon(QIcon(QPixmap(QString(":/bubble/images/backToApplication.png"))));
    backToApplicationButton.setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    backToApplicationButton.setAttribute(Qt::WA_TranslucentBackground);
    backToApplicationButton.setGeometry(smallButtonX, smallButtonY, smallButtonWidth, smallButtonHeight);
    backToApplicationButton.setClickEvent(onBackToApplicationButtonClicked);
    quitButton.setStyleSheet(smallButtonStyleSheet);
    quitButton.setIcon(QIcon(QPixmap(QString(":/bubble/images/quit.png"))));
    quitButton.setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    quitButton.setAttribute(Qt::WA_TranslucentBackground);
    quitButton.setGeometry(smallButtonX, smallButtonY, smallButtonWidth, smallButtonHeight);
    quitButton.setClickEvent(onQuitButtonClicked);
    expanded = false;
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
    moved = true;
    if(expanded) return;
    buttonX += mouseEvent->x() - startX;
    buttonY += mouseEvent->y() - startY;
    move(buttonX, buttonY);
}

void BubbleButton::mouseReleaseEvent(QMouseEvent *)
{
    this->setStyleSheet(QString("QPushButton{border-top-left-radius : ") + cornerRadius + QString("; border-top-right-radius : ") + cornerRadius + QString("; border-bottom-right-radius : ") + cornerRadius + QString("; border-bottom-left-radius : ") + cornerRadius + QString("; background-color : rgb(32, 33, 36);} QPushButton:hover{background-color : rgb(255,255, 255)}"));
    if(!moved)
    {
        clicked();
        return;
    }
    if(expanded) return;
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
    });
}

void BubbleButton::onClick()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int desktopWidth = screenGeometry.width();
    int invert = (this->x()>=desktopWidth/2)?1:-1;
    int radius = width()/2;
    int smallButtonRadius = quitButton.width()/2;
    int expandedRadius = radius + 25 + smallButtonRadius;
    int startX = x() + radius - smallButtonRadius;
    int startY = y() + radius - smallButtonRadius;
    int smallButtonWidth = quitButton.width();
    int smallButtonHeight = quitButton.height();
    if(!expanded)
    {
        int endX = startX + invert*((int)(((double)expandedRadius)*cos(((double)(2*22))/(double)(3*7))));
        int endY = startY - (int)(((double)expandedRadius)*sin(((double)(2*22))/(double)(3*7)));
        QRect startRect(startX, startY, smallButtonWidth, smallButtonHeight);
        QPropertyAnimation *animation = new QPropertyAnimation(&backToApplicationButton, "geometry", this);
        animation->setDuration(100);
        animation->setStartValue(startRect);
        animation->setEndValue(QRect(endX, endY, smallButtonWidth, smallButtonHeight));
        animation->start(QPropertyAnimation::DeleteWhenStopped);
        backToApplicationButton.show();
        QTimer::singleShot(100, this, [=](){
            int endX = startX + invert*((int)(((double)expandedRadius)*cos(((double)(8*22))/(double)(9*7))));
            int endY = startY - (int)(((double)expandedRadius)*sin(((double)(8*22))/(double)(9*7)));
            QPropertyAnimation *animation = new QPropertyAnimation(&screenshotButton, "geometry", this);
            animation->setDuration(100);
            animation->setStartValue(startRect);
            animation->setEndValue(QRect(endX, endY, smallButtonWidth, smallButtonHeight));
            animation->start(QPropertyAnimation::DeleteWhenStopped);
            screenshotButton.show();
            QTimer::singleShot(100, this, [=](){
                int endX = startX + invert*((int)(((double)expandedRadius)*cos(((double)(10*22))/(double)(9*7))));
                int endY = startY - (int)(((double)expandedRadius)*sin(((double)(10*22))/(double)(9*7)));
                QPropertyAnimation *animation = new QPropertyAnimation(&newBoardButton, "geometry", this);
                animation->setDuration(100);
                animation->setStartValue(startRect);
                animation->setEndValue(QRect(endX, endY, smallButtonWidth, smallButtonHeight));
                animation->start(QPropertyAnimation::DeleteWhenStopped);
                newBoardButton.show();
                QTimer::singleShot(100, this, [=](){
                    int endX = startX + invert*((int)(((double)expandedRadius)*cos(((double)(4*22))/(double)(3*7))));
                    int endY = startY - (int)(((double)expandedRadius)*sin(((double)(4*22))/(double)(3*7)));
                    QPropertyAnimation *animation = new QPropertyAnimation(&quitButton, "geometry", this);
                    animation->setDuration(100);
                    animation->setStartValue(startRect);
                    animation->setEndValue(QRect(endX, endY, smallButtonWidth, smallButtonHeight));
                    animation->start(QPropertyAnimation::DeleteWhenStopped);
                    quitButton.show();
                });
            });
        });
        expanded = true;
    }else
    {
        QRect startRect(startX, startY, smallButtonWidth, smallButtonHeight);
        QPropertyAnimation *animation = new QPropertyAnimation(&backToApplicationButton, "geometry", this);
        animation->setDuration(100);
        animation->setStartValue(backToApplicationButton.geometry());
        animation->setEndValue(startRect);
        animation->start(QPropertyAnimation::DeleteWhenStopped);
        QTimer::singleShot(100, this, [=](){
            backToApplicationButton.close();
            QPropertyAnimation *animation = new QPropertyAnimation(&screenshotButton, "geometry", this);
            animation->setDuration(100);
            animation->setStartValue(screenshotButton.geometry());
            animation->setEndValue(startRect);
            animation->start(QPropertyAnimation::DeleteWhenStopped);
            QTimer::singleShot(100, this, [=](){
                screenshotButton.close();
                QPropertyAnimation *animation = new QPropertyAnimation(&newBoardButton, "geometry", this);
                animation->setDuration(100);
                animation->setStartValue(newBoardButton.geometry());
                animation->setEndValue(startRect);
                animation->start(QPropertyAnimation::DeleteWhenStopped);
                QTimer::singleShot(100, this, [=](){
                    newBoardButton.close();
                    QPropertyAnimation *animation = new QPropertyAnimation(&quitButton, "geometry", this);
                    animation->setDuration(100);
                    animation->setStartValue(quitButton.geometry());
                    animation->setEndValue(startRect);
                    animation->start(QPropertyAnimation::DeleteWhenStopped);
                    QTimer::singleShot(100, this, [=](){quitButton.close();});
                });
            });
        });
        expanded = false;
    }
}

BubbleButton::~BubbleButton()
{
}
