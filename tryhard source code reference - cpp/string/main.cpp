
#include "string.h"
#include <string>

int main()
{
  zg::string a{"asada"};
	
	std::cout << a << std::endl;
	a = "abcdefghijkl";
  std::cout << "string     :" << a << std::endl;
  std::cout << "string size:" << a.size() << std::endl;
  std::cout << "string leng:" << a.length() << std::endl;
	
	
	try
	{
		std::cout << "string at 1:" << a.at(1) << std::endl;
		//std::cout << a.at(-1) << std::endl;
		//std::cout << a.at(8) << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		throw;
	}
	//a.clear();
	try
	{
		std::cout << "string fron:" << a.front() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		throw;
	}
	std::cout << "string back:" << a.back() << std::endl;
	
	const zg::string b{"abcdefgh"};
	std::cout << "consts fron:" << b.front() << std::endl;
	std::cout << "consts back:" << b.back() << std::endl;
	
}