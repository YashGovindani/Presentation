#ifndef BUBBLEBUTTON_H
#define BUBBLEBUTTON_H

#include <QPushButton>
#include <QGraphicsDropShadowEffect>
#include <QPaintEvent>
#include <QMouseEvent>

class BubbleButton:public QPushButton
{
private:
    BubbleButton(QWidget *loadingView = nullptr);
    static BubbleButton *bubbleButton;
    int startX;
    int startY;
    int buttonX;
    int buttonY;
public:
    static BubbleButton * get(QWidget *loadingView = nullptr);
    void mousePressEvent(QMouseEvent*);
    ~BubbleButton();
};

#endif // BUBBLEBUTTON_H
