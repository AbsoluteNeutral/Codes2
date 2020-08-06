
#include "endian.h"
#include "bitset.h"

namespace zg{
  
  void ztest_endian()
  {
    printf(" ############################## Running ztest_endian.cpp... ############################## \n");
    printf("Is Little Endian:    %d\n", IsLittleEndian());
    
    {
      printf("int \n");
      unsigned int number  = 0xEFFFAAFF;
      unsigned int big     = FlipEndian(number);
      unsigned int little  = FlipEndian(big);
    
      printf("Same:          %d\n", little == number);
    
      printf("Number:        %s\n", ConvertToBinary(number).c_str());
      printf("Little Endian: %s\n", ConvertToBinary(little).c_str());
      printf("Big Endian:    %s\n", ConvertToBinary(big).c_str());
    }
    {
      printf("int \n");
      int number  = 0xEFFFAAFF;
      int big     = FlipEndian(number);
      int little  = FlipEndian(big);
    
      printf("Same:          %d\n", little == number);
    
      printf("Number:        %s\n", ConvertToBinary(number).c_str());
      printf("Little Endian: %s\n", ConvertToBinary(little).c_str());
      printf("Big Endian:    %s\n", ConvertToBinary(big).c_str());
    }
    {
        printf("float \n");
        float number  = 0xEFFFAAFF;
        float big     = FlipEndian(number);
        float little  = FlipEndian(big);
    
        printf("Same:          %d\n", little == number);
        
        printf("Number:        %s\n", ConvertToBinary(number).c_str());
        printf("Little Endian: %s\n", ConvertToBinary(little).c_str());
        printf("Big Endian:    %s\n", ConvertToBinary(big).c_str());
    }
    {
        printf("unsigned long \n");
        unsigned long number  = 0xEFFFAAFFEFFFAAFF;
        unsigned long big     = FlipEndian(number);
        unsigned long little  = FlipEndian(big);
    
        printf("Same:          %d\n", little == number);
        
        printf("Number:        %s\n", ConvertToBinary(number).c_str());
        printf("Little Endian: %s\n", ConvertToBinary(little).c_str());
        printf("Big Endian:    %s\n", ConvertToBinary(big).c_str());
    }
    {
        printf("long \n");
        long number  = 0xEFFFAAFFEFFFAAFF;
        long big     = FlipEndian(number);
        long little  = FlipEndian(big);
    
        printf("Same:          %d\n", little == number);
        
        printf("Number:        %s\n", ConvertToBinary(number).c_str());
        printf("Little Endian: %s\n", ConvertToBinary(little).c_str());
        printf("Big Endian:    %s\n", ConvertToBinary(big).c_str());
    }
    {
        printf("double \n");
        double number  = 0xEFFFAAFFEFFFAAFF;
        double big     = FlipEndian(number);
        double little  = FlipEndian(big);
    
        printf("Same:          %d\n", little == number);
        
        printf("Number:        %s\n", ConvertToBinary(number).c_str());
        printf("Little Endian: %s\n", ConvertToBinary(little).c_str());
        printf("Big Endian:    %s\n", ConvertToBinary(big).c_str());
    }
    
    printf(" ############################## End ztest_endian.cpp... ############################## \n");
  }
  
}

#ifndef _RUN_ALL_TEST_
int main()
{
  zg::ztest_endian();
}
#endif
