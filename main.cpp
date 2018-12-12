#include <QApplication>
#include <QLabel>
#include <iostream>
#include "ssuclient.h"

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    SSUClient client;

    if (!client.Start()){
        return 0;
    }

    return a.exec();
}
