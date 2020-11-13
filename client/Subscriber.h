#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <QObject>
#include <qmqtt.h>
#include <QCoreApplication>
#include <QTimer>

namespace elo {

const QHostAddress EXAMPLE_HOST = QHostAddress::LocalHost;
const QString ADRESS = "test.mosquitto.org";
const quint16 EXAMPLE_PORT = 8883;
const QString EXAMPLE_TOPIC = "testy/test";

}

class Subscriber : public QMQTT::Client
{
    Q_OBJECT
    Q_PROPERTY(QString lastMsg READ lastMsg WRITE setLastMsg NOTIFY lastMsgChanged)
public:
    explicit Subscriber(const QString& hostName = elo::ADRESS,
                        const quint16 port = elo::EXAMPLE_PORT,
                        QObject* parent = NULL);
    virtual ~Subscriber() override {}

    QTextStream _qout;

    QString lastMsg() const;

public slots:
    void onConnected();

    void onSubscribed(const QString& topic);

    void onReceived(const QMQTT::Message& message);

    void setLastMsg(QString lastMsg);

signals:
    void lastMsgChanged(QString lastMsg);

private:

    QString _lastMsg;
};

#endif // SUBSCRIBER_H
