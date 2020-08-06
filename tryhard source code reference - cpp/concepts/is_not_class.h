#ifndef _ZG_IS_NOT_CLASS_H_
#define _ZG_IS_NOT_CLASS_H_

namespace zg
{
    //base
    template<typename T>
    struct is_not_class {
        static constexpr bool value = false;
    };

    //specialize
    //signed
    template<>
    struct is_not_class<bool> { 
        static constexpr bool value = true; 
    };

    template<>
    struct is_not_class<char> { 
        static constexpr bool value = true; 
    };
    template<>
    struct is_not_class<short> { 
        static constexpr bool value = true; 
    };

    template<>
    struct is_not_class<int> { 
        static constexpr bool value = true; 
    };

    template<>
    struct is_not_class<long int> { 
        static constexpr bool value = true; 
    };

    //unsigned
    template<>
    struct is_not_class<unsigned char> { 
        static constexpr bool value = true; 
    };
    template<>
    struct is_not_class<unsigned short> { 
        static constexpr bool value = true; 
    };
    template<>
    struct is_not_class<unsigned> { 
        static constexpr bool value = true; 
    };

    template<>
    struct is_not_class<unsigned long> { 
        static constexpr bool value = true; 
    };

    //float
    template<>
    struct is_not_class<float> { 
        static constexpr bool value = true; 
    };
    template<>
    struct is_not_class<double> { 
        static constexpr bool value = true; 
    };
    template<>
    struct is_not_class<long double> { 
        static constexpr bool value = true; 
    };
}

#endif //_ZG_IS_NOT_CLASS_H_
