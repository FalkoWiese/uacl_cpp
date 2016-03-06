//
// Created by Falko Wiese on 1/31/16.
//

#ifndef UACL_UA_CLIENT_H
#define UACL_UA_CLIENT_H

namespace uacl_client
{
    class UaClient
    {
    public:
        UaClient();
        ~UaClient();

        bool start();

        bool stop();

    private:
        // Don't implement!
        UaClient(const UaClient&);
        UaClient& operator=(UaClient&);
        // Don't implement!
    };


}

#endif //UACL_UA_CLIENT_H
