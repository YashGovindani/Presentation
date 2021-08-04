#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Presentation; }
QT_END_NAMESPACE

class Presentation : public QMainWindow
{
    Q_OBJECT

public:
    Presentation(QWidget *parent = nullptr);
    ~Presentation();

private:
    Ui::Presentation *ui;
};
#endif // PRESENTATION_H
