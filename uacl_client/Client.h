//
// Created by Falko Wiese on 1/31/16.
//

#ifndef UACL_CLIENT_H
#define UACL_CLIENT_H

namespace uacl_client
{
    class Client
    {
    public:
        Client();
        ~Client();

        bool start();

    private:
        // Don't implement!
        Client(const Client&);
        Client& operator=(Client&);
        // Don't implement!
    };


}

#endif //UACL_CLIENT_H
