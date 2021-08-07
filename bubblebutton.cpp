#include "bubblebutton.h"
#include "loadingview.h"

BubbleButton * BubbleButton::bubbleButton;

BubbleButton::BubbleButton(QWidget *loadingView):QPushButton()
{

}

BubbleButton *BubbleButton::get(QWidget *loadingView)
{
    if(!bubbleButton) bubbleButton = new BubbleButton(loadingView);
    return bubbleButton;
}
