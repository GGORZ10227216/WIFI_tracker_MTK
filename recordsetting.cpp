#include "recordsetting.h"
#include "ui_recordsetting.h"

RecordSetting::RecordSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecordSetting)
{
    ui->setupUi(this);
}

RecordSetting::~RecordSetting()
{
    delete ui;
}
