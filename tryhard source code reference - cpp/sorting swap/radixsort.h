#ifndef _RADIXSORT_H
#define _RADIXSORT_H

#include "swap.h"

// A utility function to get maximum value in a[]
int getMax(int a[], int n)
{
    int mx = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] > mx)
            mx = a[i];
    return mx;
}
 
// A function to do counting sort of a[] according to
// the digit represented by exp.
void countSort(int a[], int n, int exp)
{
    int output[n]; // output aay
    int i, count[10] = {0};
 
    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[ (a[i]/exp)%10 ]++;
 
 
    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
 
    // Build the output aay
    for (i = n - 1; i >= 0; i--)
    {
        output[count[ (a[i]/exp)%10 ] - 1] = a[i];
        count[ (a[i]/exp)%10 ]--;
    }
 
    // Copy the output aay to a[], so that a[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        a[i] = output[i];
}
 
// The main function to that sorts a[] of size n using 
// Radix Sort
void RadixSort(int* a, int n)
{
    // Find the maximum number to know number of digits
    int m = getMax(a, n);
 
    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; m/exp > 0; exp *= 10)
        countSort(a, n, exp);
      
}




#endif //_RADIXSORT_H
