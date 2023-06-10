#ifndef EDITREMOVE_H
#define EDITREMOVE_H

#include <QDialog>

enum CustomDialogResult {
    CustomAccepted = QDialog::Accepted,
    CustomRejected = QDialog::Rejected,
    DeleteResult = QDialog::Accepted + 1
};

namespace Ui {
class editremove;
}

class editremove : public QDialog
{
    Q_OBJECT

public:
    explicit editremove(QWidget *parent = nullptr);
    void ShowData(QList<QVariant> spisok);
    QList<QVariant> GetNewValues();
    ~editremove();

private slots:
    void on_deleteRowButton_clicked();

private:
    Ui::editremove *ui;
};

#endif // EDITREMOVE_H
