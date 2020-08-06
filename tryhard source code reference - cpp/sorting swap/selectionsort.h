#ifndef _SELECTIONSORT_H
#define _SELECTIONSORT_H

#include "swap.h"

void SelectionSort(int* a, int sz){
  for(int i = 0; i < sz-1; ++i){
    int min = i;
    
    for(int j = i + 1; j < sz; ++j){
      if(a[j] < a[min])
        min = j;
    }
    swap(a[i], a[min]);
    sortDump(a);
  }
}

template<typename T>
void SelectionSort_Template(T* begin, T* end){
	T *b = begin;
	while (b != end){
		T* min = b;
		T* j = b;
		while (j != end){
			if (*j < *min)
				min = j;
			++j;
		}
		Swap(*min, *b);
		++b;
	}
}

void BiSelectionSort(int* a, int sz){
  int h = sz/2;
  for(int i = 0; i < h; ++i){
    int min = i;
    int max = sz - i - 1;
    for(int j = i; j < sz-i; ++j){
      if(a[j] < a[min])
        min = j;
      if(a[j] > a[max])
        max = j;
    }
    swap(a[min], a[i]);
    if(i==max)
      swap(a[min], a[sz-i-1]);
    else
      swap(a[max], a[sz-i-1]);
    
    
  }
}



#endif //_SELECTIONSORT_H
