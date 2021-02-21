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

        localtime_r(&t, &time_struct);
        strftime(buffer, sizeof(buffer), "%d-%m-%Y_%H-%M-%S", &time_struct);

        return std::string(buffer, strlen(buffer));
    }
}
