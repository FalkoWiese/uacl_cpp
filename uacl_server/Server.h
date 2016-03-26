//
// Created by Falko Wiese on 1/31/16.
//

#ifndef UA_SERVER_SERVER_H
#define UA_SERVER_SERVER_H

#include <QObject>
#include <ext_utils/opcserver.h>
#include <uacl_server/InternalNodeManager.h>


namespace ua_server
{
    class Server : public QObject
    {
        Q_OBJECT
        Q_DISABLE_COPY(Server)

    public:

        Server(const QString& application_path, const QString& config_file_name, const QString& server_uri);
        ~Server();

        int start();
        void stop();

        void register_object(QObject* business_object);

    private:

        QString& app_path() { return _app_path; }
        QString _app_path;

        QString& config_file() { return _config_file; }
        QString _config_file;

        QString& ua_server_uri() { return _ua_server_uri; }
        QString _ua_server_uri;

        OpcServer* opc_server() { return _opc_server; }
        OpcServer* _opc_server;

        uacl_server::InternalNodeManager* node_manager() { return _node_manager; }
        uacl_server::InternalNodeManager* _node_manager;
    };

}


#endif //UA_SERVER_SERVER_H
