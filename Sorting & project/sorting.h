#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <math.h>
#include <time.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Function to Duplicate a new array
void Duplicate(int arr[], int duplicate[], int n);
// New function for measuring sorting performance
void MeasureSortTime(void (*sortFunction)(int[], int), int arr[], int n, long long &running_time);
void MeasureSortComparisons(void (*sortFunction_Comparisons)(int[], int, long long&), int arr[], int n, long long &comparison);
// Prototype for original sorting functions
void selectionSort(int a[], int n);
void insertionSort(int a[], int n);
void bubbleSort(int a[], int n);
void shakerSort(int a[], int n);
void shellSort(int a[], int n);
void heapSort(int a[], int n);
void mergeSort(int a[], int n);
void quickSort(int a[], int n);
void countingSort(int a[], int n);
void radixSort(int a[], int n);
void flashSort(int a[], int n);
void binaryInsertionSort(int arr[], int n);

// Prototype for comparison counting versions
void selectionSort(int a[], int n, long long &comparison);
void insertionSort(int a[], int n, long long &comparison);
void bubbleSort(int a[], int n, long long &comparison);
void shakerSort(int a[], int n, long long &comparison);
void shellSort(int a[], int n, long long &comparison);
void heapSort(int a[], int n, long long &comparison);
void mergeSort(int a[], int n, long long &comparison);
void quickSort(int a[], int n, long long &comparison);
void countingSort(int a[], int n, long long &comparison);
void radixSort(int a[], int n, long long &comparison);
void flashSort(int a[], int n, long long &comparison);
void binaryInsertionSort(int arr[], int n, long long &comparisons);

// Data generator functions
void GenerateRandomData(int a[], int n);
void GenerateSortedData(int a[], int n);
void GenerateReverseData(int a[], int n);
void GenerateNearlySortedData(int a[], int n);
void GenerateData(int a[], int n, int dataType);

// Project Arg
void Project_Arg(int argc, char* argv[]);