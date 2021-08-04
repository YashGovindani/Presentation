#include "presentation.h"
#include "ui_presentation.h"

#include "loadingview.h"
#include "initialview.h"

Presentation::Presentation(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Presentation)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->hide();
    LoadingView *loadingView = new LoadingView(this);
    loadingView->show();
    loadingView->setInfo(QString("Initiating"));
    InitialView *initialView = new InitialView(this);
    // After initiation
    loadingView->setCompleted(initialView);
}

Presentation::~Presentation()
{
    delete ui;
}

