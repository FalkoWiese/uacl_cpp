//
// Created by tester on 7/3/16.
//

#ifndef UACL_BUSINESSOBJECT_H
#define UACL_BUSINESSOBJECT_H

#include <uacl_server/UaPlugin.h>

class BusinessObject : public uacl_server::UaPlugin
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE set_name)

public:
    BusinessObject();
    BusinessObject(const BusinessObject&);
    virtual ~BusinessObject();

};


#endif //UACL_BUSINESSOBJECT_H