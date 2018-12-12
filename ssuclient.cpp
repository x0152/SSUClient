#include "ssuclient.h"

SSUClient::SSUClient(){
    _network = new Network();

    connect(_network, SIGNAL(ReciveCommand(const CommandServer*)), SLOT(ReciveCommand(const CommandServer*)));
    connect(_network, SIGNAL(Connected()), SLOT(Connect()));
    connect(_network, SIGNAL(Disconnected()), SLOT(Disconnect()));

    _network->Connect(NETWORK_CONSTS::IP,
                           NETWORK_CONSTS::PORT);
}

bool SSUClient::Start(){
    Log::WriteMsg("start ssu client!");

    if (!_network->IsConnected()){
        Log::WriteMsg("invalid connected!");
        return false;
    }

    Log::WriteMsg("connected!");

    _functions.push_back(new Function_IsLive("", "", false));//Заглушка
    _functions.push_back(new Function_IsLive("", "", false));
    _functions.push_back(new Function_GetInfoClient("Информация о клиенте", "Получить информацию о ssu клиенте", true));
    _functions.push_back(new Function_GetScreenWindow("Cкрин экрана", "", true));

    return true;
}

ResultCommandClient* SSUClient::GetFunctions() const{

    ResultCommandClient* resultCommandClient = new ResultCommandClient();
    Results results;
    int index = 0;
    for(Function* fun : _functions){

        if (fun->IsShow()){
            Data* data = new Data;
            data->data = QByteArray(fun->GetName().c_str());
            data->description = fun->GetInfo().c_str();
            data->type = index;

            results.push_back(data);
        }

        index++;
    }

    resultCommandClient->results = results;
    resultCommandClient->action = CMD_GET_FUNCTINS;

    return resultCommandClient;
}

ResultCommandClient* MakeError(QString msg, const CommandServer* command){
    Results results;

    Data* data = new Data;
    data->data = QByteArray(msg.toLocal8Bit());
    data->description = "Error";
    data->type = TYPE_RESULT_ERROR;

    results.push_back(data);

    ResultCommandClient* resultCommand = new ResultCommandClient();
    resultCommand->action = command->action;
    resultCommand->results = results;

    return resultCommand;
}

void SSUClient::ReciveCommand(const CommandServer* command){
    int numberCommand = command->action;

    if (numberCommand == CMD_GET_FUNCTINS){
       _network->SendResult(GetFunctions());
        return;
    }

    if (numberCommand >= _functions.size()){
        QString msg = QString("undefine command: %1").
                arg(numberCommand);

        Log::WriteMsg(msg.toStdString());

        auto resultCommand = MakeError(msg, command);
        _network->SendResult(resultCommand);
        delete resultCommand;

        return;
    }

    auto result = (*_functions[numberCommand])();

    ResultCommandClient* resultCommand = new ResultCommandClient();
    resultCommand->action = command->action;
    resultCommand->results = result;

    _network->SendResult(resultCommand);

    delete resultCommand;
}

void SSUClient::Disconnect(){
    Log::WriteMsg("disconnect...");
    exit(0);
}

void SSUClient::Connect(){
    Log::WriteMsg("connect...");
}
