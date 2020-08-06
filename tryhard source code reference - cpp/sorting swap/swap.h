#ifndef _SWAP_H
#define _SWAP_H

template<typename T>
void swap(T& a , T& b)
{
  T c{a};
  a = b;
  b = c;
}

//Plain Old Function
void swap(int& a, int& b)
{
  //bitwise
  /*
    in binary 
    let a = 0010_1111
    let b = 1110_1010
    
    a = 0010_1111 ^ 
        1110_1010   = 1100_0101
    b = 1100_0101 ^ 
        1110_1010   = 0010_1111 = a
    a = 1100_0101 ^ 
        0010_1111    = 1110_1010 = b
  */
  a = a ^ b;
  b = a ^ b;
  a = a ^ b;

  /*
    arithmentic
    a = a + b_
    b = (a + b) - b 
      = a
    a = (a + b) - b 
      = (a + b) - a
      = b
  */
  //a = a + b;
  //b = a - b;
  //a = a - b;
}
void swap(int* a, int* b)
{
  //bitwise
  int c = *a;
  int d = *b;
  c = c ^ d;
  d = c ^ d;
  c = c ^ d;
  *a = c;
  *b = d;
}

#endif //_SWAP_H
