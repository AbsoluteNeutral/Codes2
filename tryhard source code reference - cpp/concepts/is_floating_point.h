#ifndef _ZG_IS_FLOATING_POINT_H_
#define _ZG_IS_FLOATING_POINT_H_

namespace zg
{
    //base
    template<typename T>
    struct is_floating_point {
        static constexpr bool value = false;
    };

    //float
    template<>
    struct is_floating_point<float> { 
        static constexpr bool value = true; 
    };
    template<>
    struct is_floating_point<double> { 
        static constexpr bool value = true; 
    };
    template<>
    struct is_floating_point<long double> { 
        static constexpr bool value = true; 
    };
}

#endif //_ZG_IS_NOT_CLASS_H_
