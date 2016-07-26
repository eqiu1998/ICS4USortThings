//
//  main.cpp
//  ICS4USortThings
//
//  Created by Eric Qiu on 2016-03-11.
//  Copyright © 2016 Eric Qiu. All rights reserved.
//

#include <ctime>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <array>
#include <cstring>
#include <algorithm>

using namespace std;

bool is_sorted(int inArray[], int size) {
    bool sorted = true;
    for (int i = 1; i < size; i++) {
        if (inArray[i] < inArray[i - 1]) sorted = false;
    }
    return sorted;
}

void PrintArray(int inArray[], int size) {
    for (int i = 0; i < size - 1; i++) {
        cout << inArray[i] << " ";
    }
    cout << inArray[size - 1] << endl;
}


void SelectionSort(int inArray[], int size){
    // a[0] to a[n-1] is the array to sort
    int minIndex;
    int n = size;
    // move through array
    for (int i = 0; i < n-1; i++) {
        // assume element i is min element
        minIndex = i;
        // compare with all elements after i
        for ( int j = i+1; j < n; j++) {
            // if element j less than element i then set as new minimum
            if (inArray[j] < inArray[minIndex]) {
                // found new minimum; remember its index
                minIndex = j;
            }
        }
        
        if(minIndex != i) {
            // If min element is not at i, swap
            swap(inArray[i], inArray[minIndex]);
        }
        
    }
}

void BubbleSort(int inArray[], int size) {
    int N = size;
    do {
        int newN = 0;
        for (int i = 1; i < N; i++) {
            if (inArray[i-1] > inArray[i]) {
                swap(inArray[i-1], inArray[i]);
                newN = i;
            }
        }
        N = newN;
    } while (N != 0);
}

void merge(int a[], const int low, const int mid, const int high)
{
    int *temp = new int[high-low+1];
    
    int left = low;
    int right = mid+1;
    int current = 0;
    // Merges the two arrays into temp[]
    while(left <= mid && right <= high) {
        if(a[left] <= a[right]) {
            temp[current] = a[left];
            left++;
        }
        else { // if right element is smaller that the left
            temp[current] = a[right];
            right++;
        }
        current++;
    }
    
    // Completes the array
    
       if(left > mid) {
        for(int i=right; i <= high;i++) {
            temp[current] = a[i];
            current++;
        }
    }
        else {
        for(int i=left; i <= mid; i++) {
            temp[current] = a[i];
            current++;
        }
    }
    // into the original array
    for(int i=0; i<=high-low;i++) {
        a[i+low] = temp[i];
    }
    a = temp;
    delete[] temp;
}

void MergeSort(int a[], const int low, const int high)
{
    int mid = (low+high)/2;
    MergeSort(a, low, mid);  //left half
    MergeSort(a, mid+1, high);  //right half
    merge(a, low, mid, high);  //merge them
}

void QuickSort(int inArray[], int left, int right) {
    int i = left, j = right;
    int pivot = inArray[(left + right) / 2];
    
    /* partition */
    while (i <= j) {
        while (inArray[i] < pivot)
            i++;
        while (inArray[j] > pivot)
            j--;
        if (i <= j) {
            swap(inArray[i], inArray[j]);
            i++;
            j--;
        }
    };
    
    /* recursion */
    if (left < j)
        QuickSort(inArray, left, j);
    if (i < right)
        QuickSort(inArray, i, right);
}

void siftDown( int *a, int k, int N);

void HeapSort( int a[], int N){
    /* heapify */
    for (int k = N/2; k >= 0; k--) {
        siftDown( a, k, N);
    }
    
    while (N-1 > 0) {
        /* swap the root(maximum value) of the heap
         with the last element of the heap */
        swap(a[N-1], a[0]);
        /* put the heap back in max-heap order */
        siftDown(a, 0, N-1);
        /* N-- : decrease the size of the heap by one
         so that the previous max value will
        	stay in its proper placement */
        N--;
    }
}

void siftDown( int *a, int k, int N){
    while ( k*2 + 1 < N ) {
        /* For zero-based arrays, the children are 2*i+1 and 2*i+2 */
        int child = 2*k + 1;
        
        /* get bigger child if there are two children */
        if ((child + 1 < N) && (a[child] < a[child+1])) child++;
        
        if (a[k] < a[child]) {   /* out of max-heap order */
            swap( a[child], a[k] );
            /* repeat to continue sifting down the child now */
            k = child;  
        }        
        else            
            return;    
    }
}

int main(int argc, const char * argv[]) {
    cout << "Hello! what algorithm would you like to test?\nA. Selection Sort\nB. Bubble Sort\nC. MergeSort\nD. QuickSort\nE. HeapSort\n\nSelection: ";
    string userInput;
    cin >> userInput;
    char algorithm = toupper(userInput[0]);
    cout << "Test with what size array? ";
    cin >> userInput;
    string arraySize = userInput;
    
    int N = stoi(arraySize);
    string filename = "data" + arraySize + ".txt";
    ifstream inFile(filename);
    
    int inArray[N];
    string buffer;
    for (int i = 0; i < N; i++) {
        getline(inFile, buffer);
        inArray[i] = atoi(buffer.c_str());
    }
    printf("Before: ");
    PrintArray(inArray, N);
    clock_t begin, end;
    switch (algorithm) {
        case 'A':
            begin = clock();
            SelectionSort(inArray, N);
            end = clock();
            break;
        case 'B':
            begin = clock();
            BubbleSort(inArray, N);
            end = clock();
            break;
        case 'C':
            begin = clock();
            MergeSort(inArray, 0, N);
            end = clock();
            break;
        case 'D':
            begin = clock();
            QuickSort(inArray, 0, N);
            end = clock();
            break;
        case 'E':
            begin = clock();
            HeapSort(inArray, N);
            end = clock();
            break;
        default:
            break;
    }
    printf("After: ");
    PrintArray(inArray, N);
    double elapsedSecs = double(end - begin) / CLOCKS_PER_SEC;
    printf ("Elapsed time is %.6lf seconds.\n", elapsedSecs);
    if (is_sorted(inArray, N)) {
        cout << "Sorted" << endl;
    } else {
        cout << "NOT SORTED" << endl;
    }
}
