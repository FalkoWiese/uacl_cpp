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

#ifndef UACL_BUSINESSOBJECT_H
#define UACL_BUSINESSOBJECT_H

#include <uacl_server/UaPlugin.h>

class BusinessObject : public uacl_server::UaPlugin
{
    Q_OBJECT
	Q_PROPERTY(quint16 blub READ getBlub WRITE setBlub)

	quint16 blubValue;

public:
    BusinessObject();
    BusinessObject(const BusinessObject&);
    virtual ~BusinessObject();

	quint16 getBlub() { return blubValue; }
	void setBlub(quint16 val) { 
		int i = 0;
		blubValue = val; 
	}

    Q_INVOKABLE QString get_name();
};


#endif //UACL_BUSINESSOBJECT_H
