#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "serialize.h"
#include <iostream>
#include <string>

#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    char buffer[1024];

    std::string cont = "haha string";

    AppMsg newmsg;
    newmsg.type = ANSWER;
    newmsg.length = cont.length() + 1 + 6;
    strcpy(newmsg.content, cont.c_str());

    std::cout << "TF";

    AppMsg newmsg2;
    AppMsg * mymsg2 = &newmsg2;

    printMsg(&newmsg);

    serializeMsg(buffer, &newmsg);
    // buffer [2|4|content]
    deserializeMsg(buffer, mymsg2);

    printMsg(mymsg2);


    QGuiApplication app(argc, argv);

    std::cout << "\nWHY";

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/qt/qml/hello/main.qml"_qs);
    engine.load(url);

    return app.exec();
}