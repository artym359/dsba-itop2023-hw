#ifndef OWNER_KM_H
#define OWNER_KM_H

#include "table4ok.h"
#include <QDialog>


namespace Ui {
class owner_km;
}

class owner_km : public QDialog
{
    Q_OBJECT

public:
    explicit owner_km(QWidget *parent = nullptr);
    ~owner_km();
    void openDataFile();
    void setName(QString name);
    void sendYear(int year);

private slots:

private:
    Ui::owner_km *ui;
    table4ok* _model3;
    QString _currentFolder;
    int _year;
    //table_owner_km* _model2;

};

#endif // OWNER_KM_H
