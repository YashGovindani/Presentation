#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Presentation; }
QT_END_NAMESPACE

class Presentation : public QMainWindow
{
    Q_OBJECT

public:
    static Presentation * get(QWidget *bubbleButton, QWidget *loadingView = nullptr);
    ~Presentation();

private:
    Ui::Presentation *ui;
    static Presentation *presentation;
    static bool toolFrameInitiated;
    Presentation(QWidget *loadingView = nullptr,QWidget *parent = nullptr);
    static void setToolFramePosition(QWidget *bubbleButton);
    static void initiateToolFrame(QWidget *bubbleButton);
};
#endif // PRESENTATION_H
