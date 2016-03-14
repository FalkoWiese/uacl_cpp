//
// Created by Falko Wiese on 2/10/16.
//

#ifndef UACL_STRINGHELPER_H
#define UACL_STRINGHELPER_H

#include <QString>

#define qString2Char(x) x.toLocal8Bit().data()
#define char2QString(x) QString::fromLocal8Bit(x)
#define qString2UaString(x) UaString(x.toLocal8Bit().data())

#define isNullOrEmpty(x) (x.isNull() || x.isEmpty() || x.trimmed().isEmpty())
#define qNormalized(x) (isNullOrEmpty(x)?QString(""):x.trimmed().toUpper())


#endif //UACL_STRINGHELPER_H
