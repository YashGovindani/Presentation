#ifndef BUBBLEBUTTON_H
#define BUBBLEBUTTON_H

#include <QPushButton>
#include <QGraphicsDropShadowEffect>

class BubbleButton:public QPushButton
{
private:
    BubbleButton(QWidget *loadingView = nullptr);
    static BubbleButton *bubbleButton;
    QGraphicsDropShadowEffect *shadow_effect;
public:
    static BubbleButton * get(QWidget *loadingView = nullptr);
    ~BubbleButton();
};

#endif // BUBBLEBUTTON_H
