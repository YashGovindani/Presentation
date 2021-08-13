#include "presentation.h"
#include "ui_presentation.h"

#include "loadingview.h"
#include "initialview.h"

#include <QScreen>
#include <QGuiApplication>
#include <QRect>
#include <QFont>

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
}

void Presentation::setToolFramePosition(QWidget *bubbleButton)
{

}

void Presentation::initiateToolFrame(QWidget *bubbleButton)
{

}

Presentation *Presentation::get(QWidget *bubbleButton, QWidget *loadingView)
{
    if(!presentation) presentation = new Presentation(loadingView);
    presentation->initiateToolFrame(bubbleButton);
    presentation->setToolFramePosition(bubbleButton);
    return presentation;
}

Presentation::~Presentation()
{
    delete ui;
}

