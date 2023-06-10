#include "aboutform.h"
#include "ui_aboutform.h"

aboutform::aboutform(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutform)
{
    ui->setupUi(this);
}

aboutform::~aboutform()
{
    delete ui;
}
