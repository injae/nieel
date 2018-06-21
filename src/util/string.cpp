#include"util/string.hpp"

namespace nieel
{
    bool has_str(std::string& target, std::string_view str) {
        std::size_t pos = 0;
        if ((pos = target.find(str, 0)) != std::string::npos) {
            return true;
        } 
        else {
           return false;
        }
    }
}
