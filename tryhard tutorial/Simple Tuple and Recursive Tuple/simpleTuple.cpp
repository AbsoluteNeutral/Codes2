#include <iostream>

namespace zg
{
  /*
    Aggregate class:
    - no private memebers
    - class/struct with public members varibles only
    
    simpleTuple is a way to store using "has a" relationship. (see main())
    The members is retrive using "." relationship, which get more messier 
    with longer tuple.
  */
  template<typename T, typename ... Args>
  struct simpleTuple
  {
    T val;
    simpleTuple<Args...> next;
  };
  
  template<typename T>
  struct simpleTuple<T>
  {
    T val;
  };
  
  template<typename ... Args>
  simpleTuple<Args...> make_simple_tuple(Args ... args)
  {
    return simpleTuple<Args...>{args...};
  }
}


int main()
{
  zg::simpleTuple<int, float, double> value {1, 2.2f, 3.4};
  std::cout << value.val << std::endl;
	std::cout << value.next.val << std::endl;
	std::cout << value.next.next.val << std::endl;
	
	auto copied = zg::make_simple_tuple(1, 2.4f, 3.5);
	std::cout << copied.val << std::endl;
	std::cout << copied.next.val << std::endl;
	std::cout << copied.next.next.val << std::endl;
}
