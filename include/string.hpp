#ifndef __NIEEL_STRING_STRING_HPP__
#define __NIEEL_STRING_STRING_HPP__

#include<string>
#include<numeric>
#include<iostream>
#include<functional>

namespace nieel::str
{
    template<typename Collection>
    std::string accumulate(Collection stl, std::string token="") {
        return std::accumulate(begin(stl), end(stl), std::string{},
            [&token](auto& str, const auto& piece) { return str += (token + piece);});
    };
    
    template<typename Collection>
    std::string accumulate(Collection stl, std::function<void(std::string& sum, std::string& piece)> func) {
        return std::accumulate(begin(stl), end(stl), std::string{}, func);
    };
    
    std::string erase(const std::string& target_str, const std::string& erase_str);
    bool has(std::string& target, std::string_view str);
    std::string upper_first_letter(const std::string& str);
    void to_lower(std::string& str);
}


#endif