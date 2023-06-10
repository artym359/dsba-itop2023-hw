#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "aboutform.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QAction>
#include <QLabel>

int ind = 0;


QString loadCurrentFolderFromFile()
{
    QFile inputFile("C:/Users/Имя/Downloads/dataset_1633.csv");
    if (!inputFile.open(QFile::ReadOnly | QFile::Text))
    {
        return QString("");
    }
    QTextStream inputStream(&inputFile);

    return inputStream.readLine();
}

QString extractDir(QString file)
{
    return file;
}

void saveCurrentFolderToFile(QString _currentFolder)
{
    QFile outputFile("./settings_file.txt");
    if (!outputFile.open(QFile::WriteOnly | QFile::Text))
    {
        return;
    }
    QTextStream outputStream(&outputFile);
    outputStream << _currentFolder;
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    _model = new table(this);
    _proxy = new MyProxy(this);
    _proxy->setSourceModel(_model);

    ui->tableView->setModel(_proxy);
    ui->tableView->setSortingEnabled(true);

    ui ->tableView->hideColumn(5);

    QObject::connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openDataFile);
    QObject::connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::superAction);

    QObject::connect(ui->minPriceEdit, &QLineEdit::textChanged, this, &MainWindow::on_minPriceEdit_textChanged);
    QObject::connect(ui->maxPriceEdit, &QLineEdit::textChanged, this, &MainWindow::on_maxPriceEdit_textChanged);
    QObject::connect(ui->minYearEdit, &QLineEdit::textChanged, this, &MainWindow::on_minYearEdit_textChanged);
    QObject::connect(ui->maxYearEdit, &QLineEdit::textChanged, this, &MainWindow::on_maxYearEdit_textChanged);


    _currentFolder = loadCurrentFolderFromFile();

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::superAction()
{
    aboutform x;

    x.setWindowIcon(QIcon("C:/Users/Имя/Documents/photo_2023-06-10_02-50-21.png"));
    x.setWindowTitle("ABOUT");

    if (x.exec()){}
}

void MainWindow::openDataFile()
{
    ind = 1;
    if (_currentFolder.isEmpty())
    {
        _currentFolder = ".";
    }

    QString fileName = QFileDialog::getOpenFileName(this, "Open data file", _currentFolder, "*.csv");

    //QMessageBox::warning(this, "Error", fileName, QMessageBox::Ok);

    _currentFolder = extractDir(fileName);
    saveCurrentFolderToFile(_currentFolder);


    if (!_model->reloadDataFromFile(fileName))
    {
        QMessageBox::warning(this, "Error", "Cannot open file", QMessageBox::Ok);
        ind = 0;
    }
}


//void MainWindow::openEditInfo()
//{
//    if (ind)
//    {
//        EditInfo dialog;
//        if (dialog.exec())
//        {
//            QList<QVariant> dataRow = dialog.getDataRow();
//            _model->appendRow(dataRow);
//        }
//    }
//}

