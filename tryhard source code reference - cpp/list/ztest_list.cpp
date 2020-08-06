
#include <stdio.h>
#include "zglist.h"

namespace zg{
    
    void Test1_List_Ctor()
    {
      printf(" ############################## Test1_List_Ctor() \n");

      list<int> tmp{};
      tmp.push_back(1);	tmp.print();
      tmp.push_back(2);	tmp.print();
      tmp.push_back(3);	tmp.print();
      tmp.push_back(4);	tmp.print();
      tmp.pop_back();		tmp.print();
      tmp.pop_back();		tmp.print();
      tmp.pop_back();		tmp.print();
  
      tmp.push_back(1);	tmp.print();
      tmp.push_back(2);	tmp.print();
      tmp.push_back(3);	tmp.print();
      tmp.push_back(4);	tmp.print();
      printf("Front Value: %d", tmp.front());
      
      tmp.reverse();		tmp.print();
      printf("Front Value: %d", tmp.front());
      
      tmp.clear();		tmp.print();
      
      printf("\n");
    }
    
    void Test2_isParamIntegral()
    {
      printf(" ############################## Test2_isParamIntegral() \n");
      

      
      printf("\n");
    }
    
    void Test3_isParamFloat()
    {
      printf(" ############################## Test3_isParamFloat() \n");

    
      printf("\n");
    }
    
    void ztest_list()
    {
      printf(" ############################## Running ztest_list.cpp... ############################## \n\n");
      Test1_List_Ctor();
      Test2_isParamIntegral();
      Test3_isParamFloat();
      printf(" ############################## End ztest_list.cpp... ############################## \n\n");
    }
    
    
}

#ifndef _RUN_ALL_TEST_
int main()
{
  zg::ztest_list();
}
#endif
