//
// Created by Falko Wiese on 1/31/16.
//

#ifndef UACL_SERVER_H
#define UACL_SERVER_H

#include <QObject>

namespace uacl_server
{
    class Server : public QObject
    {
    Q_OBJECT

    public:

        Server();

        ~Server();

        bool start();
        bool stop();

    private:

        Q_DISABLE_COPY(Server)

    };

}


#endif //UACL_SERVER_H
