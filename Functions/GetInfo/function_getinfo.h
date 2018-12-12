#ifndef FUNCTION_GETINFO_H
#define FUNCTION_GETINFO_H
#include <QByteArray>
#include "../functions.h"
#include "consts.h"
#include <QString>

class Function_GetInfoClient: public Function{
public:
    using Function::Function;
    virtual Results operator ()(Args args = Args()){
        Results results;

        QString info = QString("client version %1\n").arg(VERSION);

        Data* data = new Data;
        data->data = QByteArray(info.toLocal8Bit());
        data->description = "info";
        data->type = TYPE_RESULT_TEXT;

        results.push_back(data);
        return results;
    }
};

#endif // FUNCTION_GETINFO_H
