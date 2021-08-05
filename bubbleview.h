#ifndef BUBBLEVIEW_H
#define BUBBLEVIEW_H

#include <QMainWindow>

namespace Ui {
class BubbleView;
}

class BubbleView : public QMainWindow
{
    Q_OBJECT

public:
    explicit BubbleView(QWidget *parent = nullptr);
    ~BubbleView();

private:
    Ui::BubbleView *ui;
};

#endif // BUBBLEVIEW_H
