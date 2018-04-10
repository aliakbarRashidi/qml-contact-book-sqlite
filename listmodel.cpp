#include "listmodel.h"

ListModel::ListModel(QObject *parent) : QSqlQueryModel(parent)
{
    this->updateModel();
}

QVariant ListModel::data(const QModelIndex &index, int role) const
{
    int columnId = role - Qt::UserRole - 1;
    QModelIndex modelIndex = this->index(index.row(), columnId);

    return QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
}

QHash<int, QByteArray> ListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[FirstNameRole] = "firstname";
    roles[LastNameRole] = "lastname";
    roles[MobileRole] = "mobile";
    return roles;
}

void ListModel::updateModel()
{
    this->setQuery("SELECT id, firstname, lastname, mobile FROM " TABLE);
}

int ListModel::getId(int row)
{
    return this->data(this->index(row, 0), IdRole).toInt();
}
