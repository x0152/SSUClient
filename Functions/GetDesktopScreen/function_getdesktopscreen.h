#ifndef FUNCTION_GETDESKTOPSCREEN_H
#define FUNCTION_GETDESKTOPSCREEN_H
#include <QApplication>
#include <QPixmap>
#include <QDesktopWidget>
#include <QBuffer>
#include "../functions.h"

class Function_GetScreenWindow : public Function{
public:
    using Function::Function;
    virtual QByteArray* GetScreenDesktop(){
        QPixmap pixmap = QPixmap::grabWindow(QApplication::desktop()->winId(),
                                             0, 0,
                                             QApplication::desktop()->width(),
                                             QApplication::desktop()->height());

        QByteArray* bArray = new QByteArray();
        QBuffer buffer(bArray);
        buffer.open(QIODevice::WriteOnly);
        pixmap.save(&buffer, "PNG");

        return bArray;
    }

    virtual Results operator ()(Args args = Args()){
        Results results;

        Data* data = new Data;
        data->data = *GetScreenDesktop();
        data->description = "screen.png";
        data->type = TYPE_RESULT_IMAGE;

        results.push_back(data);
        return results;
    }
};

#endif // FUNCTION_GETDESKTOPSCREEN_H
