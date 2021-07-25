#include <Pataro/Persistent.hpp>

using namespace pat;

bool Persistent::load_int(const std::vector<char>& data, std::size_t& pos, int& out)
{
    if (pos + 4 < data.size())
    {
        out = 0;
        for (std::size_t i = 0; i < 4; ++i)
            out = (out << 8) + data[pos + i];
        pos += 4;

        return true;
    }

    return false;
}

bool Persistent::put_int(std::vector<char>& data, int i)
{
    for (int j = 0; j < 4; ++j)
    {
        data.push_back(static_cast<char>(
            (i & (0xff << (8 * j))) >> (8 * j)
        ));
    }

    return true;
}

bool Persistent::load_string(const std::vector<char>& data, std::size_t& pos, std::string& out)
{
    int length = 0;
    if (!load_int(data, pos, length))
        return false;

    if (pos + length < data.size())
    {
        out = "";
        for (std::size_t i = 0; i < length; ++i)
            out.push_back(data[pos + i]);
        pos += length;

        return true;
    }

    return false;
}

bool Persistent::put_string(std::vector<char>& data, const std::string& str)
{
    if (!put_int(data, static_cast<int>(str.size())))
        return false;

    for (std::size_t i = 0; i < str.size(); ++i)
        data.push_back(str[i]);

    return true;
}