#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "garmintreemodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Create Models
    GarminTreeModel garminDrives{ GarminTreeModel::tr("Drives") };
    // TODO: gpx models tbd

    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();

    // Connect models to views
    // TODO: Can context be moved / refenced from the controller and connections are made in the
    // controller?
    context->setContextProperty("_garminDrives", &garminDrives);

    const QUrl url(u"qrc:/AnalyzeGPX/MainView.qml"_qs);
    QObject::connect(
            &engine, &QQmlApplicationEngine::objectCreated, &app,
            [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);
            },
            Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
