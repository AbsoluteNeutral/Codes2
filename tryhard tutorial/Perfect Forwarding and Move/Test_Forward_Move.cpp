#include <iostream>
#include <algorithm>
#include <string>

/*
  Ref collasping Rule:
  &   &  -> &
  &   && -> &
  &&  &  -> &
  &&  && -> &&
  
  Link:
  https://stackoverflow.com/questions/13725747/concise-explanation-of-reference-collapsing-rules-requested-1-a-a-2
*/
  
namespace zg
{
  // default parent class
  template<typename T>
  struct remove_ref
  {
    using type = T;
  };
  
  // specialize class to remove T&& 
  template<typename T>
  struct remove_ref<T&&>
  {
    using type = T;
  };
  
  //specialize class to remove T& 
  template<typename T>
  struct remove_ref<T&>
  {
    using type = T;
  };
  
  
  //forward lvalue as lvalue,
  //forward rvalue as rvalue
	/* 
    Note:
      "typename remove_ref<T>::type" is a non-deduce context,
      forcing the function template to "act" like a class template.
      It's a design as it's forces the user to take note of perfect forwarding
      such as <obj>, <obj&>, <obj&&>
      
      T&& forward(typename remove_ref<T>::type& value) can be just written as
      T&& forward(T& value) and it will work.
      
    More explaination/examples:
    https://stackoverflow.com/questions/25245453/what-is-a-nondeduced-context
    
    example deduction
      eg.1
      if:       forward<obj1&>(arg) is passed,    
      deduce:   T is obj1&,
      deduce:   remove_ref<obj1&>::type = obj1 
      deduce:   value is now of type obj1& 
      returning
      deduce:   return static_cast<T &&>(value);
      deduce:   return static_cast<obj1& &&>(value);
      into->    return static_cast<obj1&>(value);    (lvalue)
      
      eg.2
      if:       forward<obj1>(arg) is passed,     
      deduce:   T is obj1,
      deduce:   remove_ref<obj1>::type = obj1 
      deduce:   value is now of type obj1& 
      returning
      deduce:   return static_cast<T &&>(value);
      deduce:   return static_cast<obj1 &&>(value);
      into->    return static_cast<obj1&&>(value);    (rvalue)
      
      eg.3
      if:       forward<obj1&&>(arg) is passed,     
      deduce:   T is obj1&&,
      deduce:   remove_ref<obj1>::type = obj1 
      deduce:   value is now of type obj1& 
      returning
      deduce:   return static_cast<T &&>(value);
      deduce:   return static_cast<obj1&& &&>(value);
      into->    return static_cast<obj1&&>(value);    (rvalue)
  */
  template<typename T>
  //T&& forward(T& value)
  T&& forward(typename remove_ref<T>::type& value)
  {
    return static_cast<T&&>(value);
  }
  
  /*
    make lvalue or rvalue move to a rvalue
  */
  template<typename T>
  typename remove_ref<T>::type&& move(T&& value) noexcept
  {
    typedef typename remove_ref<T>::type&& rvalueref;
    return static_cast<rvalueref>(value);
  }
  
}

struct obj1 {};
class obj2
{
public:
  obj2()            { std::cout << "obj2() default ctr" << std::endl; }
	obj2(const obj2&) { std::cout << "obj2(const obj2&) copy ctr" << std::endl; }
	obj2(obj2&&)      { std::cout << "obj2::obj2(obj2&&) move ctr" << std::endl; }	
	obj2(const obj1&) { std::cout << "obj2(const obj1&) copy obj1 ctr" << std::endl; }
	obj2(obj1&&)      { std::cout << "obj2(obj1&&) move obj1 ctr" << std::endl; }
	~obj2()           { std::cout << "~obj2()\n"; }
};

int main()
{
  obj1 a;
	obj2 b; //invoke the default constructor
	
  std::cout << "Test 1: \n";
  
  std::cout << "b1 zg::forward: ";
  obj2 b1 { zg::forward<obj2>(b) };
  std::cout << "b2 std::forward: ";
  obj2 b2 { std::forward<obj2>(b) };
  
  std::cout << "b3 zg::forward: ";
  obj2 b3 { zg::forward<obj2&>(b) };
  std::cout << "b4 std::forward: ";
  obj2 b4 { std::forward<obj2&>(b) };
  
  std::cout << "b5 zg::forward: ";
  obj2 b5 { zg::forward<obj2&&>(b) };
  std::cout << "b6 std::forward: ";
  obj2 b6 { std::forward<obj2&&>(b) };
  
  std::cout << "b7 copy ";
  obj2 b7 { b };
  
  std::cout << "b8 zg::move: ";
  obj2 b8 { zg::move(b) };
  std::cout << "b9 std::move: ";
  obj2 b9 { std::move(b) };
  
  std::cout << "b10 zg::forward: ";
  obj2 b10 { zg::forward<obj1&>(a) };
  std::cout << "b11 std::forward: ";
  obj2 b11 { std::forward<obj1&>(a) };
  
  std::cout << "b12 zg::forward: ";
  obj2 b12 { zg::forward<obj1&&>(a) };
  std::cout << "b13 std::forward: ";
  obj2 b13 { std::forward<obj1&&>(a) };
  
  std::cout << "b14 zg::move: ";
  obj2 b14 { zg::move(a) };
  std::cout << "b15 std::move: ";
  obj2 b15 { std::move(a) };
  
	int x;
  int         yy    = zg::move(x);
	const int&& crrx  = zg::move(x);
	int&&       rrx   = zg::move(x);
	//int&        erx   = zg::move(x);        //compile error
	//int&        efrx  = zg::forward<int>(x);//compile error
	int&        frx   = zg::forward<int&>(x); 
	int&        rx    = rrx; 
}

