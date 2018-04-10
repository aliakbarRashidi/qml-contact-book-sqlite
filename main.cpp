#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include<QQmlContext>

#include "database.h"
#include "listmodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    Database database;
    database.connectToDatabase();

    ListModel* model = new ListModel();
    engine.rootContext()->setContextProperty("myModel", model);
    engine.rootContext()->setContextProperty("database", &database);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    return app.exec();
}
