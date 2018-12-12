#include "log.h"
#include <iostream>

Log::Log(){

}

void Log::WriteMsg(const string msg){
    std::cout << msg << std::endl;
}
