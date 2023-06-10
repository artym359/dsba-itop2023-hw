#include "myproxy.h"

MyProxy::MyProxy(QObject* parent)
    : QSortFilterProxyModel(parent)
{
    _minPrice = 0;
    _maxPrice = INT_MAX;
    _minYear = 0;
    _maxYear = INT_MAX;
}



void MyProxy::setSearchText(const QString& searchText)
{
    m_searchText = searchText;
    invalidateFilter();
}

void MyProxy::setPriceRange(int minPrice, int maxPrice)
{
    _minPrice = minPrice;
    _maxPrice = maxPrice;
    invalidateFilter();
}


void MyProxy::setYearRange(int minYear, int maxYear)
{
    _minYear = minYear;
    _maxYear = maxYear;
    invalidateFilter();
}

//bool MyProxy::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
//{
//    QModelIndex index = sourceModel()->index(sourceRow, 1, sourceParent);
//    int price = sourceModel()->data(index).toInt();

//    if (!m_searchText.isEmpty() && price >= _minPrice && price <= _maxPrice) {
//        for (int i = 0; i < sourceModel()->columnCount(sourceParent); ++i) {
//            QModelIndex index = sourceModel()->index(sourceRow, i, sourceParent);
//            QString data = sourceModel()->data(index).toString();

//            if (data.contains(m_searchText, Qt::CaseInsensitive))
//                return true;
//        }
//    } else if (!m_searchText.isEmpty()) {
//        for (int i = 0; i < sourceModel()->columnCount(sourceParent); ++i) {
//            QModelIndex index = sourceModel()->index(sourceRow, i, sourceParent);
//            QString data = sourceModel()->data(index).toString();

//            if (data.contains(m_searchText, Qt::CaseInsensitive))
//                return true;
//        }
//    } else if (price >= _minPrice && price <= _maxPrice) {
//        return true;
//    }

//    return false;
//}

//bool MyProxy::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
//{
//    QModelIndex indexPrice = sourceModel()->index(sourceRow, 1, sourceParent);
//    int price = sourceModel()->data(indexPrice).toInt();

//    QModelIndex indexYear = sourceModel()->index(sourceRow, 2, sourceParent);
//    int year = sourceModel()->data(indexYear).toInt();

//    if (!m_searchText.isEmpty() && price >= _minPrice && price <= _maxPrice && year >= _minYear && year <= _maxYear) {
//        for (int i = 0; i < sourceModel()->columnCount(sourceParent); ++i) {
//            QModelIndex index = sourceModel()->index(sourceRow, i, sourceParent);
//            QString data = sourceModel()->data(index).toString();

//            if (data.contains(m_searchText, Qt::CaseInsensitive))
//                return true;
//        }
//    } else if (!m_searchText.isEmpty()) {
//        for (int i = 0; i < sourceModel()->columnCount(sourceParent); ++i) {
//            QModelIndex index = sourceModel()->index(sourceRow, i, sourceParent);
//            QString data = sourceModel()->data(index).toString();

//            if (data.contains(m_searchText, Qt::CaseInsensitive))
//                return true;
//        }
//    } else if (price >= _minPrice && price <= _maxPrice && year >= _minYear && year <= _maxYear) {
//        return true;
//    }

//    return false;
//}

bool MyProxy::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
{
    QModelIndex indexPrice = sourceModel()->index(sourceRow, 1, sourceParent);
    int price = sourceModel()->data(indexPrice).toInt();

    QModelIndex indexYear = sourceModel()->index(sourceRow, 2, sourceParent);
    int year = sourceModel()->data(indexYear).toInt();

    if (m_searchText.isEmpty()) {
        // Only apply price and year range filtering
        if (price >= _minPrice && price <= _maxPrice && year >= _minYear && year <= _maxYear) {
            return true;
        }
    } else {
        // Apply search text, price range, and year range filtering
        bool matchesSearchText = false;
        for (int i = 0; i < sourceModel()->columnCount(sourceParent); ++i) {
            QModelIndex index = sourceModel()->index(sourceRow, i, sourceParent);
            QString data = sourceModel()->data(index).toString();

            if (data.contains(m_searchText, Qt::CaseInsensitive)) {
                matchesSearchText = true;
                break;
            }
        }

        if (matchesSearchText && price >= _minPrice && price <= _maxPrice && year >= _minYear && year <= _maxYear) {
            return true;
        }
    }

    return false;
}

