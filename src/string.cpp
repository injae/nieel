#include"nieel/string.hpp"
#include<vector>
#include<cctype>
#include<algorithm>

namespace nieel::str
{
    bool has(std::string& target, std::string_view str) {
        std::size_t pos = 0;
        if ((pos = target.find(str, 0)) != std::string::npos) {
            return true;
        } 
        else {
           return false;
        }
    }
    
    void to_lower(std::string& str) {
        std::transform(str.begin(), str.end(), str.begin() , [](auto ch){ return std::tolower(ch);} );
    }
    
    std::string upper_first_letter(const std::string& str) {
        auto copy = str;
        copy[0] = toupper(copy[0]);
        return copy;
    }
    std::string erase(const std::string& target_str, const std::string& erase_str) {
        auto copy_str = target_str; 
        auto pos = copy_str.find(erase_str);
        if(pos != std::string::npos) return copy_str.erase(pos, erase_str.length());
        else                         return copy_str;
        
    }
    
    std::vector<std::string> split(const char* str, char c) {
        std::vector<std::string> result;
        do {
            const char* begin = str;
            while(*str != c && *str) 
                str++;
                
            result.emplace_back(std::string(begin, str));
        }while( *str++ != 0);
        
        return result;
    }
}