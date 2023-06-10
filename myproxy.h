#ifndef MYPROXY_H
#define MYPROXY_H

#include <QSortFilterProxyModel>

class MyProxy : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit MyProxy(QObject *parent = nullptr);


    void setSearchText(const QString& searchText);
    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const;
    void setMinPrice(int minPrice);
    bool priceFitsFilter(QVariant dataAge) const;
    void setPriceRange(int minPrice, int maxPrice);
    void setYearRange(int minYear, int maxYear);
private:
    QString m_searchText;
    int _minPrice;
    int _maxPrice;
    int _minYear;
    int _maxYear;
    bool _priceFilterEnabled;
};

#endif // MYPROXY_H
