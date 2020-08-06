#include <iostream>
#include <vector>

namespace zg
{
  class TypeErasure
  {
    /*
      Abstract, internal mirror structure of the class/struct
      that is going to pass in, every class that is going to 
      pass in must have the same function, obviously 
    */
    struct Model
    {
      virtual void Print() = 0;
      virtual Model* clone() = 0;
      ~Model(){}
    };
    
    /*
      Instantiate class of the model
    */
    template<typename T>
    struct Instance : Model
    {
      Instance(const T& obj_)
        :obj(obj_)
      {}
      Instance<T>* clone()
      {
        return new Instance(obj);
      }
      
      void Print()
      {
        obj.Print();
      }
      
      T obj;
    };
  
  public:
    template<typename T>
    TypeErasure(const T& obj_)
      :modelPtr(new Instance<T>(obj_))
    {}
    
    TypeErasure(const TypeErasure& rhs)
      :modelPtr(rhs.modelPtr->clone())
    {}
    
    TypeErasure& operator=(const TypeErasure& rhs)
    {
      Model* tmp = rhs.modelPtr->clone();
      delete modelPtr;
      modelPtr = tmp;
      return *this;
    }
    
    ~TypeErasure()
    {
      delete modelPtr;
    }
    
    /*
      Calls Instance's function directed by virtual function
    */
    void Print()
    {
      modelPtr->Print();
    }

    Model* modelPtr;
  };
}

struct DummyA {
  void Print() { std::cout << "DummyA" << std::endl; }
};
struct DummyB { 
  void Print() { std::cout << "DummyB" << std::endl; }
};
struct DummyC {
  void Print() { std::cout << "DummyC" << std::endl; }
};
struct DummyD {
  void Print() { std::cout << "DummyD" << std::endl; }
};

int main()
{
  std::vector<zg::TypeErasure> listofNoType
  {
    DummyA{}, DummyB{}, DummyC{}, DummyD{}
  };
  
  listofNoType[0].Print();
  listofNoType[1].Print();
  listofNoType[2].Print();
  listofNoType[3].Print();
}
