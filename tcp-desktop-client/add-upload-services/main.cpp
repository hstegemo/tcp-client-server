#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
// non-portable path to file "tcpclient.h"
#include "TcpClient.h"
/*
 * This is a modified TCP chat client from the Youtube video
 * 'Creating a Simple Chat Server and Client using Qt and QML' by
 * Hesam Gholami: https://www.youtube.com/watch?v=Y5wLGxOLu2A&t=845s
 * The GitHub source that was used, can be downloaded from:
 * 'https://github.com/J-TAG/qt-chat-client'
 *
*/


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    TcpClient client;
    // Hva gjør denne?
    engine.rootContext()->setContextProperty("client", &client);
    engine.load(url);

    return app.exec();
}
