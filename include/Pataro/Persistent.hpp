#ifndef PATARO_PERSISTENT_HPP
#define PATARO_PERSISTENT_HPP

#include <vector>
#include <string>

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
         * @return true if the operation was successful
         * @return false otherwise
         */
        virtual bool load(const std::vector<char>& data, std::size_t& pos) = 0;

        /**
         * @brief Interface for a data dumper.
         * 
         * @param data the structure to dump data to
         * @return true if the operation was successful
         * @return false otherwise
         */
        virtual bool save(std::vector<char>& data) = 0;

        /**
         * @brief Load an integer from a given data structure
         * 
         * @param data 
         * @param pos 
         * @param out 
         * @return int 
         * @return true if the operation was successful
         * @return false otherwise
         */
        bool load_int(const std::vector<char>& data, std::size_t& pos, int& out);

        /**
         * @brief Put an integer in the given data structure
         * 
         * @param data 
         * @param i 
         * @return true if the operation was successful
         * @return false otherwise
         */
        bool put_int(std::vector<char>& data, int i);

        /**
         * @brief Load a string from a given data structure
         * 
         * @param data 
         * @param pos 
         * @param out 
         * @return int 
         * @return true if the operation was successful
         * @return false otherwise
         */
        bool load_string(const std::vector<char>& data, std::size_t& pos, std::string& out);

        /**
         * @brief Put a string in the given data structure
         * 
         * @param data 
         * @param i 
         * @return true if the operation was successful
         * @return false otherwise
         */
        bool put_string(std::vector<char>& data, const std::string& str);
    };
}

#endif
