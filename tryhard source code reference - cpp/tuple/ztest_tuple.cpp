#include <iostream>
#include "tuple.h"
#include "simpleTuple.h"

int main()
{
#ifdef TEST_SIMPLETUPLE
  zg::simpleTuple<int, float, double> value {1, 2.2f, 3.4};
  std::cout << value.val << std::endl;
	std::cout << value.next.val << std::endl;
	std::cout << value.next.next.val << std::endl;
	
	auto copied = zg::make_simple_tuple(1, 2.4f, 3.5);
	std::cout << copied.val << std::endl;
	std::cout << copied.next.val << std::endl;
	std::cout << copied.next.next.val << std::endl;
#endif
  
#ifdef TEST_TUPLE
  zg::Tuple<int, float, double> a {1, 2.2f, 3.4};
  std::cout << zg::get<0>(a) << std::endl;
	std::cout << zg::get<1>(a) << std::endl;
  std::cout << zg::get<2>(a) << std::endl;	
  std::cout << zg::get<2>(a) << std::endl;	
  
  auto copied = zg::make_tuple(1, 2.4f, 3.5);
  std::cout << zg::get<0>(copied) << std::endl;
	std::cout << zg::get<1>(copied) << std::endl;
  std::cout << zg::get<2>(copied) << std::endl;	
#endif
}
