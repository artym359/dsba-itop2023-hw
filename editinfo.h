#ifndef EDITINFO_H
#define EDITINFO_H

#include <QDialog>

namespace Ui {
class EditInfo;
}

class EditInfo : public QDialog
{
    Q_OBJECT

public:
    explicit EditInfo(QWidget *parent = nullptr);
    ~EditInfo();

    QList<QVariant> getDataRow();

private:
    Ui::EditInfo *ui;
};

#endif // EDITINFO_H
