#include "Subscriber.h"

Subscriber::Subscriber(const QString& hostName, const quint16 port, QObject *parent)
    : QMQTT::Client(hostName, port, QSslConfiguration(), true, parent)
    , _qout(stdout)
{
    connect(this, &Subscriber::connected, this, &Subscriber::onConnected);
    connect(this, &Subscriber::subscribed, this, &Subscriber::onSubscribed);
    connect(this, &Subscriber::received, this, &Subscriber::onReceived);

    connect(this, &Subscriber::error, this, [=](const QMQTT::ClientError error) {
       qDebug() <<  "subscriber error " << error;
       this->setLastMsg("subscribed error");
    });
}

QString Subscriber::lastMsg() const
{
    return _lastMsg;
}

void Subscriber::onConnected()
{
    _qout << "connected" << endl;
    setLastMsg("connected");
    subscribe(elo::EXAMPLE_TOPIC, 1);
}

void Subscriber::onSubscribed(const QString &topic)
{
    _qout << "subscribed " << topic << endl;
    setLastMsg("subscribed");
}

void Subscriber::onReceived(const QMQTT::Message &message)
{
    _qout << "publish received: \"" << QString::fromUtf8(message.payload())
          << "\"" << endl;
    setLastMsg(message.payload());
}

void Subscriber::setLastMsg(QString lastMsg)
{
    if (_lastMsg == lastMsg)
        return;

    _lastMsg = lastMsg;
    emit lastMsgChanged(_lastMsg);
}
