#ifndef __NIEEL_UTIL_FILESYSTEM_H__
#define __NIEEL_UTIL_FILESYSTEM_H__

#include"boost/filesystem.hpp"
#include"boost/optional.hpp"
#include<fstream>
#include<regex>
#include<vector>

#define BOOST_FILESYSTEM_NO_DEPRECATED
#define BOOST_FILESYSTEM_VERSION 3

namespace fs = boost::filesystem;
using boost::optional;
using boost::none;

namespace nieel 
{
    void recursive_copy(const fs::path& src, const fs::path& dst);
    void copy(const std::string src, const std::string dst);
    
    std::vector<std::string>                   find_regex_files(std::string path, std::regex filter);
    std::vector<std::string>                   find_files(std::string path, std::regex filter, bool is_full_path = true);
    optional<fs::path>                         find_file(const fs::path& path, const std::string file_name);
    optional<fs::path>                         reverse_find_file(const fs::path& path, const std::string file_name);
    optional<std::vector<fs::directory_entry>> file_list(const fs::path& path);
    optional<std::vector<fs::directory_entry>> recursive_file_list(const fs::path& path);
    std::string read_all(std::string path);
}

#endif
         