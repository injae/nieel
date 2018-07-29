#include"nieel/filesystem.h"
#include"nieel/algorithm.hpp"
#include"nieel/string.hpp"
#include <fstream>

namespace nieel
{
    void copy(const std::string src, const std::string dst) {
        if(fs::exists(dst)) fs::remove(dst);
        fs::copy(src, dst);
    }

    optional<std::vector<fs::directory_entry>> file_list(const fs::path& path) {
        std::vector<fs::directory_entry> list;
        std::copy(fs::directory_iterator(path), fs::directory_iterator(), std::back_inserter(list));
        return list;    
    }
    
    optional<std::vector<fs::directory_entry>> recursive_file_list(const fs::path& path) {
        std::vector<fs::directory_entry> list;
        fs::directory_iterator end_itr;
        for( fs::directory_iterator it(path); it != end_itr; ++it) {
           if(is_directory(it->status())) {
               nieel::insert(list, recursive_file_list(it->path()).get());
               continue;
           }
           list.push_back(*it);
        }
        return list;
    }
    
    
    optional<fs::path> find_file(const fs::path& path, const std::string file_name) {
        if(!fs::exists(path)) return none; 
        
        auto list = file_list(path);
        if(!list) return none; 
        
        for(const auto& file : list.get()) {
          if(file.path().filename() == file_name) return file.path();
          if(fs::is_directory(file)) 
            if(auto f = find_file(file, file_name)) return f;
        }
        return none;
    }
    
    std::vector<std::string> find_files(std::string path, std::regex filter, bool is_full_path) {
        auto files = nieel::recursive_file_list(path).get();
        std::vector<std::string> matching_files;
        fs::directory_iterator end_itr;
        for(auto it : files) {
            std::smatch what;
            auto file = nieel::str::erase(it.path().string(), path + "/");
            if(!std::regex_match(file, what, filter)) continue;
            if(!is_full_path)  matching_files.push_back(file);
            else matching_files.push_back(it.path().string());
        }
        return matching_files;
    }
    
    optional<fs::path> reverse_find_file(const fs::path& path, const std::string file_name) {
        if(!fs::exists(path)) return none; 
        
        auto list = file_list(path);
        if(!list) return none; 
        
        for(const auto& file : list.get()) {
          if(file.path().filename() == file_name) return file.path();
        }
        
        if(path == path.root_directory()) return none;
        return find_file(path.parent_path(), file_name);
    }
    
    std::vector<std::string> find_regex_files(std::string path, std::regex filter) {
        std::vector<std::string> matching_files;
        
        boost::filesystem::directory_iterator end_itr; // Default ctor yields past-the-end
        for( fs::directory_iterator it( path ); it != end_itr; ++it)
        {
            // Skip if not a file
            //if( !fs::is_regular_file( i->status() ) ) continue;
            std::smatch what;
        
            if(!std::regex_match( it->path().filename().string(), what, filter ) ) continue;
        
            matching_files.push_back( it->path().filename().string());
        }   
        
        return matching_files;
    }
    
    void recursive_copy(const fs::path& src, const fs::path& dst) {
        if (fs::exists(dst)){
           std::cerr << dst.generic_string() + " exists" << std::endl; return;
        }
    
        if (fs::is_directory(src)) {
           fs::create_directories(dst);
           for(fs::directory_iterator item(src); item != fs::directory_iterator(); ++item) {
              recursive_copy(item->path(), dst/item->path().filename());
            }
        } 
        else if (fs::is_regular_file(src)) {
          fs::copy(src, dst); 
        } 
        else {
          std::cerr << (dst.generic_string() + " not dir or file") << std::endl; return ;
        } 
    }
    
    std::string read_all(std::string path) {
        if(fs::is_directory(path)) {
            std::cerr << path << " is directory" << std::endl;
            return "";
        }
        std::ifstream file(path.c_str());
        return { std::istreambuf_iterator<char>(file)
               , std::istreambuf_iterator<char>()
               };
    }
}