#include <Pataro/Utils.hpp>

#define _CRT_SECURE_NO_WARNINGS
#include <ctime>

#include <iomanip>
#include <sstream>
#include <iostream>

namespace pat::details
{
    std::string date_to_string()
    {
        auto t = std::time(nullptr);
        // TODO this is considered unsafe, fix this
        auto tm = *std::localtime(&t);

        std::ostringstream oss;
        oss << std::put_time(&tm, "%d-%m-%Y_%H-%M-%S");
        return oss.str();
    }
}

#undef _CRT_SECURE_NO_WARNINGS