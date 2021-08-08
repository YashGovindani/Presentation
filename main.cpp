#include "presentation.h"
#include "loadingview.h"
#include "initialview.h"
#include "bubblebutton.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoadingView *loadingView = new LoadingView(nullptr);
    loadingView->show();
    loadingView->setInfo(QString("Initiating"));
    InitialView *initialView = new InitialView(nullptr, loadingView);
    BubbleButton *bubbleButton = BubbleButton::get(loadingView);
    bubbleButton->setA(&a);
    // After initiation
    loadingView->setInfo(QString("Ready to go !!!!"));
    loadingView->setCompleted(initialView);
    return a.exec();
}
