#ifndef TYPES_H
#define TYPES_H

#include <QByteArray>
#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

struct Data;

typedef int Action;
typedef std::map<string, string> Args;
typedef vector<Data*> Results;

enum{
    TYPE_RESULT_ERROR = -1,
    TYPE_RESULT_TEXT,
    TYPE_RESULT_IMAGE,
    TYPE_RESULT_FILE,
    TYPE_RESULT_LINK,
};

enum{
    CMD_GET_FUNCTINS
};


struct Data{
    int type;
    QByteArray data;
    string description;
};

struct CommandServer{
    Action action;
    Results results;
};

struct ResultCommandClient{
    Action action;
    Results results;
};

#endif // TYPES_H
