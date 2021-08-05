#include "bubbleview.h"
#include "ui_bubbleview.h"

BubbleView::BubbleView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BubbleView)
{
    ui->setupUi(this);
}

BubbleView::~BubbleView()
{
    delete ui;
}
