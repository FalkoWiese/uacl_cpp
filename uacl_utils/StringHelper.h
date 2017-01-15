/*
 * This file is part of the UACL (Unified Architecture Convenience
 * Layer) project.
 *
 * Copyright (C) 2017 Falko Wiese (wieSE Software Engineering,
 *                                 Neubrandenburg)
 *
 * Project website ... https://gitlab.com/falko.wiese/uacl_cpp
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UACL_STRINGHELPER_H
#define UACL_STRINGHELPER_H

#include <QString>

#define qString2Char(x) x.toLocal8Bit().data()
#define char2QString(x) QString::fromLocal8Bit(x)
#define qString2UaString(x) UaString(x.toLocal8Bit().data())

#define isNullOrEmpty(x) (x.isNull() || x.isEmpty() || x.trimmed().isEmpty())
#define qNormalized(x) (isNullOrEmpty(x)?QString(""):x.trimmed().toUpper())


#endif //UACL_STRINGHELPER_H
