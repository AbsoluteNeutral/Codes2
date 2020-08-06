#ifndef _ZG_TUPLE_H
#define _ZG_TUPLE_H

namespace zg
{
  //______________________________________________________________________
  /*
    Dummy parent struct
  */
  template<typename... Args>
  struct Tuple{};
  
  /*
    Store Recursivly the tuple
  */
  template<typename T, typename... Args>
  struct Tuple<T, Args...>
  {
    T value;
    Tuple<Args...> subTuple;
    
    Tuple(T value_, Args... args_)
      :value(value_), subTuple(args_...)
    {}
  };
  //______________________________________________________________________
  
  //______________________________________________________________________
  /*
    Dummy parent struct for "get"
  */
  template<unsigned N, typename... Args>
  struct TupleElement{};
  
  /*
    Specialize 1:
    - Applies meta programming method to retrive "Args..." varibles.
    - This class decrement N till 0 and retrive the type and value of 
    the current tuple
  */
  template<unsigned N, typename T, typename... Args>
  struct TupleElement<N, T, Args...> : TupleElement<N-1, Args...>
  {
    using BaseClass = TupleElement<N-1, Args...>;
    using type = typename BaseClass::type;
    
    TupleElement(Tuple<T, Args...>& tuple_)
      :BaseClass(tuple_.subTuple)
    {}
  };
  
  /*
    Have an End Specialize struct/class to stop
  */
  template<typename Arg, typename... Args>
  struct TupleElement<0, Arg, Args...>
  {
    using type = Arg;
    Tuple<Arg, Args...>& tuple;
    
    TupleElement(Tuple<Arg, Args...>& tuple_)
      :tuple(tuple_)
      {}
    Arg& get()
    {
      return tuple.value;
    }
  };
  
  /*
    get;

    Get the value at the index of tuple, if exist
    if not exist, compile error
  */
  template<unsigned N, typename... Args>
  typename TupleElement<N, Args...>::type& get(Tuple<Args...>& tuple_)
  {
    TupleElement<N, Args...>tuple_element(tuple_);
    return tuple_element.get();
  }
  //______________________________________________________________________
  
  //______________________________________________________________________
  
  
  //______________________________________________________________________
  
  
  /*
    make_tuple
  */
  template<typename... Args>
  Tuple<Args...> make_tuple(Args ... args)
  {
    return Tuple<Args...>{args...};
  }
}


#endif // _ZG_TUPLE_H
