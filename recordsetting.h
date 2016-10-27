#ifndef RECORDSETTING_H
#define RECORDSETTING_H

#include <QWidget>

namespace Ui {
class RecordSetting;
}

class RecordSetting : public QWidget
{
    Q_OBJECT

public:
    explicit RecordSetting(QWidget *parent = 0);
    ~RecordSetting();

private:
    Ui::RecordSetting *ui;
};

#endif // RECORDSETTING_H
