#ifndef PATARO_PERSISTENT_HPP
#define PATARO_PERSISTENT_HPP

#include <vector>

namespace pat
{
    class Persistent
    {
    public:
        /**
         * @brief Interface for a data loader.
         * 
         * @param data a stream of bytes
         * @param pos the current position in the stream of bytes
         */
        virtual void load(const std::vector<char>& data, std::size_t& pos) = 0;

        /**
         * @brief Interface for a data dumper.
         * 
         * @param data the structure to dump data to
         */
        virtual void save(std::vector<char>& data) = 0;

        /**
         * @brief Load an integer from a given data structure
         * 
         * @param data 
         * @param pos 
         * @return int 
         */
        int load_int(const std::vector<char>& data, std::size_t& pos);

        /**
         * @brief Put an integer in the given data structure
         * 
         * @param data 
         * @param i 
         */
        void put_int(std::vector<char>& data, int i);

        std::string load_string(const std::vector<char>& data, std::size_t& pos);

        void put_string(std::vector<char>& data, const std::string& str);
    };
}

#endif
