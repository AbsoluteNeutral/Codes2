#ifndef _ZG_IS_INTEGRAL_H_
#define _ZG_IS_INTEGRAL_H_

namespace zg
{
    //base
    template<typename T>
    struct is_integral {
        static constexpr bool value = false;
    };

    //specialize
    //signed
    template<>
    struct is_integral<short> { 
        static constexpr bool value = true; 
    };

    template<>
    struct is_integral<int> { 
        static constexpr bool value = true; 
    };

    template<>
    struct is_integral<long int> { 
        static constexpr bool value = true; 
    };

    //unsigned
    template<>
    struct is_integral<unsigned char> { 
        static constexpr bool value = true; 
    };
    template<>
    struct is_integral<unsigned short> { 
        static constexpr bool value = true; 
    };
    template<>
    struct is_integral<unsigned> { 
        static constexpr bool value = true; 
    };

    template<>
    struct is_integral<unsigned long> { 
        static constexpr bool value = true; 
    };
}

#endif //_ZG_IS_INTEGRAL_H_
