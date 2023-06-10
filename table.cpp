#include "table.h"
#include <QFile>
#include <QTextStream>
#include <QSize>

table::table(QObject* parent)
    : QAbstractTableModel(parent)
{
    _header.append("Name");
    _header.append("Selling Price");
    _header.append("Year");
    _header.append("Owner");
    _header.append("KM Driven");
//    _header.append("index");
}

QVariant table::headerData(int section, Qt::Orientation orientation, int role) const
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

int table::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;


    return _data.size();
}

int table::columnCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;

    return _header.size();
}

QVariant table::data(const QModelIndex& index, int role) const
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

bool table::setData(const QModelIndex& index, const QVariant& value, int role)
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

Qt::ItemFlags table::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}


bool table::reloadDataFromFile(const QString& path)
{

    QList<QList<QVariant>> newData;

    QFile inputFile(path);
    if (!inputFile.open(QFile::ReadOnly | QFile::Text))
    {
        return false;
    }
    QTextStream inputStream(&inputFile);

    // header
    // QString firstline = inputStream.readLine();
    // _header = firstline.split(",");
    QString line = inputStream.readLine();
//    int k = 0;
    while (!inputStream.atEnd())
    {
        QString line = inputStream.readLine();

        QList<QVariant> dataRow;
        QList<QString> items = line.split(",");
        for (int i = 0; i < items.size() - 1; ++i)
        {
            QVariant value;
            if (i != 3)
            {
                value = items[i];
                dataRow.append(value);
            }
        }

//        dataRow.append(k);
//        k++;

        newData.append(dataRow);
    }
    inputFile.close();

    beginResetModel();
    _data = newData;
    endResetModel();
    return true;
}


bool table::saveDataToFile(const QString& path)
{
    QFile outputFile("C:/Users/Имя/Downloads/dataset_1633.csv");
    if (!outputFile.open(QFile::WriteOnly | QFile::Text))
    {
        return false;
    }
    QTextStream outputStream(&outputFile);


    outputStream << "name,selling_price,year,seller_type,owner,km_driven,ex_showroom_price\n";



    for (const QList<QVariant>& row: _data)
    {
        bool first = true;
        int k = 0;

        for (const QVariant& item: row)
        {
            if (!first)
            {
                outputStream << ",";
            }
            if (k == 3)
            {
                outputStream << "blanc,";
            }

            outputStream << item.toString();
            first = false;
            k++;
        }

        outputStream << ",\n";
    }
    return true;
}

void table::appendRow(const QList<QVariant>& newRow)
{
    beginInsertRows(QModelIndex(), _data.size(), _data.size());
    _data.append(newRow);
    endInsertRows();
}


bool table::removeRow(int rowIndex)
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

QList<QVariant> table:: getRow(int index)
{
    return _data[index];
}

void table:: editRow(int index, QList<QVariant> newdata)
{
    _data[index] = newdata;
}















