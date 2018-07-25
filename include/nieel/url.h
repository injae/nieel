#ifndef __NIEEL_URL_H__
#define __NIEEL_URL_H__

#include<string>
#include<boost/optional.hpp>
using boost::optional;
using boost::none;

namespace nieel
{
    struct URL
    {
          std::string protocol 
        ; std::string domain 
        ; std::string port 
        ; std::string path 
        ; std::string query 
        ;  
    };

    optional<URL> parse_url(std::string url);
}




#endif