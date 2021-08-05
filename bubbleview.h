#ifndef BUBBLEVIEW_H
#define BUBBLEVIEW_H

#include <QMainWindow>
#include <QGraphicsDropShadowEffect>

namespace Ui {
class BubbleView;
}

class BubbleView : public QMainWindow
{
    Q_OBJECT

public:
    static BubbleView* getBubbleView(QWidget *parent = nullptr, QWidget *loadingView = nullptr);
    ~BubbleView();

private:
    explicit BubbleView(QWidget *parent = nullptr, QWidget *loadingView = nullptr);
    Ui::BubbleView *ui;
    QGraphicsDropShadowEffect *shadow_effect;
    static BubbleView *bubbleView;
};

#endif // BUBBLEVIEW_H
