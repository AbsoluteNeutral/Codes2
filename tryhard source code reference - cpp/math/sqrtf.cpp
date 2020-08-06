#include <iostream>
#include <stdio.h>
#include <math.h> 

#define _USE_NEWTON_RAPHSON_METHOD 1

namespace zg
{
  float sqrtf(float value_)
  {
    if(value_ <= 0.0f) return value_;
    
    /*
      Newton Raphson Method
      intial value x, determine how fast the code runs
      magic is growth rate of rate of (1 / x^0.5) = x^-0.5
      using pow defeat the purpose of this function
      Draw graph to see: https://www.desmos.com/calculator
      1     - 1
      2     ~ 0.7
      4     - 0.5 
      25    - 0.2
      100   - 0.1
      400   - 0.05
      625   - 0.04
      1111  ~ 0.03
      2500  - 0.02
      10000 - 0.01
    */
    
    ////__________ use default magic number
    //float x = 1.0f; 
    
    ////__________ use pre-determine magic number
    float x = value_;
    if(value_ >= 4500)
      x *= 0.02f;
    if(value_ >= 400)
      x *= 0.05f;
    else if(value_ >= 60)
      x *= 0.1f;
    else if (value_ >= 17)
      x *= 0.2f;
    else
      x *= 0.5f;
      
    float prev = x;  
    do
    {
      prev = x; 
      float a = (x * x - value_);
      float b = (2.0 * x);
      x = x - a / b ;
  
      prev -= x;
      prev = prev < 0.0f ? -prev : prev;
      
    } while( prev > 0.000001 );
    return x;
  }
}


int main()
{
  //long double aaa = 9795.84465548;
  long double aaa = 1025;
  //long double aaa = 35;
  
  
  //// caclulate the slope of square root to determine the intial value x0
  //long double b = 2.0;
  //while(b < 10001)
  //{
  //  std::cout << b << "  " << sqrt(b) / b * 100 << std::endl;
  //  b += 1.0;
  //}
  
  std::cout << sqrt(aaa) << std::endl;
  std::cout << sqrtf(aaa) << std::endl;
  std::cout << std::sqrt(aaa) << std::endl;
  std::cout << zg::sqrtf(aaa) << std::endl;
}
