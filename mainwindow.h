#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myproxy.h"
#include "table.h"
#include "infotable.h"
#include "editinfo.h"
#include "editremove.h"
#include "myproxy.h"
#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openDataFile();
    void superAction();
//    void openEditInfo();
    void on_addButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_infoButton_clicked();

    void on_lineSearch_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void setMinFilterPrice(int value);

    void on_minPriceEdit_textChanged(const QString &arg1);

//    void on_minPriceEdit_editingFinished();
//    void on_minPriceEdit_editingFinished();

    void on_maxPriceEdit_textEdited(const QString &arg1);

    void on_maxPriceEdit_textChanged(const QString &arg1);

    void on_minYearEdit_textChanged(const QString &arg1);

    void on_maxYearEdit_textChanged(const QString &arg1);


    void on_statsButton_clicked();

private:
    Ui::MainWindow *ui;
    table* _model;
    QString _currentFolder;
    MyProxy* _proxy;
};
#endif // MAINWINDOW_H
