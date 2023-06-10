#include "infotable.h"
#include "owner_km.h"
#include "table4infotable.h"
#include "ui_infotable.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QAction>

InfoTable::InfoTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoTable)
{
    ui->setupUi(this);
    _model3 = new table4infotable(this);

    ui-> infotableView -> setModel(_model3);
//    ui->infotableView->setSortingEnabled(true);

    openDataFile();
}


QString loadCurrentFolderFromFile2()
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

void saveCurrentFolderToFile2(QString _currentFolder)
{
    QFile outputFile("./settings_file.txt");
    if (!outputFile.open(QFile::WriteOnly | QFile::Text))
    {
        return;
    }
    QTextStream outputStream(&outputFile);
    outputStream << _currentFolder;
}

void InfoTable::openDataFile()
{
    if (_currentFolder.isEmpty())
    {
        _currentFolder = ".";
    }

//    QString fileName = QFileDialog::getOpenFileName(this, "Open data file", _currentFolder, "*.csv");

    //QMessageBox::warning(this, "Error", fileName, QMessageBox::Ok);

//    _currentFolder = extractDir2(fileName);
    _currentFolder = "C:/Users/Имя/Downloads/dataset_1633.csv";
    saveCurrentFolderToFile2(_currentFolder);


    if (!_model3->reloadDataFromFile())
    {
        QMessageBox::warning(this, "Error", "Cannot open file", QMessageBox::Ok);
    }
}


InfoTable::~InfoTable()
{
    delete ui;
}

void InfoTable::on_infotableView_clicked(const QModelIndex &index)
{
    QVariant year = _model3 -> getRow(index.row())[0];

    owner_km tab;

    tab.setWindowIcon(QIcon("C:/Users/Имя/Documents/photo_2023-06-10_02-50-21.png"));
    tab.setWindowTitle("KM IN " + year.toString());

    tab.setName(year.toString());


    tab.sendYear(year.toInt());

    if (tab.exec())
    {

    }

}

