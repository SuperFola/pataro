#include <Pataro/Utils.hpp>

#include <ctime>
#include <cstring>
#include <cmath>

namespace pat::details
{
    std::string date_to_string()
    {
        time_t t = time(nullptr);
        char buffer[70];
        struct tm time_struct {};

#ifdef WIN32
        localtime_s(&time_struct, &t);
#else
        localtime_r(&t, &time_struct);
#endif
        strftime(buffer, sizeof(buffer), "%d-%m-%Y_%H-%M-%S", &time_struct);

        return {buffer, strlen(buffer)};
    }

    unsigned get_manhattan_distance(int x1, int y1, int x2, int y2)
    {
        return std::abs(x2 - x1) + std::abs(y2 - y1);
    }
}
