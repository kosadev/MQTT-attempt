#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <QObject>
#include <qmqtt.h>
#include <QCoreApplication>
#include <QTimer>

const QHostAddress EXAMPLE_HOST = QHostAddress::LocalHost;
const QString ADRESS = "test.mosquitto.org";
const quint16 EXAMPLE_PORT = 8883;
const QString EXAMPLE_TOPIC = "testy/test";

class Publisher : public QMQTT::Client
{
    Q_OBJECT
    Q_PROPERTY(QString lastMsg READ lastMsg WRITE setLastMsg NOTIFY lastMsgChanged)
public:
    explicit Publisher(const QString& hostName = ADRESS,
                       const quint16 port = EXAMPLE_PORT,
                       QObject* parent = NULL);
    virtual ~Publisher() override {}

    QTimer _timer;
    quint16 _number;
    QString lastMsg() const;

public slots:
    void onConnected();

    void onTimeout();

    void onDisconnected();

    void setLastMsg(QString lastMsg);

signals:
    void lastMsgChanged(QString lastMsg);

private:
    QString _lastMsg;
};

#endif // PUBLISHER_H
