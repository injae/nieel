#ifndef __NIEEL_ALGORITHM_HPP__
#define __NIEEL_ALGORITHM_HPP__

#include<algorithm>
#include<numeric>
#include<iostream>
#include<iterator>
#include<string>

namespace nieel
{
    template<typename Collection, typename ...Args>
    auto find(Collection&& col, Args&&... args) {
       return std::find(col.begin(), col.end(), args...);
    }
    
    template<typename Collection>
    void insert(Collection& src, Collection& des) {
       src.insert(src.end(), des.begin(), des.end());
    }
    
    template<typename Collection, typename ...Args>
    void for_each(Collection&& col, Args&&... args) {
        std::for_each(col.begin(), col.end(), args...);
    }
    
    template<typename Collection, typename Type>
    bool has(const Collection& col, Type value) {
        return find(col, value) != col.end() ? true : false;
    }
     
    template<typename Collection, typename ...Args>
    auto accumulate(Collection&& col, Args&&... args) {
        return std::accumulate(col.begin(), col.end(), args...);
    }
     
    template<typename Collection, typename ...Args>
    auto remove(Collection&& col, Args&&... args) {
       return std::remove(col.begin(), col.end(), args...);
    }
    
    template<typename Collection, typename ...Args>
    auto remove_if(Collection& col, Args... args) {
       return std::remove_if(col.begin(), col.end(), args...);
    }
    
    template<typename Collection, typename ...Args>
        auto erase(Collection&& col, Args&&... args) {
        col.erase(remove(col, args...));
        return col;
    }
    
    template<typename Collection, typename ...Args>
        auto erase_if(Collection&& col, Args&&... args) {
        col.erase(remove_if(col, args...));
        return col;
    }
    
    template<typename Collection, typename Func>
    auto transform(Collection col, Func&& func) {
        return std::transform(col.begin(), col.end(), col.begin(), func);
    }
    
    template<typename Func>
    auto transform(std::string& str, Func&& func) {
        return std::transform(begin(str), end(str), begin(str), func);
    }
    
    template<typename Collection, typename ...Args>
    auto transform(Collection col, Args&&... args) {
        return std::transform(col.begin(), col.end(), args...);
    }
    
    template<typename RCollection, typename Collection,  typename ...Args>
    auto transform(Collection col, Args&&... args) {
        RCollection retrun_value;
        std::transform(col.begin(), col.end(), std::back_inserter(retrun_value), args...);
        return retrun_value;
    }
    
    
    template<typename Collection, typename Func> 
    void print(Collection col, Func func) {
        for(auto& it : col)  {
            std::cout << func << std::endl; 
        }
    }
    
    template<typename Collection> 
    void print(Collection col) {
        for(auto& it : col)  {
            std::cout << it << std::endl; 
        }
    }
}

#endif