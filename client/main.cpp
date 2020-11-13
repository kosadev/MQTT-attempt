//#include <qmqtt.h>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTimer>
#include <QQmlContext>
#include <QSslSocket>
#include <QSslKey>
#include <QSslConfiguration>
#include <QSslCertificate>

#include "Publisher.h"
#include "Subscriber.h"


int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);

    if(QSslSocket::supportsSsl()) {
        QSslConfiguration config = QSslConfiguration::defaultConfiguration();
        config.setProtocol(QSsl::TlsV1_3);

        QSslConfiguration::setDefaultConfiguration(config);
    }


//    Subscriber subscriber;
//    subscriber.connectToHost();
    Publisher publisher;
    publisher.connectToHost();

    QQmlApplicationEngine engine;
//    engine.rootContext()->setContextProperty("subscriber", &subscriber);
    engine.rootContext()->setContextProperty("publisher", &publisher);

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
