#ifndef TABLE_INFOTABLE_H
#define TABLE_INFOTABLE_H

#include <QAbstractTableModel>

class table_infotable : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit table_infotable(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool reloadDataFromFile(const QString& path);

private:
    QList<QList<QVariant>> _data;
    QList<QString> _header;
};

#endif // TABLE_INFOTABLE_H
