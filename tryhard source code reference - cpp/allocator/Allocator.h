#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_
#include <iostream>

template <typename T>
class IAllocator {
public:
	IAllocator() = default;

	template <typename T>
	IAllocator(const IAllocator<T>&) {}

	T* allocate(size_t n) {
		n *= sizeof(T);
		//std::cout << "allocating " << n << " bytes\n";

		//return static_cast<T*>(::operator new(n));
		return static_cast<T*>(malloc(n));
	}

	void deallocate(T* p, size_t n) {
		//std::cout << "deallocating " << n * sizeof*p << " bytes\n";
		//::operator delete(p);
		free(p);
	}
};

#endif //_ALLOCATOR_H_
