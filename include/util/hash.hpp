#ifndef __NIEEL_UTIL_HASH_HPP__
#define __NIEEL_UTIL_HASH_HPP__

#include<iostream>
#include<string>

namespace nieel
{
    uint64_t constexpr mix(char m, uint64_t s) {
        return ((s<<7) + ~(s>>3)) + ~m;
    }
     
    uint64_t constexpr hash(const char * m) {
        return (*m) ? mix(*m,hash(m+1)) : 0;
    }
    
    inline uint64_t hash(const std::string& str) {
        return hash(str.c_str());
    }
}

#endif

