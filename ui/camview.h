#ifndef CAMVIEW_H
#define CAMVIEW_H

#include <QMainWindow>
#include <QDebug>
#include <gldrawer.h>
#include <QTimer>

namespace Ui {
class camView;
}

class camView : public QMainWindow
{
    Q_OBJECT

public:
    explicit camView(QString url , QWidget *parent = 0);
    ~camView();

private:
    Ui::camView *ui;
};

#endif // CAMVIEW_H
