#include "quicksort.h"

void swap(int *a, int *b)
{
    int t;
    t = *a;
    *a = *b;
    *b = t;
}

int partition(int *A, int left, int right)
{
    int i, j;
    int pivot = A[right];
    i = left - 1;

    for(j = left; j < right; j++)
    {
        if(A[j] <= pivot)
        {
            i++;
            swap(&A[j], &A[i]);
        }
    }
    swap(&A[i + 1], &A[right]);
    return i + 1;
}

void quicksort(int *A, int left, int right)
{
    if(left < right)
    {
        int pivot = partition(A, left, right);
        quicksort(A, left, pivot - 1);
        quicksort(A, pivot + 1, right);
    }
}