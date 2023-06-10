//#ifndef TABLE4KBO_H
//#define TABLE4KBO_H

//#include <QAbstractTableModel>

//class table4kbo : public QAbstractTableModel
//{
//    Q_OBJECT

//public:
//    explicit table4kbo(QObject *parent = nullptr);

//    // Basic functionality:
//    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
//    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

//    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

//    bool reloadDataFromFile();
//    bool saveDataToFile();

//    bool setData(const QModelIndex &index, const QVariant &value,
//                 int role = Qt::EditRole) override;

//    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
//    Qt::ItemFlags flags(const QModelIndex& index) const override;

//    void appendRow(const QList<QVariant>& newRow);
//    bool removeRow(int rowIndex);
//    QList<QVariant> getRow(int index);
//    void passYear(int year);
////    int _year;

//private:

//    QList<QList<QVariant>> _data;
//    QList<QString> _header;
//};

//#endif // TABLE4KBO_H


#ifndef TABLE4KBO_H
#define TABLE4KBO_H

#include <QAbstractTableModel>

class table4kbo : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit table4kbo(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool reloadDataFromFile();
    bool saveDataToFile();

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    void appendRow(const QList<QVariant>& newRow);
    bool removeRow(int rowIndex);
    QList<QVariant> getRow(int index);

private:

    QList<QList<QVariant>> _data;
    QList<QString> _header;
};

#endif // TABLE4KBO_H
