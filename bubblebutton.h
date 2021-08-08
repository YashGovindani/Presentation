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
    bool moved;
    QString cornerRadius;
    QPushButton newBoardButton;
    QPushButton screenshotButton;
    QPushButton backToApplicationButton;
    QPushButton quitButton;
public:
    static BubbleButton * get(QWidget *loadingView = nullptr);
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void onClick();
    ~BubbleButton();
};

#endif // BUBBLEBUTTON_H
