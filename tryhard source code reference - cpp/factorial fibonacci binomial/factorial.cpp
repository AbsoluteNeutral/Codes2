
#include "factorial.h"

namespace zg{
  /* __________ TFactorial */
  unsigned Factorial(unsigned N_)
  {
    unsigned value = 1;
    while(N_)
      value *= N_--;
    return value;
  }
  
  /* __________ Binomial */
  unsigned nCr(unsigned N_, unsigned R_)
  {
    return Factorial(N_) / (Factorial(N_-R_) * Factorial(R_));
  }

} //namespace zg

//#define _TEST_THIS 1
#ifdef _TEST_THIS
#include <iostream>
/* Recursive */
unsigned FactorialRecursive(unsigned N_)
{
  if(N_ <= 1) return 1;

  return FactorialRecursive(N_- 1) * N_;
}

/* Iterative forloop */
unsigned FactorialItreativeFor(unsigned N_)
{
  unsigned value = 1;
  for(unsigned i = N_; i > 1; --i)
  {
    value *= N_;
    --N_;
  }
  return value;
}

/* Iterative while */
unsigned FactorialItreativeWhile(unsigned N_)
{
  unsigned value = 1;
  while(N_)
    value *= N_--;
  return value;
}

/* Print Vector, only works for classes with 
  std::os& opeartor<<(std::ostream& os_, const class& classname_) 
  overload 
*/
template<typename T>
void PrintVector(const std::vector<T>& vec_)
{
  for(const auto& elem :vec_) 
  {
    std::cout << elem << " ";
  }
  std::cout << std::endl;
}

int main()
{
  printf("Running factorial.cpp...\n\n");

  std::cout << "TFactorial " << "FactorialRecursive "  << "FactorialItreativeWhile " << "FactorialItreativeFor" << std::endl;
  std::cout << zg::TFactorial<0>::val  << " " << FactorialRecursive(0)  << " " << FactorialItreativeWhile(0) << " " << FactorialItreativeFor(0) << std::endl;
	std::cout << zg::TFactorial<1>::val  << " " << FactorialRecursive(1)  << " " << FactorialItreativeWhile(1) << " " << FactorialItreativeFor(1) << std::endl;
  std::cout << zg::TFactorial<2>::val  << " " << FactorialRecursive(2)  << " " << FactorialItreativeWhile(2) << " " << FactorialItreativeFor(2) << std::endl;	
  std::cout << zg::TFactorial<3>::val  << " " << FactorialRecursive(3)  << " " << FactorialItreativeWhile(3) << " " << FactorialItreativeFor(3) << std::endl;	
  std::cout << zg::TFactorial<10>::val << " " << FactorialRecursive(10) << " " << FactorialItreativeWhile(10)<< " " << FactorialItreativeFor(10) << std::endl;
  std::cout << std::endl;

  std::cout << "GetBinomialSequence Test:" << std::endl;
  PrintVector(zg::GetBinomialSequence(0));
  PrintVector(zg::GetBinomialSequence(1));
  PrintVector(zg::GetBinomialSequence(2));
  PrintVector(zg::GetBinomialSequence(3));
  PrintVector(zg::GetBinomialSequence(4));
  PrintVector(zg::GetBinomialSequence(5));
  PrintVector(zg::GetBinomialSequence(6));
  PrintVector(zg::GetBinomialSequence(7));
  PrintVector(zg::GetBinomialSequence(8));
  PrintVector(zg::GetBinomialSequence(9));
  PrintVector(zg::GetBinomialSequence(10));
  std::cout << std::endl;
  
  std::cout << "TnCr Test:" << std::endl;
  std::cout << zg::TnCr<0, 0>::val << std::endl;
  std::cout << zg::TnCr<1, 0>::val << " " << zg::TnCr<1, 1>::val << std::endl;
  std::cout << zg::TnCr<2, 0>::val << " " << zg::TnCr<2, 1>::val << " " << zg::TnCr<2, 2>::val << std::endl;
  std::cout << zg::TnCr<3, 0>::val << " " << zg::TnCr<3, 1>::val << " " << zg::TnCr<3, 2>::val << " " << zg::TnCr<3, 3>::val << std::endl;
  std::cout << zg::TnCr<4, 0>::val << " " << zg::TnCr<4, 1>::val << " " << zg::TnCr<4, 2>::val << " " << zg::TnCr<4, 3>::val << " " << zg::TnCr<4, 4>::val << std::endl;
  std::cout << std::endl;
  
  std::cout << "nCr Test:" << std::endl;
  std::cout << zg::nCr(0, 0) << std::endl;
  std::cout << zg::nCr(1, 0) << " " << zg::nCr(1, 1) << std::endl;
  std::cout << zg::nCr(2, 0) << " " << zg::nCr(2, 1) << " " << zg::nCr(2, 2) << std::endl;
  std::cout << zg::nCr(3, 0) << " " << zg::nCr(3, 1) << " " << zg::nCr(3, 2) << " " << zg::nCr(3, 3) << std::endl;
  std::cout << zg::nCr(4, 0) << " " << zg::nCr(4, 1) << " " << zg::nCr(4, 2) << " " << zg::nCr(4, 3) << " " << zg::nCr(4, 4) << std::endl;
}

#endif