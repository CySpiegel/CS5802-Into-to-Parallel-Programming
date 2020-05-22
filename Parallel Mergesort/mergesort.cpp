#include "mergesort.h"

void mergeSort(std::vector<int64_t> &arr, int64_t l, int64_t r) 
{ 
    if (l < r) 
    {
        int64_t m = l+(r-l)/2; 
        mergeSort(arr, l, m); 
        mergeSort(arr, m + 1, r); 
        merge(arr, l, m, r); 
    }
}

void p_mergeSort(std::vector<int64_t> &arr, int64_t l,int64_t r, int count, int THREAD_MAX)
{
    int64_t m;
    if(l < r && count <= THREAD_MAX)
    {
        m = l + (r - l)/2;
        auto future = std::async(std::launch::deferred,[&]() {p_mergeSort(arr, l, r, count + 1, THREAD_MAX);});
        p_mergeSort(arr, l, m, count + 1, THREAD_MAX);
        future.get();
        merge(arr, l, m, r);
    }
    return;
}

void merge(std::vector<int64_t> &arr, int64_t l, int64_t m, int64_t r) 
{ 
    int64_t i, j, k; 
    int64_t n1 = m - l + 1; 
    int64_t n2 =  r - m; 
    vector<int64_t> L, R;

    for (i = 0; i < n1; i++) 
        L.push_back(arr[l + i]); 

    for (j = 0; j < n2; j++) 
        R.push_back(arr[m + 1+ j]); 

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 

    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 

    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
