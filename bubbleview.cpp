#include "bubbleview.h"
#include "ui_bubbleview.h"

#include <QScreen>
#include <QRect>
#include <QGraphicsDropShadowEffect>

BubbleView * BubbleView::bubbleView;

BubbleView::BubbleView(QWidget *parent, QWidget *loadingView) :
    QMainWindow(parent),
    ui(new Ui::BubbleView)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int desktopWidth = screenGeometry.width();
    int desktopHeight = screenGeometry.height();
    int windowHeight = (desktopHeight<desktopWidth)?desktopHeight/12:desktopWidth/12;
    if(windowHeight % 2 != 0) windowHeight+=1;
    int windowWidth = windowHeight;
    int radius = windowHeight/2;
    int shadowRadius = 5;
    QString cornerRadius = QString::number(radius);
    this->setGeometry(desktopWidth - windowWidth - shadowRadius, desktopHeight/2 - windowHeight/2 - shadowRadius, windowWidth + shadowRadius*2, windowHeight + shadowRadius*2);
    this->ui->button->setGeometry(shadowRadius, shadowRadius, windowWidth, windowHeight);
    shadow_effect=new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(QColor(0, 0, 0, 255));
    shadow_effect->setBlurRadius(shadowRadius);
    this->ui->button->setGraphicsEffect(shadow_effect);
    this->ui->button->setStyleSheet(QString("QPushButton{border-top-left-radius : ") + cornerRadius + QString("; border-top-right-radius : ") + cornerRadius + QString("; border-bottom-right-radius : ") + cornerRadius + QString("; border-bottom-left-radius : ") + cornerRadius + QString("; background-color : rgb(32, 33, 36);} QPushButton:hover{background-color : rgb(255,255, 255)} QPushButton:pressed{background-color : rgb(23, 100, 189)}"));
}

BubbleView *BubbleView::getBubbleView(QWidget *parent, QWidget *loadingView)
{
    if(!bubbleView) bubbleView = new BubbleView(parent, loadingView);
    return bubbleView;
}

BubbleView::~BubbleView()
{
    delete ui;
}
