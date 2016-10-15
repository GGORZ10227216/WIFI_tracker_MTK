#ifndef CAMVIEW_H
#define CAMVIEW_H

#include <QWebEngineView>
#include <QMainWindow>
#include <QDebug>

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
