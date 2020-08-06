#ifndef _BUBBLESORT_H
#define _BUBBLESORT_H

#include "swap.h"

void BubbleSort_ForLoop(int* a, int sz){
  for(int i = 0; i < sz; ++i){
    for(int j = 0; j < sz-i-1; ++j){
      if(a[j] > a[j+1])
        swap(a[j], a[j+1]);
    }
  }
}

void BubbleSort_Adaptive(int* a, int sz){
  for(int i = 0; i < sz; ++i){
    bool swapped = false;
    for(int j = 0; j < sz-i-1; ++j){
      if(a[j] > a[j+1]){
        swap(a[j], a[j+1]);
        swapped |= 1;
      }
    }
    if(!swapped) return;
  }
}
template<typename T>
void BubbleSort_Template(T* begin, T* end){
	T* e = end;
	while(e != begin){
    bool swapped = false;
		T* b = begin;
		while (b != e-1){
			if (*(b + 1) < *b) {
        swap(*b, *(b + 1));
        swapped |= 1;
      }++b;
		}
    if(!swapped) return;
    --e;
	}
}

template<typename T>
void BubbleSort_TemplateSize(T* begin, int sz){
	T* e = begin + sz;
	while(e != begin){
    bool swapped = false;
		T* b = begin;
		while (b != e-1){
			if (*(b + 1) < *b) {
        swap(*b, *(b + 1));
        swapped |= 1;
      }++b;
		}
    if(!swapped) return;
    --e;
	}
}

#endif //_BUBBLESORT_H
