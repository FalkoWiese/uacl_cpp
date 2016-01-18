//
// Created by Falko Wiese on 1/10/16.
//

#include <iostream>
#include <StringHelper.h>

namespace uacl_utils
{
    StringHelper::StringHelper() { }

    StringHelper::~StringHelper() { }

    void StringHelper::print_to_out(const std::string &s)
    {
        std::cout << s << std::endl;
    }
}
