#include <stdio.h>
#include <iostream>

struct A
{
  A()
  {
    std::cout << "A()" << std::endl;
  }
  ~A()
  {
    std::cout << "~A()" << std::endl;
  }
};

struct B : A
{
  B()
  {
    std::cout << "B()" << std::endl;
  }
  ~B()
  {
    std::cout << "~B()" << std::endl;
  }
};

struct A1
{
  A1()
  {
    std::cout << "A1()" << std::endl;
  }
  virtual ~A1()
  {
    std::cout << "~A1()" << std::endl;
  }
};

struct B1 : A1
{
  B1()
  {
    std::cout << "B1()" << std::endl;
  }
  ~B1()
  {
    std::cout << "~B1()" << std::endl;
  }
};

struct B2
{
  B2()
  {
    std::cout << "B2()" << std::endl;
  }
  ~B2()
  {
    std::cout << "~B2()" << std::endl;
  }
  
  A a;
  A1 a1;
};

int main()
{
  std::cout << "\nTest 1" << std::endl;
  {
    B b;
  }
  
  std::cout << "\nTest 2" << std::endl;
  {
    B* b = new B;
    delete b;
  }
  
  std::cout << "\nTest 3" << std::endl;
  {
    A* a = new B;
    delete a;
  }
  
  
  std::cout << "\nTest 4 : virtual" << std::endl;
  {
    B1* a1 = new B1;
    delete a1;
  }
  
  std::cout << "\nTest 5 : virtual" << std::endl;
  {
    A1* a1 = new B1;
    delete a1;
  }
  
  std::cout << "\nTest 6" << std::endl;
  {
    B2 b2;
  }
}
