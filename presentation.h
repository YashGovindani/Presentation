#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <QMainWindow>
#include <QGraphicsDropShadowEffect>

QT_BEGIN_NAMESPACE
namespace Ui { class Presentation; }
QT_END_NAMESPACE

class Presentation : public QMainWindow
{
    Q_OBJECT

public:
    static Presentation * get(QWidget *bubbleButton, QWidget *loadingView = nullptr);
    void enlargeToolFrame();
    void showFullScreenView();
    ~Presentation();
private:
    Ui::Presentation *ui;
    static Presentation *presentation;
    static bool toolFrameInitiated;
    Presentation(QWidget *loadingView = nullptr,QWidget *parent = nullptr);
    void setToolFramePosition(QWidget *bubbleButton);
    void initiateToolFrame(QWidget *bubbleButton);
    int toolFrameHeight;
    QGraphicsDropShadowEffect *toolFrameShadow;
};
#endif // PRESENTATION_H
