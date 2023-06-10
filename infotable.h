#ifndef INFOTABLE_H
#define INFOTABLE_H

#include "table4infotable.h"
#include <QDialog>


namespace Ui {
class InfoTable;
}

class InfoTable : public QDialog
{
    Q_OBJECT

public:
    explicit InfoTable(QWidget *parent = nullptr);
    ~InfoTable();
    void openDataFile();
    void setValue(int value);

private slots:
    void on_infotableView_clicked(const QModelIndex &index);

private:
    Ui::InfoTable *ui;
    table4infotable* _model3;
    QString _currentFolder;
    int m_value;
    //table_infotable* _model2;

};

#endif // INFOTABLE_H
