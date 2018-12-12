#include "network.h"

Network::Network() {
    _socket = new QTcpSocket(this);

    connect(_socket, SIGNAL(readyRead()), SLOT(_ReciveCommand()));
    connect(_socket, SIGNAL(connected()), SLOT(_Connected()));
    connect(_socket, SIGNAL(disconnected()), SLOT(_Disconnected()));
}

void Network::Connect(const string ip, const short port){
    _socket->connectToHost(ip.c_str(), port);
}

bool Network::IsConnected(){

    if (_socket->state() == QTcpSocket::ConnectingState){
        _socket->waitForConnected();
    }

    return _socket->state() == QTcpSocket::ConnectedState;
}

void Network::SendResult(const ResultCommandClient* result){
    QJsonArray results;
    for (auto r : result->results){
        QJsonObject res{
            {"Type", r->type},
            {"Data", QString::fromLatin1(r->data.toBase64())},
            {"Description", r->description.c_str()}
        };

        results.append(res);
    }

    QJsonObject structure{
        {"Act", result->action},
        {"Res", results}
    };

    QJsonDocument document(structure);
    WriteData(document.toJson());
}

#define CHECK_JSON_VALUE(VALUE) \
    if (!structure.contains(VALUE)){\
        Log::WriteMsg("no correct data");\
        return; \
    }

void Network::_ReciveCommand(){
    auto data = ReadData();

    auto document = QJsonDocument::fromJson(data);
    if(document.isNull() || document.isEmpty()){
        Log::WriteMsg("no validation recive data");
        return;
    }

    QJsonObject structure = document.object();

    CHECK_JSON_VALUE("Act")
    CHECK_JSON_VALUE("Res")

    CommandServer* commandServer = new CommandServer();
    commandServer->action = structure["Act"].toInt();

    QJsonArray jsArgs = structure["Res"].toArray();

    Data* results = new Data;
    for(int i = 0; i < jsArgs.size(); ++i){
        results->type= jsArgs[i].toObject().value("Type").toInt();
        results->data = jsArgs[i].toObject().value("Data").toVariant().toByteArray();
        results->description = jsArgs[i].toObject().value("Description").toString().toStdString();

        commandServer->results.push_back(results);
    }

    emit ReciveCommand(commandServer);
}

void Network::WriteData(const QByteArray data){
    _socket->write(data);

    Log::WriteMsg(QString("Отправлено байт %1: %2").
                  arg(data.size()).
                  arg(data.toStdString().c_str()).toStdString());
}

int BrackdownPackage(const QByteArray data){
    int validBacket = 0;
    int countBacket = 0;
    int countChars = 0;

    for(auto ch : data){
        switch (ch) {
        case '{':
            validBacket++;
            countBacket++;
            break;
        case '}':
            countBacket++;
            validBacket--;
            break;
        }

        countChars++;

        if(countBacket > 0 && validBacket == 0){
           return countChars;
        }
    }

    return -1;
}

QByteArray Network::ReadData(){
    for(;;){
        auto data = _socket->read(NETWORK_CONSTS::SIZE_BUFFER);

        if (data.size() == 0){
            throw std::runtime_error("error connecting server");
        }

        int endPackage = BrackdownPackage(data);

        if(endPackage == -1){
            _cash = data;
            continue;
        }

        QByteArray newPackage;
        newPackage = data.left(endPackage);
        _cash = data.right(data.size() - endPackage);

        Log::WriteMsg(QString("Принято байт %1: %2").
                  arg(data.size()).
                  arg(newPackage.toStdString().c_str()).toStdString());

        return newPackage;
    }
}

void Network::_Connected(){
    emit Connected();
}

void Network::_Disconnected(){
    emit Disconnected();
}
