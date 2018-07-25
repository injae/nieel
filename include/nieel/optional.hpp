#ifndef __NIEEL_OPTIONAL_HPP__
#define __NIEEL_OPTIONAL_HPP__

namespace nieel
{
    template<typename OPTIONAL>
    auto is_(OPTIONAL option) {
        using type = decltype(*option);
        return option ? *option : type{};
    }
}

#endif