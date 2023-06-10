#ifndef PROXYMODEL_H
#define PROXYMODEL_H
#include <QString>

class proxymodel
{
public:
    proxymodel();
    void setSearchText(const QString& searchText);
    QString m_searchText;
};

#endif // PROXYMODEL_H
