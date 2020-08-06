#ifndef _QUICKSORT_H
#define _QUICKSORT_H

#include "swap.h"

int Partition(int *a, int i, int j){
  int p = a[i];
  int h = i;
  for(int k = i+1; k <=j; ++k){
    if(a[k] < p){
      ++h;
      swap(a[k], a[h]);
      sortDump(a);
    }
  }
  swap(a[h], a[i]);
  
  return h;
}

void QuickSort(int* a, int l, int r){
  if(l < r){
    const int i = Partition(a, l, r);
    QuickSort(a, l, i - 1);
    QuickSort(a, i + 1, r);
    
  }
}

#endif //_QUICKSORT_H

