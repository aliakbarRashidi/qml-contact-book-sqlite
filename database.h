#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFile>
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QString>

#define Database_HOSTNAME "localhost"
#define Database_NAME "mydatabase.db"
#define TABLE "users"

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);
    ~Database();
    void connectToDatabase();

private:
    QSqlDatabase db;
    bool openDatabase();
    bool restorDatabase();
    bool closeDatabase();
    bool createTable();

signals:

public slots:
    bool insertIntoTable(const QVariantList& data);
    bool insertIntoTable(const QString& fname, const QString& sname, const QString& nik);
    bool removeRecord(const int id);
};

#endif // DATABASE_H
