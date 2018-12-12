#include "functions.h"

Function::Function(const string name, const string info, const bool isShow) {
    _name = name;
    _info = info;
    _isShow = isShow;
}

Results Function::operator ()(const Args args){
    return Results();
}

string Function::GetName() const {
    return _name;
}

string Function::GetInfo() const{
   return _info;
}

bool Function::IsShow() const{
    return _isShow;
}
