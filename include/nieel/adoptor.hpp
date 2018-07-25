#ifndef __NIEEL_ADOPTOR_HPP__
#define __NIEEL_ADOPTOR_HPP__

#include"nieel/algorithm.hpp"

namespace nieel::adoptor
{
    template<typename Container,typename Adoptor>
    Container operator|(Container&& con, Adoptor&& adoptor) {
        return adoptor(con);
    }
    
    template<typename Func>
    struct erase_if
    {
    public:
       erase_if(Func&& func) : func_(std::move(func)) {}
       template<typename Container>
       Container operator()(Container& container) {
           return nieel::erase_if(container, func_);
       }
   private:
       Func func_;
    };
    
    template<typename Func>
    struct for_each 
    {
    public:
       for_each(Func&& func) : func_(std::move(func)) {}
       template<typename Container>
       Container&& operator()(Container&& container) {
           nieel::for_each(container, func_);
           return container;
       }
    private:
       Func func_;
    };
    
}

#endif