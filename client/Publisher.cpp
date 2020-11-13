#include "Publisher.h"

Publisher::Publisher(const QString& hostName, const quint16 port, QObject *parent)
    : QMQTT::Client(hostName, port, QSslConfiguration(), true, parent)
    , _number(0)
{
    connect(this, &Publisher::connected, this, &Publisher::onConnected);
    connect(&_timer, &QTimer::timeout, this, &Publisher::onTimeout);
    connect(this, &Publisher::disconnected, this, &Publisher::onDisconnected);

    connect(this, &Publisher::error, this, [=](const QMQTT::ClientError error) {
       qDebug() <<  "Publisher error " << error;
       setLastMsg("Publisher error ");
    });
}

QString Publisher::lastMsg() const
{
    return _lastMsg;
}

void Publisher::onConnected()
{
    qDebug() << "Connected";
    subscribe(EXAMPLE_TOPIC, 1);
    _timer.start(1000);
}

void Publisher::onTimeout()
{
    QMQTT::Message message(_number, EXAMPLE_TOPIC,
                           QString("Number is %1").arg(_number).toUtf8());
    setLastMsg("SENT MESSAGE: " + message.payload());
    publish(message);
    _number++;
    if(_number >= 10)
    {
        _timer.stop();
        disconnectFromHost();
    }
}

void Publisher::onDisconnected()
{
    setLastMsg("DISCONNECTED FROM HOST");
}

void Publisher::setLastMsg(QString lastMsg)
{
    if (_lastMsg == lastMsg)
        return;

    _lastMsg = lastMsg;
    emit lastMsgChanged(_lastMsg);
}
