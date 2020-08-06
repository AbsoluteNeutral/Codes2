#ifndef _MERGESORT_H
#define _MERGESORT_H

#include "swap.h"

void Merge(int *a, int l, int m, int r){
    unsigned i = 0; // Initial index of first subaay
    unsigned j = 0; // Initial index of second subaay
    unsigned k = l; // Initial index of merged subaay
  
    int n1 = m - l + 1;
    int n2 = r - m;
 
    /* create temp aays */
    int L[n1], R[n2];
 
    /* Copy data to temp aays L[] and R[] */
    for (; i < n1; i++)
        L[i] = a[l + i];
    for (; j < n2; j++)
        R[j] = a[m + 1+ j];
 
    /* Merge the temp aays back into a[l..r]*/
    i = 0; // Initial index of first subaay
    j = 0; // Initial index of second subaay
    while (i < n1 && j < n2){
        if (L[i] <= R[j])
            a[k++] = L[i++];
        else
            a[k++] = R[j++];
    }
    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
        a[k++] = L[i++]; 
    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
        a[k++] = R[j++];
}

void MergeSort(int* a, int l, int r){
  if(l < r){
    const int m = (l + r)/2;
    MergeSort(a, l, m);
    MergeSort(a, m + 1, r);
    Merge(a, l, m, r);
    sortDump(a);
  }
}




#endif //_MERGESORT_H
