#include "table4infotable.h"
#include <QFile>
#include <QTextStream>
#include <QSize>

table4infotable::table4infotable(QObject* parent)
    : QAbstractTableModel(parent)
{
    _header.append("Year");
    _header.append("KM Driven");
}

QVariant table4infotable::headerData(int section, Qt::Orientation orientation, int role) const
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

int getKMbyYear(int year)
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

int table4infotable::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;


    return _data.size();
}

int table4infotable::columnCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;

    return _header.size();
}

QVariant table4infotable::data(const QModelIndex& index, int role) const
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

bool table4infotable::setData(const QModelIndex& index, const QVariant& value, int role)
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

Qt::ItemFlags table4infotable::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}


bool newDataCompare(QList<QVariant> a, QList<QVariant> b)
{
    return a[0].toInt() > b[0].toInt();
}

bool table4infotable::reloadDataFromFile()
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
            year_km.append(getKMbyYear(items[2].toInt()));
            newData.append(year_km);
            year_used.append(items[2]);
        }

    }
    std::sort(newData.begin(), newData.end(), newDataCompare);
    inputFile.close();

    beginResetModel();
    _data = newData;
    endResetModel();
    return true;
}

bool table4infotable::saveDataToFile()
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


void table4infotable::appendRow(const QList<QVariant>& newRow)
{
    beginInsertRows(QModelIndex(), _data.size(), _data.size());
    _data.append(newRow);
    endInsertRows();
}


bool table4infotable::removeRow(int rowIndex)
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

QList<QVariant> table4infotable:: getRow(int index)
{
    return _data[index];
}
