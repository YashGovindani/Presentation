#include "presentation.h"
#include "ui_presentation.h"

#include "loadingview.h"
#include "initialview.h"

#include <QScreen>
#include <QGuiApplication>
#include <QRect>
#include <QFont>
#include <QPropertyAnimation>

Presentation *Presentation::presentation = nullptr;
bool Presentation::toolFrameInitiated = false;

Presentation::Presentation(QWidget *loadingView, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Presentation)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setGeometry(QGuiApplication::primaryScreen()->geometry());
    this->setStyleSheet(QString("background-color : rgb(46, 47, 48)"));
    QFont font;
    font.setPointSize(64);
    font.setBold(true);
    this->ui->mainViewLabel->setGeometry(this->geometry());
    this->ui->mainViewLabel->setText(QString("Welcome"));
    this->ui->mainViewLabel->setFont(font);
    this->ui->mainViewLabel->setAlignment(Qt::AlignCenter);
    this->ui->mainViewLabel->setStyleSheet(QString("color : rgba(1,1,1,25); background-color : rgba(0,0,0,0)"));
    this->ui->toolFrame->setStyleSheet(QString("background-color : rgba(255, 255, 255, 25); border : 1px solid white;"));
    toolFrameShadow = new QGraphicsDropShadowEffect(this);
    toolFrameShadow->setOffset(0, 0);
    toolFrameShadow->setColor(QColor(0, 0, 0, 255));
    toolFrameShadow->setBlurRadius(30);
    this->ui->toolFrame->setGraphicsEffect(toolFrameShadow);
}

void Presentation::setToolFramePosition(QWidget *bubbleButton)
{
    this->ui->toolFrame->setGeometry(bubbleButton->geometry());
}

void Presentation::initiateToolFrame(QWidget *bubbleButton)
{
    toolFrameInitiated = true;
    this->ui->toolFrame->setStyleSheet(bubbleButton->styleSheet());
    int buttonRadius = this->ui->toolFrame->width()/2;
    QString radiusString = QString::number(buttonRadius);
    this->ui->toolFrame->setStyleSheet(QString("background-color : rgb(32, 33, 36); border-top-left-radius : ") + radiusString + QString("; border-top-right-radius : ") + radiusString + QString("; border-bottom-right-radius : ") + radiusString + QString("; border-bottom-left-radius : ") + radiusString + QString(";"));
    int buttonCount = 4;
    this->toolFrameHeight = buttonCount*buttonRadius*2;
}

Presentation *Presentation::get(QWidget *bubbleButton, QWidget *loadingView)
{
    if(!presentation) presentation = new Presentation(loadingView);
    presentation->setToolFramePosition(bubbleButton);
    if(!toolFrameInitiated) presentation->initiateToolFrame(bubbleButton);
    return presentation;
}

void Presentation::enlargeToolFrame()
{
    int checkY = this->height()/2 - this->ui->toolFrame->height()/2;
    int startY = this->height()/2 - this->toolFrameHeight/2, endY = startY +this->toolFrameHeight;
    if(this->ui->toolFrame->y() < checkY)
    {
        startY -= checkY - this->ui->toolFrame->y();
        if(startY < 0) startY = 0;
        endY = startY + this->toolFrameHeight;
    }
    else
    {
        endY += this->ui->toolFrame->y() - checkY;
        if(endY > this->height()) endY = this->height();
        startY = endY - this->toolFrameHeight;
    }
    QPropertyAnimation *animation = new QPropertyAnimation(this->ui->toolFrame, "geometry", this);
    animation->setDuration(800);
    animation->setStartValue(this->ui->toolFrame->geometry());
    animation->setEndValue(QRect(this->ui->toolFrame->x(), startY, this->ui->toolFrame->width(), this->toolFrameHeight));
    animation->start(QPropertyAnimation::DeleteWhenStopped);
}

void Presentation::showFullScreenView()
{
    this->showFullScreen();
    this->enlargeToolFrame();
}

Presentation::~Presentation()
{
    delete toolFrameShadow;
    delete ui;
}

