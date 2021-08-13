#include "presentation.h"
#include "ui_presentation.h"

#include "loadingview.h"
#include "initialview.h"

Presentation *Presentation::presentation = nullptr;

Presentation::Presentation(QWidget *loadingView, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Presentation)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
}

Presentation::~Presentation()
{
    delete ui;
}

