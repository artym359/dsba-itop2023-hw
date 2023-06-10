//#ifndef KMBYOWNERS_H
//#define KMBYOWNERS_H

//#include "table4kbo.h"
//#include <QDialog>

//namespace Ui {
//class KMbyOwners;
//}

//class KMbyOwners : public QDialog
//{
//    Q_OBJECT

//public:
//    explicit KMbyOwners(QWidget *parent = nullptr);
//    void setName(QString name);
//    void openDataFile();
//    int passYeartokbo(int year);
////    int __year;
//    ~KMbyOwners();


//private:
//    Ui::KMbyOwners *ui;
//    table4kbo* _model4;
//    QString _currentFolder;
//};

//#endif // KMBYOWNERS_H


#ifndef KMBYOWNERS_H
#define KMBYOWNERS_H

#include "table4kbo.h"
#include <QDialog>


namespace Ui {
class KMbyOwners;
}

class KMbyOwners : public QDialog
{
    Q_OBJECT

public:
    explicit KMbyOwners(QWidget *parent = nullptr);
    ~KMbyOwners();
    void openDataFile();
//    void setName(QString name);

private slots:
    void on_infotableView_clicked(const QModelIndex &index);

private:
    Ui::KMbyOwners *ui;
    table4kbo* _model4;
    QString _currentFolder;


};

#endif // INFOTABLE_H
