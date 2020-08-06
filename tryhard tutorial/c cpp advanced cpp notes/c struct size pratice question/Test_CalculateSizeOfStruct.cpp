#include <stdio.h>
#include <iostream>

struct A
{
};

struct B
{
  bool b;
};

struct C
{
  int a;
  bool b;
  //padding 3
};

struct D
{
  bool a; // & 0
          // & 1 + padding 3, align to multiple of 4 -> sizeof(int) = 4
  int b;  // & 4
  bool c; // & 8 
          // & 9 + padding 7, align to multiple of 8 -> sizeof(long) = 8
  long d; // & 16, Largest size in C's -> sizeof(int) = 4
  C e;    // & 24, sizeof(C) = 8, 24 is multiple of 8, no padding/align needed
  bool f; // & 32
          // & 33, padding 7, align to multiple of 8 (largest size is sizeof(long) = 8)
          // & 40, multiple of 8
};

struct E
{
  int a;
};

struct F
{
  bool a; // & 0
          // & 1 + padding 3, align to multiple of 4 -> sizeof(int) = 4
  int b;  // & 4
  bool c; // & 8 
          // & 9 + padding 7, align to multiple of 8 -> sizeof(long) = 8
  long d; // & 16, Largest size in C's -> sizeof(int) = 4
  E e;    // & 24, sizeof(E) = 4, 24 is multiple of 4, no padding/align needed
  bool f; // & 28
          // & 29, padding 3, align to multiple of 8 (largest size is sizeof(long) = 8)
          // & 32, multiple of 8
};

int main()
{
  std::cout << "Size Of A: " << sizeof(A) << std::endl;
  std::cout << "Size Of B: " << sizeof(B) << std::endl;
  std::cout << "Size Of C: " << sizeof(C) << std::endl;
  std::cout << "Size Of D: " << sizeof(D) << std::endl;
  std::cout << "Size Of E: " << sizeof(E) << std::endl;
  std::cout << "Size Of F: " << sizeof(F) << std::endl;
}
