//
// Created by tester on 7/3/16.
//

#ifndef UACL_QTREFLECTIONHANDLER_H
#define UACL_QTREFLECTIONHANDLER_H

#include <QObject>
#include <QMetaObject>
#include <QMetaMethod>
#include <QMetaProperty>
#include <uabase/uanodeid.h>
#include <uabase/statuscode.h>

namespace uacl_server
{

    class QtReflectionHandler
    {
    public:
        QtReflectionHandler();

        ~QtReflectionHandler();

        void collect_remote_methods(QList<QMetaMethod> &methods, const QObject *origin);

        void methods_of(const QObject *qObject, const QMetaObject *metaObject, QList<QMetaMethod> &methods);

        void collect_process_variables(QList<QMetaProperty> &methods, const QObject *qObject);

        void properties_of(const QObject *qObject, const QMetaObject *metaObject, QList<QMetaProperty> &methods);



    };
}

#endif //UACL_QTREFLECTIONHANDLER_H
