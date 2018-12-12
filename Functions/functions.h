#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <string>
#include "types.h"
#include "consts.h"

using std::string;

class Function{
public:
    Function(const string name, const string info, const bool isShow);
    virtual Results operator ()(Args args = Args()) = 0;
    virtual string GetName() const;
    virtual string GetInfo() const;
    virtual bool IsShow() const;
    virtual ~Function(){}
private:
    string _name;
    string _info;
    bool _isShow;
};

class Function_Empty: public Function{
public:
    using Function::Function;
    virtual Results operator ()(Args args = Args()){
        Results results;
        return results;
    }
};

typedef Function_Empty Function_IsLive;

#endif // FUNCTIONS_H
