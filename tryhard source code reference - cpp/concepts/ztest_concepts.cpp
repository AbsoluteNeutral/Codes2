#include <stdio.h>
#include "../ZGconcepts.h"

namespace zg{
    template<typename T, typename P = typename enable_if<is_not_class<T>::value >::type>
    //template<typename T>
    void isParamNotAClass(T number)
    {
    	printf("T is Not a User Defined type\n");
    }

    template<typename T, typename P = typename enable_if<is_integral<T>::value >::type>
    void isParamIntegral(T number)
    {
    	printf("T is Integral\n");
    }
    
    template<typename T, typename P = typename enable_if<is_floating_point<T>::value >::type>
    void isParamFloat(T number)
    {
    	printf("T is Floating point\n");
    }
    struct A{};
    
    void Test1_isParamNotAClass()
    {
      printf(" ############################## Test1_isParamNotAClass() \n");

      zg::isParamNotAClass(10);
      //zg::isParamNotAClass(zg::A());  //compile error
      printf("\n");
    }
    
    void Test2_isParamIntegral()
    {
      printf(" ############################## Test2_isParamIntegral() \n");
      
      zg::isParamIntegral(10);
      //zg::isParamIntegral(10.0f);   //compile error
      
      printf("\n");
    }
    
    void Test3_isParamFloat()
    {
      printf(" ############################## Test3_isParamFloat() \n");

      zg::isParamFloat(10.0f);
      zg::isParamFloat(10.0);
      //zg::isParamFloat(10);   //compile error
    
      printf("\n");
    }
    
    void ztest_concepts()
    {
      printf(" ############################## Running ztest_concepts.cpp... ############################## \n\n");
      Test1_isParamNotAClass();
      Test2_isParamIntegral();
      Test3_isParamFloat();
      printf(" ############################## End ztest_concepts.cpp... ############################## \n\n");
    }
    
    
}

#ifndef _RUN_ALL_TEST_
int main()
{

#ifdef _TEST_IS_NOT_CLASS_H_
    zg::Test1_isParamNotAClass();
#endif

#ifdef _TEST_IS_INTEGRAL_H_
    zg::Test2_isParamIntegral();
#endif

#ifdef _TEST_IS_FLOATING_POINT_H_
    zg::Test3_isParamFloat();
#endif
}
#endif
