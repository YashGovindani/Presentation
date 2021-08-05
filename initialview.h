#ifndef INITIALVIEW_H
#define INITIALVIEW_H

#include <QMainWindow>
#include <QGraphicsDropShadowEffect>

namespace Ui {
class InitialView;
}

class InitialView : public QMainWindow
{
    Q_OBJECT

public:
    explicit InitialView(QWidget *parent = nullptr, QWidget *loadingView = nullptr);
    ~InitialView();

private slots:
    void on_fullScreenViewButton_clicked();

    void on_bubbleViewButton_clicked();

private:
    Ui::InitialView *ui;
    QGraphicsDropShadowEffect *shadow_effect;
};

#endif // INITIALVIEW_H
