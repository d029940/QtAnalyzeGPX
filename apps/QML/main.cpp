#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QQuickView>

#include "controllers/controller.h"
#include "garmintreemodel.h"
#include "gpxtablemodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Create Models
    GarminTreeModel garminDrives{ GarminTreeModel::tr("Drives") };
    GpxTableModel tracks{ GpxTableModel::tr("Tracks") }; // Table view for tracks
    GpxTableModel routes{ GpxTableModel::tr("Routes") }; // Table view for routes
    GpxTableModel courses{ GpxTableModel::tr("Courses") }; // Table view for routes
    GpxTableModel waypoints{ GpxTableModel::tr("Waypoints") }; // Table view for waypoints (POIs)

    // Controller
    Controller mainController(garminDrives, tracks, routes, waypoints, courses);

    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();

    // Connect models and controllers to views
    context->setContextProperty("_tracks", &tracks);
    context->setContextProperty("_routes", &routes);
    context->setContextProperty("_courses", &courses);
    context->setContextProperty("_waypoints", &waypoints);
    context->setContextProperty("_garminDrives", &garminDrives);
    context->setContextProperty("_controller", &mainController);

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
