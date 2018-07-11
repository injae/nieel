#ifndef __NIEEL_UTIL_FILESYSTEM_H__
#define __NIEEL_UTIL_FILESYSTEM_H__

#include"boost/filesystem.hpp"
#include"boost/optional.hpp"
#include<boost/regex.hpp>
#include<vector>

#define BOOST_FILESYSTEM_NO_DEPRECATED
#define BOOST_FILESYSTEM_VERSION 3

namespace fs = boost::filesystem;
using boost::optional;
using boost::none;

namespace nieel 
{
    void create_directory(std::string dir_name);
    void recursive_copy(const fs::path& src, const fs::path& dst);
    
    std::vector<std::string>                   find_regex_files(std::string path, boost::regex filter);
    optional<fs::path>                         find_file(const fs::path& path, const std::string file_name);
    optional<fs::path>                         reverse_find_file(const fs::path& path, const std::string file_name);
    optional<std::vector<fs::directory_entry>> file_list(const fs::path& path);
}

#endif
         