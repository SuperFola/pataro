#include <Pataro/Utils.hpp>

using namespace pat::details;

std::string date_to_string()
{
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y_%H-%M-%S");
    return oss.str();
}
