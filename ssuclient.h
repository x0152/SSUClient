#ifndef SSUCLIENT_H
#define SSUCLIENT_H
#include "Network/network.h"
#include "Network/consts.h"
#include "Functions/functions.h"
#include "Log/log.h"
#include "Functions/GetDesktopScreen/function_getdesktopscreen.h"
#include "Functions/GetInfo/function_getinfo.h"

class SSUClient : public QObject {
    Q_OBJECT
public:
    SSUClient();
    bool Start();
    ResultCommandClient* GetFunctions() const;
public slots:
    void ReciveCommand(const CommandServer* command);
    void Connect();
    void Disconnect();
private:
    Network* _network;
    vector<Function*> _functions;
};

#endif // SSUCLIENT_H
