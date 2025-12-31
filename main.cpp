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

#include <stdio.h>

// Security Fix: Custom Message Handler
// Protects against Information Disclosure by suppressing debug logs in Release builds
void secureMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // In Release builds (when QT_DEBUG is NOT defined), suppress Debug and Info messages
    // This prevents leaking system paths, arguments, and hardware details to stdout
#ifndef QT_DEBUG
    if (type == QtDebugMsg || type == QtInfoMsg) {
        return;
    }
#endif

    // Default formatting for allowed messages
    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file ? context.file : "";
    
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s\n", localMsg.constData());
        break;
    case QtInfoMsg:
        fprintf(stderr, "Info: %s\n", localMsg.constData());
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s\n", localMsg.constData());
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s (%s:%u)\n", localMsg.constData(), file, context.line);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s (%s:%u)\n", localMsg.constData(), file, context.line);
        abort();
    }
}

int main(int argc, char *argv[])
{
    // Install Security Handler
    qInstallMessageHandler(secureMessageHandler);

    QGuiApplication app(argc, argv);
    
    // Fix: Set Identity for consistent QSettings location
    app.setOrganizationName("AsusTuf");
    app.setApplicationName("FanControl");

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