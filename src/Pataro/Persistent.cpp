#include <Pataro/Persistent.hpp>

using namespace pat;

int Persistent::load_int(const std::vector<char>& data, std::size_t& pos)
{
    int val = 0;

    if (pos + 4 < data.size())
    {
        for (std::size_t i = 0; i < 4; ++i)
            val = (val << 8) + data[pos + i];
        pos += 4;
    }

    return val;
}

void Persistent::put_int(std::vector<char>& data, int i)
{
    for (int j = 0; j < 4; ++j)
    {
        data.push_back(static_cast<char>(
            (i & (0xff << (8 * j))) >> (8 * j)
        ));
    }
}

std::string Persistent::load_string(const std::vector<char>& data, std::size_t& pos)
{
    std::size_t length = static_cast<std::size_t>(load_int(data, pos));
    std::string val;

    if (pos + length < data.size())
    {
        for (std::size_t i = 0; i < length; ++i)
            val.push_back(data[pos + i]);
        pos += length;
    }

    return val;
}

void Persistent::put_string(std::vector<char>& data, const std::string& str)
{
    put_int(data, static_cast<int>(str.size()));

    for (std::size_t i = 0; i < str.size(); ++i)
        data.push_back(str[i]);
}