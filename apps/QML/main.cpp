#include <QGuiApplication>
#include <QQmlApplicationEngine>
// #include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // TODO: Initiate garmintreemodel

    QQmlApplicationEngine engine;
    //    QQmlContext *context = engine.rootContext();
    //    context->setProperty();

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
