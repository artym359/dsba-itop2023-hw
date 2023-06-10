#include "owner_km.h"
#include "table4ok.h"
#include "ui_owner_km.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QAction>

owner_km::owner_km(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::owner_km)
{

    ui->setupUi(this);
//    _model3 = new table4ok(this);
//    ui -> tableView -> setModel(_model3);
//    openDataFile();
}



QString loadCurrentFolderFromFile3()
{
    QFile inputFile("C:/Users/Имя/Downloads/dataset_1633.csv");
    if (!inputFile.open(QFile::ReadOnly | QFile::Text))
    {
        return QString("");
    }
    QTextStream inputStream(&inputFile);

    return inputStream.readLine();
}

//QString extractDir2(QString file)
//{
//    return file;
//}

void saveCurrentFolderToFile3(QString _currentFolder)
{
    QFile outputFile("./settings_file.txt");
    if (!outputFile.open(QFile::WriteOnly | QFile::Text))
    {
        return;
    }
    QTextStream outputStream(&outputFile);
    outputStream << _currentFolder;
}

void owner_km::openDataFile()
{
    if (_currentFolder.isEmpty())
    {
        _currentFolder = ".";
    }

    //    QString fileName = QFileDialog::getOpenFileName(this, "Open data file", _currentFolder, "*.csv");

    //QMessageBox::warning(this, "Error", fileName, QMessageBox::Ok);

    //    _currentFolder = extractDir2(fileName);
    _currentFolder = "C:/Users/Имя/Downloads/dataset_1633.csv";
    saveCurrentFolderToFile3(_currentFolder);


    if (!_model3->reloadDataFromFile())
    {
        QMessageBox::warning(this, "Error", "Cannot open file", QMessageBox::Ok);
    }
}

void owner_km::setName(QString name)
{
    ui -> label -> setText(name);
}

void owner_km::sendYear(int year)
{
    _year = year;
    qDebug() << _year << "ii";

    _model3 = new table4ok(this);
    _model3->send2(_year);
    ui -> tableView -> setModel(_model3);
    openDataFile();
}

owner_km::~owner_km()
{
    delete ui;
}


