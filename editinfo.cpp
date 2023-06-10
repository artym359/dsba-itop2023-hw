#include "editinfo.h"
#include "ui_editinfo.h"

EditInfo::EditInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditInfo)
{
    ui->setupUi(this);
}

EditInfo::~EditInfo()
{
    delete ui;
}


QList<QVariant> EditInfo::getDataRow()
{
    QList<QVariant> dataRow;

    dataRow.append(ui->lineName->text());
    dataRow.append(ui->linePrice->text().toInt());
    dataRow.append(ui->lineYear->text().toInt());
    dataRow.append(ui->lineOwner->text());
    dataRow.append(ui->lineKM->text().toDouble());

    return dataRow;
}
