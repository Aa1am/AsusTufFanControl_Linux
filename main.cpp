#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include <QPixmap>
#include <QDebug>
#include "src/FanController.h"
#include "src/SystemStatsMonitor.h"
#include "src/AuraController.h"
#include "src/FanCurveController.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // --- DEBUG CHECK ---
    QPixmap testLoad(":/ui/app_icon.png");
    if (testLoad.isNull()) {
        qCritical() << "ERROR: Image failed to load! Check file path and re-run cmake.";
    } else {
        qInfo() << "SUCCESS: Image loaded. Size:" << testLoad.size();
        app.setWindowIcon(QIcon(testLoad));
    }
    // -------------------

    qmlRegisterType<FanController>("AsusTufFanControl", 1, 0, "FanController");
    qmlRegisterType<SystemStatsMonitor>("AsusTufFanControl", 1, 0, "SystemStatsMonitor");
    qmlRegisterType<AuraController>("AsusTufFanControl", 1, 0, "AuraController");
    qmlRegisterType<FanCurveController>("AsusTufFanControl", 1, 0, "FanCurveController");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/ui/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    
    engine.load(url);

    return app.exec();
}