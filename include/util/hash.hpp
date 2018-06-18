#ifndef __NIEEL_UTIL_HASH_HPP__
#define __NIEEL_UTIL_HASH_HPP__

#include<iostream>

namespace nieel::util
{
    uint64_t constexpr mix(char m, uint64_t s) {
        return ((s<<7) + ~(s>>3)) + ~m;
    }
     
    uint64_t constexpr hash(const char * m) {
        return (*m) ? mix(*m,hash(m+1)) : 0;
    }
}

#endif

