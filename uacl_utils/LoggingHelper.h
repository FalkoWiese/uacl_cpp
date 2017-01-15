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

#ifndef UACL_LOGGINGHELPER_H
#define UACL_LOGGINGHELPER_H

#include <QString>

#define log_out(s) uacl_utils::LoggingHelper().print_to_out(s)
#define log_err(s) uacl_utils::LoggingHelper().print_to_err(s)

namespace uacl_utils
{
    class LoggingHelper
    {

    public:
        LoggingHelper();
        ~LoggingHelper();

        void print_to_out(const QString &s);
        void print_to_err(const QString &s);

    };
}

#endif //UACL_LOGGINGHELPER_H