void MainWindow::on_addButton_clicked()
{

    if (ind)
    {
        EditInfo dialog;
        dialog.setWindowIcon(QIcon("C:/Users/Имя/Documents/photo_2023-06-10_02-50-21.png"));
        dialog.setWindowTitle("ADD NEW ROW");

        if (dialog.exec())
        {
            QList<QVariant> dataRow = dialog.getDataRow();
            _model->appendRow(dataRow);
            ui -> pushButton -> setText("SAVE CHANGES");
        }
    }
    else
    {
        QMessageBox::warning(this, "Error", "Open your file first", QMessageBox::Ok);
    }
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{

    QModelIndex proxyIndex = _proxy->index(index.row(), index.column());
    QModelIndex sourceIndex = _proxy->mapToSource(proxyIndex);

    editremove form;
    {
        QList<QVariant> spisok = _model -> getRow(sourceIndex.row());

        _model ->editRow(sourceIndex.row(), spisok);

        form.ShowData(spisok);
    }
    form.setWindowIcon(QIcon("C:/Users/Имя/Documents/photo_2023-06-10_02-50-21.png"));
    form.setWindowTitle("EDIT / REMOVE DATA");
//    if (form.exec())
//    {
//        QList<QVariant> spisok = form.GetNewValues();
//        _model ->editRow(index.row(), spisok);
//        _model->saveDataToFile("C:/Users/Имя/Downloads/dataset_1633.csv");
//        ui->tableView->update();

//    }

    int result = form.exec();

    if (result == DeleteResult)
    {
        _model -> removeRow(sourceIndex.row());
        ui -> pushButton -> setText("SAVE CHANGES");
    }
    else
    {
        if (result == QDialog::Accepted)
        {
            QList<QVariant> spisok = form.GetNewValues();
            _model ->editRow(sourceIndex.row(), spisok);
            ui -> pushButton -> setText("SAVE CHANGES");
        }
    }


    ui -> tableView -> update();
}



void MainWindow::on_infoButton_clicked()
{
    InfoTable infota;
    infota.setWindowIcon(QIcon("C:/Users/Имя/Documents/photo_2023-06-10_02-50-21.png"));
    infota.setWindowTitle("STATISTICS 1");

    if (infota.exec())
    {

    }

}


void MainWindow::on_lineSearch_textChanged(const QString &arg1)
{
    MyProxy* proxyModel = qobject_cast<MyProxy*>(ui->tableView->model());
    if (proxyModel)
    {
        QString searchString = ui->lineSearch->text();
        proxyModel->setSearchText(searchString);
    }
}


void MainWindow::on_pushButton_clicked()
{
    if (ind)
    {
        _model->saveDataToFile("C:/Users/Имя/Downloads/dataset_1633.csv");
        ui -> pushButton -> setText("SAVED");
    }
    else
    {
        QMessageBox::warning(this, "Error", "Open your file first", QMessageBox::Ok);
    }
}


void MainWindow::on_minPriceEdit_textChanged(const QString &arg1)
{

    MyProxy* proxyMo = qobject_cast<MyProxy*>(ui->tableView->model());

    if (proxyMo)
    {
        qDebug() << "0";

        int newMinPrice = 0;
        int newMaxPrice = INT_MAX;

        if (ui->maxPriceEdit->text() != "")
        {
            newMaxPrice = ui->maxPriceEdit->text().toInt();
        }
        if (ui->minPriceEdit->text() != "")
        {
            newMinPrice = ui->minPriceEdit->text().toInt();
        }
        proxyMo->setPriceRange(newMinPrice, newMaxPrice);
    }
}



void MainWindow::on_maxPriceEdit_textChanged(const QString &arg1)
{
    MyProxy* proxyMo = qobject_cast<MyProxy*>(ui->tableView->model());

    if (proxyMo)
    {
        qDebug() << "1";

        int newMinPrice = 0;
        int newMaxPrice = INT_MAX;

        if (ui->maxPriceEdit->text() != "")
        {
            newMaxPrice = ui->maxPriceEdit->text().toInt();
        }
        if (ui->minPriceEdit->text() != "")
        {
            newMinPrice = ui->minPriceEdit->text().toInt();
        }
        proxyMo->setPriceRange(newMinPrice, newMaxPrice);
    }
}



void MainWindow::on_minYearEdit_textChanged(const QString &arg1)
{
    MyProxy* proxyMo = qobject_cast<MyProxy*>(ui->tableView->model());

    if (proxyMo)
    {
        qDebug() << "1";

        int newMinYear = 0;
        int newMaxYear = INT_MAX;

        if (ui->maxYearEdit->text() != "")
        {
            newMaxYear = ui->maxYearEdit->text().toInt();
        }
        if (ui->minYearEdit->text() != "")
        {
            newMinYear = ui->minYearEdit->text().toInt();
        }
        proxyMo->setYearRange(newMinYear, newMaxYear);
    }
}

void MainWindow::on_maxYearEdit_textChanged(const QString &arg1)
{
    MyProxy* proxyMo = qobject_cast<MyProxy*>(ui->tableView->model());

    if (proxyMo)
    {
        qDebug() << "1";

        int newMinYear = 0;
        int newMaxYear = INT_MAX;

        if (ui->maxYearEdit->text() != "")
        {
            newMaxYear = ui->maxYearEdit->text().toInt();
        }
        if (ui->minYearEdit->text() != "")
        {
            newMinYear = ui->minYearEdit->text().toInt();
        }
        proxyMo->setYearRange(newMinYear, newMaxYear);
    }
}




