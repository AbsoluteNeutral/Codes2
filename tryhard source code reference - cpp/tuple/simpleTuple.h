#ifndef _ZG_SIMPLE_TUPLE_H
#define _ZG_SIMPLE_TUPLE_H

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
}//namespace zg

#endif //_ZG_SIMPLE_TUPLE_H
