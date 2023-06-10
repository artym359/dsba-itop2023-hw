#ifndef ABOUTFORM_H
#define ABOUTFORM_H

#include <QDialog>

namespace Ui {
class aboutform;
}

class aboutform : public QDialog
{
    Q_OBJECT

public:
    explicit aboutform(QWidget *parent = nullptr);
    ~aboutform();

private:
    Ui::aboutform *ui;
};

#endif // ABOUTFORM_H
