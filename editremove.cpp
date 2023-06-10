#include "editremove.h"
#include "qpushbutton.h"
#include "ui_editremove.h"


editremove::editremove(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editremove)
{
    ui->setupUi(this);
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Edit");
//    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Cancel");
}

editremove::~editremove()
{
    delete ui;
}



void editremove::ShowData(QList<QVariant> spisok)
{
    ui -> lineName -> setText(spisok[0].toString());
    ui -> linePrice -> setText(spisok[1].toString());
    ui -> lineYear -> setText(spisok[2].toString());
    ui -> lineOwner -> setText(spisok[3].toString());
    ui -> lineKM -> setText(spisok[4].toString());
}


QList<QVariant> editremove::GetNewValues()
{

    QList<QVariant> newdata;
    newdata.append(ui -> lineName -> text());
    newdata.append(ui -> linePrice -> text());
    newdata.append(ui -> lineYear -> text());
    newdata.append(ui -> lineOwner -> text());
    newdata.append(ui -> lineKM -> text());

    return newdata;
}




void editremove::on_deleteRowButton_clicked()
{
    setResult(DeleteResult);
    hide();
}

