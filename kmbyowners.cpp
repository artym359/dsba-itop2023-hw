#include "kmbyowners.h"
#include "ui_kmbyowners.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QAction>

KMbyOwners::KMbyOwners(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KMbyOwners)
{
    ui->setupUi(this);
    table4kbo* _model4 = new table4kbo(this);
    ui -> kbotableView -> setModel(_model4);
    openDataFile();
}

//void KMbyOwners:: setName(QString name)
//{
//    ui -> label -> setText(name);
//}

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



void KMbyOwners::openDataFile()
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


    if (!_model4 -> reloadDataFromFile())
    {
        QMessageBox::warning(this, "Error", "Cannot open file", QMessageBox::Ok);
    }
}

//int passYeartokbo(int year)
//{
//    return year;
//}


KMbyOwners::~KMbyOwners()
{
    delete ui;
}
