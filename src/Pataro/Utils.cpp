#include <Pataro/Utils.hpp>

#include <time.h>
#include <string.h>

namespace pat::details
{
    std::string date_to_string()
    {
        time_t t = time(nullptr);
        char buffer[70];
        struct tm time_struct;

#ifdef WIN32
        localtime_s(&time_struct, &t);
#else
        localtime_r(&t, &time_struct);
#endif
        strftime(buffer, sizeof(buffer), "%d-%m-%Y_%H-%M-%S", &time_struct);

        return std::string(buffer, strlen(buffer));
    }
}
