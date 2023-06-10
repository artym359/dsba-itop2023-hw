#include "table4kbo.h"
#include <QFile>
#include <QTextStream>
#include <QSize>

//table4kbo::table4kbo(QObject* parent)
//    : QAbstractTableModel(parent)
//{
//    _header.append("Owner");
//    _header.append("KM Driven");
////    _year = 2008;
//}

//QVariant table4kbo::headerData(int section, Qt::Orientation orientation, int role) const
//{
//    if (orientation == Qt::Horizontal)
//    {
//        if (role == Qt::DisplayRole)
//        {
//            return _header[section];
//        }
//    }
//    return QVariant();
//}

//int getKMbyOwner(int year, QVariant owner)
//{
//    qDebug() << "nihuya";

//    QFile inputFile("C:/Users/Имя/Downloads/dataset_1633.csv");
//    if (!inputFile.open(QFile::ReadOnly | QFile::Text))
//    {
//        return false;
//    }
//    QTextStream inputStream(&inputFile);
//    QString line = inputStream.readLine();

//    int km = 0;

//    while (!inputStream.atEnd())
//    {
//        QString line = inputStream.readLine();
////        QList<QVariant> yearRow;
////        QList<int> kmRow;
//        QList<QString> items = line.split(",");

//        if ((items[2].toInt() == year)&&(items[4] == owner))
//        {
//            km += items[5].toInt();
//        }

//    }
//    inputFile.close();

//    return km;
//}

//int table4kbo::rowCount(const QModelIndex& parent) const
//{
//    if (parent.isValid())
//        return 0;


//    return _data.size();
//}

//int table4kbo::columnCount(const QModelIndex& parent) const
//{
//    if (parent.isValid())
//        return 0;

//    return _header.size();
//}

//QVariant table4kbo::data(const QModelIndex& index, int role) const
//{
//    if (!index.isValid())
//        return QVariant();

//    if (role == Qt::DisplayRole || role == Qt::EditRole)
//    {
//        int row = index.row();
//        int column = index.column();
//        return _data.at(row).at(column);
//    }
//    else if (role == Qt::CheckStateRole)
//    {
//        return QVariant();
//    }
//    return QVariant();
//}

//bool table4kbo::setData(const QModelIndex& index, const QVariant& value, int role)
//{
//    if (data(index, role) != value)
//    {
//        int row = index.row();
//        int column = index.column();
//        _data[row][column] = value;

//        emit dataChanged(index, index, {role});
//        return true;
//    }
//    return false;
//}

//Qt::ItemFlags table4kbo::flags(const QModelIndex& index) const
//{
//    if (!index.isValid())
//        return Qt::NoItemFlags;

//    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
//}


////bool newDataCompare(QList<QVariant> a, QList<QVariant> b)
////{
////    return a[0].toInt() > b[0].toInt();
////}

//bool table4kbo::reloadDataFromFile()
//{

//    QList<QList<QVariant>> newData;

//    QFile inputFile("C:/Users/Имя/Downloads/dataset_1633.csv");
//    if (!inputFile.open(QFile::ReadOnly | QFile::Text))
//    {
//        return false;
//    }
//    QTextStream inputStream(&inputFile);
//    QString line = inputStream.readLine();

//    QList<QString> owner_used;

//    while (!inputStream.atEnd())
//    {
//        QString line = inputStream.readLine();
//        QList<QString> items = line.split(",");

//        if (!owner_used.contains(items[4]))
//        {
//            qDebug() << "opa";
//            QList<QVariant> owner_km;
//            owner_km.append(items[4]);
//            owner_km.append(getKMbyOwner(2019, items[4]));
////            qDebug() << _year << items[4];
//            newData.append(owner_km);
//            owner_used.append(items[4]);
//        }

//    }
//    inputFile.close();

//    beginResetModel();
//    _data = newData;
//    endResetModel();
//    return true;
//}

//bool table4kbo::saveDataToFile()
//{

//    QFile outputFile("C:/Users/Имя/Downloads/dataset_1633.csv");
//    if (!outputFile.open(QFile::WriteOnly | QFile::Text))
//    {
//        return false;
//    }
//    QTextStream outputStream(&outputFile);


//    for (const QList<QVariant>& row: _data)
//    {
//        bool first = true;
//        for (const QVariant& item: row)
//        {
//            if (!first)
//            {
//                outputStream << ",";
//            }
//            outputStream << item.toString();
//            first = false;
//        }
//    }
//    return true;
//}


