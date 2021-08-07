#ifndef BUBBLEBUTTON_H
#define BUBBLEBUTTON_H

#include <QPushButton>

class BubbleButton:public QPushButton
{
private:
    BubbleButton(QWidget *loadingView = nullptr);
    static BubbleButton *bubbleButton;
public:
    static BubbleButton * get(QWidget *loadingView = nullptr);
};

#endif // BUBBLEBUTTON_H
