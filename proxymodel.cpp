#include "proxymodel.h"
#include <QModelIndex>

proxymodel::proxymodel()
{

}

void proxymodel::setSearchText(const QString& searchText)
{
    m_searchText = searchText;
    invalidateFilter();
}

bool proxymodel::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
{
    if (m_searchText.isEmpty())
        return true;

    for (int i = 0; i < odel()->columnCount(sourceParent); ++i) {
        QModelIndex index = sourceModel()->index(sourceRow, i, sourceParent);
        QString data = sourceModel()->data(index).toString();
        if (data.contains(m_searchText, Qt::CaseInsensitive))
            return true;
    }
    return false;
}