//void table4kbo::appendRow(const QList<QVariant>& newRow)
//{
//    beginInsertRows(QModelIndex(), _data.size(), _data.size());
//    _data.append(newRow);
//    endInsertRows();
//}


//bool table4kbo::removeRow(int rowIndex)
//{
//    if (rowIndex >= _data.size())
//    {
//        return false;
//    }
//    beginRemoveRows(QModelIndex(), rowIndex, rowIndex);
//    _data.removeAt(rowIndex);
//    endRemoveRows();
//    return true;
//}

//QList<QVariant> table4kbo:: getRow(int index)
//{
//    return _data[index];
//}

////void table4kbo::passYear(int year)
////{
////    _year = year;
////}
///

#include "table4kbo.h"
#include <QFile>
#include <QTextStream>
#include <QSize>

table4kbo::table4kbo(QObject* parent)
    : QAbstractTableModel(parent)
{
    _header.append("Year");
    _header.append("KM Driven");
}

QVariant table4kbo::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        if (role == Qt::DisplayRole)
        {
            return _header[section];
        }
    }
    return QVariant();
}

int getKMbyYear2(int year)
{
    QFile inputFile("C:/Users/Имя/Downloads/dataset_1633.csv");
    if (!inputFile.open(QFile::ReadOnly | QFile::Text))
    {
        return false;
    }
    QTextStream inputStream(&inputFile);

    int km = 0;

    while (!inputStream.atEnd())
    {
        QString line = inputStream.readLine();
        QList<QVariant> yearRow;
        QList<int> kmRow;
        QList<QString> items = line.split(",");

        if (items[2].toInt() == year)
        {
            km += items[5].toInt();
        }

    }
    inputFile.close();

    return km;
}

int table4kbo::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;


    return _data.size();
}

int table4kbo::columnCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;

    return _header.size();
}

QVariant table4kbo::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        int row = index.row();
        int column = index.column();
        return _data.at(row).at(column);
    }
    else if (role == Qt::CheckStateRole)
    {
        return QVariant();
    }
    return QVariant();
}

bool table4kbo::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (data(index, role) != value)
    {
        int row = index.row();
        int column = index.column();
        _data[row][column] = value;

        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags table4kbo::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}


bool newDataCompare2(QList<QVariant> a, QList<QVariant> b)
{
    return a[0].toInt() > b[0].toInt();
}

bool table4kbo::reloadDataFromFile()
{

    QList<QList<QVariant>> newData;

    QFile inputFile("C:/Users/Имя/Downloads/dataset_1633.csv");
    if (!inputFile.open(QFile::ReadOnly | QFile::Text))
    {
        return false;
    }
    QTextStream inputStream(&inputFile);
    QString line = inputStream.readLine();

    QList<QVariant> year_used;

    while (!inputStream.atEnd())
    {
        QString line = inputStream.readLine();
        QList<QString> items = line.split(",");

        if (!year_used.contains(items[2]))
        {
            QList<QVariant> year_km;
            year_km.append(items[2].toInt());
            year_km.append(getKMbyYear2(items[2].toInt()));
            newData.append(year_km);
            year_used.append(items[2]);
        }

    }
    std::sort(newData.begin(), newData.end(), newDataCompare2);
    inputFile.close();

    beginResetModel();
    _data = newData;
    endResetModel();
    return true;
}

bool table4kbo::saveDataToFile()
{

    QFile outputFile("C:/Users/Имя/Downloads/dataset_1633.csv");
    if (!outputFile.open(QFile::WriteOnly | QFile::Text))
    {
        return false;
    }
    QTextStream outputStream(&outputFile);


    for (const QList<QVariant>& row: _data)
    {
        bool first = true;
        for (const QVariant& item: row)
        {
            if (!first)
            {
                outputStream << ",";
            }
            outputStream << item.toString();
            first = false;
        }
    }
    return true;
}


void table4kbo::appendRow(const QList<QVariant>& newRow)
{
    beginInsertRows(QModelIndex(), _data.size(), _data.size());
    _data.append(newRow);
    endInsertRows();
}


bool table4kbo::removeRow(int rowIndex)
{
    if (rowIndex >= _data.size())
    {
        return false;
    }
    beginRemoveRows(QModelIndex(), rowIndex, rowIndex);
    _data.removeAt(rowIndex);
    endRemoveRows();
    return true;
}

QList<QVariant> table4kbo:: getRow(int index)
{
    return _data[index];
}
