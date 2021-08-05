#ifndef LOADINGVIEW_H
#define LOADINGVIEW_H

#include <QMainWindow>
#include <QGraphicsDropShadowEffect>
#include <QTimerEvent>

namespace Ui {
class LoadingView;
}

class LoadingView : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoadingView(QWidget *parent = nullptr);
    void setInfo(QString);
    QString getInfo();
    void timerEvent(QTimerEvent *);
    void setCompleted(QWidget *);
    ~LoadingView();

private:
    Ui::LoadingView *ui;
    QGraphicsDropShadowEffect *shadow_effect;
    int timerId;
    int runTimeDuration;
    bool isCompleted;
    QWidget *initialView;
    int timerEventTime;

};

#endif // LOADINGVIEW_H
