#include "database.h"

Database::Database(QObject *parent) : QObject(parent)
{

}

Database::~Database()
{

}

void Database::connectToDatabase()
{
    if(!QFile("/home/aliakbar/" Database_NAME).exists()) {
        this->restorDatabase();
    } else {
        this->openDatabase();
    }

}

bool Database::openDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(Database_HOSTNAME);
    db.setDatabaseName("/home/aliakbar/" Database_NAME);
    if(db.open()) {
        return true;
    } else {
        return false;
    }

}

bool Database::restorDatabase()
{
    if(this->openDatabase()) {
        return this->createTable() ? true : false;
    } else {
        qDebug() << "Failed to restore the database";
        return false;
    }
    return false;
}

bool Database::closeDatabase()
{
    db.close();
    return true;
}

bool Database::createTable()
{
    QSqlQuery query;
    if(!query.exec("CREATE TABLE " TABLE " (id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "firstname VARCHAR(255) NOT NULL, "
                   "lastname VARCHAR(255) NOT NULL, "
                   "mobile VARCHAR(255) NOT NULL"
                   ");"
                   )) {
        qDebug() << "Database: error of create " << TABLE;        
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

bool Database::insertIntoTable(const QVariantList &data)
{
    QSqlQuery query;
    query.prepare("INSERT INTO " TABLE " (firstname, "
                  "lastname, "
                  "mobile )"
                  "VALUES (:firstname, :lastname, :mobile)");

    query.bindValue(":firstname", data[0].toString());
    query.bindValue(":lastname", data[1].toString());
    query.bindValue(":mobile", data[2].toString());

    if(!query.exec()) {
        qDebug() << "error insert into " TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

bool Database::insertIntoTable(const QString &fname, const QString &sname, const QString &nik)
{
    QVariantList data;
    data.append(fname);
    data.append(sname);
    data.append(nik);

    if(insertIntoTable(data))
        return true;
    else
        return false;
}

bool Database::removeRecord(const int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM " TABLE " WHERE id= :ID ;");
    query.bindValue(":ID", id);

    if(!query.exec()) {
        qDebug() << "error delete row " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}
