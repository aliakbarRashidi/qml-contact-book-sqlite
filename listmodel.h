#ifndef LISTMODEL_H
#define LISTMODEL_H

#include <QObject>
#include <QSqlQueryModel>

#define TABLE "users"

class ListModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    enum Roles {
        IdRole = Qt::UserRole + 1,      // id
        FirstNameRole,                  // firstname
        LastNameRole,                   // lastname
        MobileRole                      // mobile
    };

    explicit ListModel(QObject *parent = nullptr);
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;

signals:

public slots:
    void updateModel();
    int getId(int row);
};

#endif // LISTMODEL_H
