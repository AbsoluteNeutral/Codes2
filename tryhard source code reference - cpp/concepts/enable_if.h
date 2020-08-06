#ifndef _ZG_ENABLE_IF_H_
#define _ZG_ENABLE_IF_H_

namespace zg
{
    template<bool B, typename T = void>
    struct enable_if {};

    template<typename T>
    struct enable_if<true, T>
    {
        using type = T;
    };
}

#endif //_ZG_BITSET_H_
