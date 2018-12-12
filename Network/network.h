#ifndef NETWORK_H
#define NETWORK_H
#include <QtNetwork/QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include "Log/log.h"
#include "types.h"
#include "consts.h"

class Network : public QObject
{
    Q_OBJECT
public:
    Network();
    bool IsConnected();
    void SendResult(const ResultCommandClient* result);
    void WaitForConnected() const;
    void Connect(const string ip, const short port);
signals:
    void ReciveCommand(const CommandServer* commandServer);
    void Connected();
    void Disconnected();
private:
    QByteArray ReadData();

    void WriteData(const QByteArray bytes);
    bool _isConnected;
    QTcpSocket* _socket;
    QByteArray _cash;
private slots:
    void _ReciveCommand();
    void _Connected();
    void _Disconnected();
};

#endif // NETWORK_H
