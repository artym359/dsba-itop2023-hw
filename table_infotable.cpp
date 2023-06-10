#include "table_infotable.h"
#include <QFile>
#include <QTextStream>
#include <QSize>

table_infotable::table_infotable(QObject* parent)
    : QAbstractTableModel(parent)
{
    _header.append("Year");
    _header.append("KM Driven");
}

QVariant table_infotable::headerData(int section, Qt::Orientation orientation, int role) const
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

int table_infotable::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;


    return _data.size();
}

int table_infotable::columnCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;

    return _header.size();
}

QVariant table_infotable::data(const QModelIndex& index, int role) const
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


int getKMbyYear(int year,const QString& path)
{
    QFile inputFile(path);
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

bool table_infotable::reloadDataFromFile(const QString& path)
{

    QList<QList<QVariant>> newData;

    QFile inputFile(path);
    if (!inputFile.open(QFile::ReadOnly | QFile::Text))
    {
        return false;
    }
    QTextStream inputStream(&inputFile);

    QString line = inputStream.readLine();

//    while (!inputStream.atEnd())
//    {
//        QString line = inputStream.readLine();

//        QList<QVariant> yearRow;
//        QList<int> kmRow;
//        QList<QString> items = line.split(",");



//    }


    QList<QVariant> year_used;
    QList<QString> items = line.split(",");

    if (std::find(year_used.begin(), year_used.end(), items[2]) == year_used.end())
    {
        QList<QVariant> year_km;
        year_km.append(items[2]);
        year_km.append(getKMbyYear(items[2].toInt(), path));
        newData.append(year_km);
    }

    inputFile.close();

    beginResetModel();
    _data = newData;
    endResetModel();
    return true;
}

