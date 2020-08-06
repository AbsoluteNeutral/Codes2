#ifndef _INSERTIONSORT_H
#define _INSERTIONSORT_H

#include "swap.h"

void InsertionSort(int* a, int N){
  for(int i = 1; i < N; ++i){
    int j = i;
    int current = a[i];
    while( j && (a[j-1] > current)){
      a[j] = a[j-1];
      --j;
    }
    a[j] = current;
    sortDump(a);
  }
}

template<typename T>
void InsertionSortTemplate(T* begin, T* end) {
	T* b = begin+1;
	while(b != end){
		T* s = b;
		while (s != begin && *s < *(s-1)){
			Swap(*s, *(s - 1));
			--s;
		}++b;
	}
}
#endif //_INSERTIONSORT_H
