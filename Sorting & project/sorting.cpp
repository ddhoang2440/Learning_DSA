#include "sorting.h"

//copy original array
void Duplicate(int arr[], int duplicate[], int n) {
    for (int i = 0; i < n; i++) {
        duplicate[i] = arr[i];
    }
}

/***************Measure Sort Comparisons and Running time*****************/
void MeasureSortTime(void (*sortFunction)(int[], int), int arr[], int n, long long &running_time) {
    int *copyArray = new int[n];
    Duplicate(arr, copyArray, n);

    auto start = high_resolution_clock::now();
    sortFunction(copyArray, n);
    auto stop = high_resolution_clock::now();

    running_time = duration_cast<milliseconds>(stop - start).count();

    delete[] copyArray;
}

void MeasureSortComparisons(void (*sortFunction_Comparisons)(int[], int, long long&), int arr[], int n, long long &comparison) {
    comparison = 0;
    sortFunction_Comparisons(arr, n, comparison);
}

/***************************************/
// selection sort
void selectionSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIdx])
            {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}

void selectionSort(int arr[], int n, long long &comparisons)
{
    comparisons = 0;
    for (int i = 0; ++comparisons && i < n - 1; i++)
    {
        int minIdx = i;
        for (int j = i + 1; ++comparisons && j < n; j++)
        {
            if (++comparisons && arr[j] < arr[minIdx])
            {
                minIdx = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[minIdx];
        arr[minIdx] = temp;
    }
}

/***************************************/
// insertion sort
void insertionSort(int arr[], int n)
{
    int i, j, key;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void insertionSort(int arr[], int n, long long &comparisons)
{
    comparisons = 0;

    int i, j, key;
    for (i = 1; ++comparisons && i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while ((++comparisons && j >= 0) && (++comparisons && arr[j] > key))
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

/***************************************/
// binary insertion sort
void binaryInsertionSort(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int l = 0, r = i - 1;
        while (l <= r)
        {
            int m = (l + r) / 2;
            if (key < arr[m])
                r = m - 1;
            else
                l = m + 1;
        }

        for (int j = i - 1; j >= l; j--)
        {
            arr[j + 1] = arr[j];
        }
        arr[l] = key;
    }
}

void binaryInsertionSort(int arr[], int n, long long &comparisons)
{
    comparisons = 0;
    for (int i = 1; ++comparisons && i < n; i++)
    {
        int key = arr[i];
        int l = 0, r = i - 1;
        while (++comparisons && l <= r)
        {
            int m = (l + r) / 2;
            if (++comparisons && key < arr[m])
                r = m - 1;
            else
                l = m + 1;
        }

        for (int j = i - 1; ++comparisons && j >= l; j--)
        {
            arr[j + 1] = arr[j];
        }
        arr[l] = key;
    }
}

/***************************************/
// bubble sort
void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (arr[j + 1] < arr[j])
                swap(arr[j + 1], arr[j]);
        }
    }
}

void bubbleSort(int arr[], int n, long long &comparisons)
{
    for (int i = 0; ++comparisons && i < n - 1; i++)
    {
        for (int j = 0; ++comparisons && j < n - 1 - i; j++)
        {
            if (++comparisons && arr[j + 1] < arr[j])
                swap(arr[j + 1], arr[j]);
        }
    }
}

/***************************************/
// shaker sort
void shakerSort(int arr[], int n)
{
    int left = 0;
    int right = n - 1;
    int k = 0;

    while (left < right)
    {
        bool swapped = false;
        for (int i = left; i < right; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                swap(arr[i], arr[i + 1]);
                k = i;
                swapped = true;
            }
        }

        if (swapped == false)
            break;
        right = k;

        swapped = false;
        for (int i = right; i > left; i--)
        {
            if (arr[i] < arr[i - 1])
            {
                swap(arr[i], arr[i - 1]);
                k = i;
                swapped = true;
            }
        }
        if (swapped == false)
            break;
        left = k;
    }
}

void shakerSort(int arr[], int n, long long &comparisons)
{
    comparisons = 0;
    int left = 0;
    int right = n - 1;
    int k = 0;

    while (++comparisons && left < right)
    {
        bool swapped = false;
        for (int i = left; ++comparisons && i < right; i++)
        {
            if (++comparisons && arr[i] > arr[i + 1])
            {
                swap(arr[i], arr[i + 1]);
                k = i;
                swapped = true;
            }
        }

        if (++comparisons && swapped == false)
            break;
        right = k;

        swapped = false;
        for (int i = right; ++comparisons && i > left; i--)
        {
            if (++comparisons && arr[i] < arr[i - 1])
            {
                swap(arr[i], arr[i - 1]);
                k = i;
                swapped = true;
            }
        }

        if (++comparisons && swapped == false)
            break;

        left = k;
    }
}

/***************************************/
// shell sort
void shellSort(int arr[], int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i += 1)
        {
            int temp = arr[i];

            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            {
                arr[j] = arr[j - gap];
            }

            arr[j] = temp;
        }
    }
}

void shellSort(int arr[], int n, long long &comparisons)
{
    comparisons = 0;
    for (int gap = n / 2; ++comparisons && gap > 0; gap /= 2)
    {
        for (int i = gap; ++comparisons && i < n; i++)
        {
            int temp = arr[i];

            int j;
            for (j = i; (++comparisons && j >= gap) && (++comparisons && arr[j - gap] > temp); j -= gap)
            {
                arr[j] = arr[j - gap];
            }

            arr[j] = temp;
        }
    }
}

/***************************************/
// heap sort
void maxHeap(int arr[], int i, int n)
{
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int mx = i;

    if (l <= n - 1 && arr[l] > arr[mx])
    {
        mx = l;
    }

    if (r <= n - 1 && arr[r] > arr[mx])
    {
        mx = r;
    }

    if (mx != i)
    {
        swap(arr[i], arr[mx]);
        maxHeap(arr, mx, n);
    }
}

void buildMaxHeap(int arr[], int n)
{
    for (int i = (n / 2) - 1; i >= 0; --i)
    {
        maxHeap(arr, i, n);
    }
}

void heapSort(int arr[], int n)
{

    buildMaxHeap(arr, n);
    int sz = n;

    while (sz)
    {
        swap(arr[0], arr[sz - 1]);
        --sz;
        maxHeap(arr, 0, sz);
    }
}

void maxHeap(int arr[], int i, int n, long long &comparisons)
{
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int mx = i;

    if (++comparisons && l <= n - 1 && ++comparisons && arr[l] > arr[mx])
    {
        mx = l;
    }

    if (++comparisons && r <= n - 1 && ++comparisons && arr[r] > arr[mx])
    {
        mx = r;
    }

    if (++comparisons && mx != i)
    {
        swap(arr[i], arr[mx]);
        maxHeap(arr, mx, n, comparisons);
    }
}

void buildMaxHeap(int arr[], int n, long long &comparisons)
{
    for (int i = (n / 2) - 1; ++comparisons && i >= 0; --i)
    {
        maxHeap(arr, i, n, comparisons);
    }
}

void heapSort(int arr[], int n, long long &comparisons)
{
    comparisons = 0;
    buildMaxHeap(arr, n, comparisons);
    int sz = n;

    while (++comparisons && sz)
    {
        swap(arr[0], arr[sz - 1]);
        --sz;
        maxHeap(arr, 0, sz, comparisons);
    }
}

/***************************************/
// merge sort
void Merge(int arr[], int l, int mid, int r)
{
    int *a = new int[r - l + 1];
    int i = l, j = mid + 1, k = 0;

    while (i <= mid && j <= r)
    {
        if (arr[i] < arr[j])
            a[k++] = arr[i++];
        else
            a[k++] = arr[j++];
    }
    while (i <= mid)
    {
        a[k++] = arr[i++];
    }
    while (j <= r)
    {
        a[k++] = arr[j++];
    }

    for (int i = 0; i < k; i++)
    {
        arr[l++] = a[i];
    }

    delete[] a;
}

void MergeSort(int arr[], int l, int r)
{
    if (l >= r)
        return;

    int mid = (l + r) / 2;
    MergeSort(arr, l, mid);
    MergeSort(arr, mid + 1, r);

    Merge(arr, l, mid, r);
}

void mergeSort(int arr[], int n)
{
    MergeSort(arr, 0, n - 1);
}

void Merge(int arr[], int l, int mid, int r, long long &comparisons)
{
    int *a = new int[r - l + 1];
    int i = l, j = mid + 1, k = 0;

    while (++comparisons && i <= mid && ++comparisons && j <= r)
    {
        if (++comparisons && arr[i] < arr[j])
            a[k++] = arr[i++];
        else
            a[k++] = arr[j++];
    }
    while (++comparisons && i <= mid)
    {
        a[k++] = arr[i++];
    }
    while (++comparisons && j <= r)
    {
        a[k++] = arr[j++];
    }

    for (int i = 0; ++comparisons && i < k; i++)
    {
        arr[l++] = a[i];
    }
}

void MergeSort(int arr[], int l, int r, long long &comparisons)
{
    if (++comparisons && l >= r)
        return;

    int mid = (l + r) / 2;
    MergeSort(arr, l, mid, comparisons);
    MergeSort(arr, mid + 1, r, comparisons);
    Merge(arr, l, mid, r, comparisons);
}

void mergeSort(int arr[], int n, long long &comparisons)
{
    MergeSort(arr, 0, n - 1, comparisons);
}

/***************************************/
// quick sort

int sortFirstMiddleLast(int arr[], int first, int last)
{
    int mid = first + (last - first) / 2;
    if (arr[first] > arr[mid])
        swap(arr[first], arr[mid]);
    if (arr[mid] > arr[last])
        swap(arr[mid], arr[last]);
    if (arr[first] > arr[mid])
        swap(arr[first], arr[mid]);
    return mid;
}

int partition(int arr[], int first, int last)
{

    int pivotIndex = sortFirstMiddleLast(arr, first, last);

    swap(arr[pivotIndex], arr[last - 1]);
    pivotIndex = last - 1;
    int pivot = arr[pivotIndex];

    int indexFromLeft = first + 1, indexFromRight = last - 2;
    bool done = false;
    while (!done)
    {

        while (arr[indexFromLeft] < pivot)
            indexFromLeft++;

        while (arr[indexFromRight] > pivot)
            indexFromRight--;

        if (indexFromLeft < indexFromRight)
        {
            swap(arr[indexFromLeft], arr[indexFromRight]);
            indexFromLeft++;
            indexFromRight--;
        }
        else
            done = true;
    }

    swap(arr[pivotIndex], arr[indexFromLeft]);
    pivotIndex = indexFromLeft;
    return pivotIndex;
}

void quickSort(int arr[], int first, int last)
{

    if (first >= last) return;
    else

    {

        int pivotIndex = partition(arr, first, last);

        quickSort(arr, first, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, last);
    }
}

void quickSort(int arr[], int n)
{
    quickSort(arr, 0, n - 1);
}

int sortFirstMiddleLastCom(int arr[], int first, int last, long long &comparisons)
{
    int mid = first + (last - first) / 2;
    if (++comparisons && arr[first] > arr[mid])
        swap(arr[first], arr[mid]);
    if (++comparisons && arr[mid] > arr[last])
        swap(arr[mid], arr[last]);
    if (++comparisons && arr[first] > arr[mid])
        swap(arr[first], arr[mid]);
    return mid;
}

int partitionCom(int arr[], int first, int last, long long &comparisons)
{
    int pivotIndex = sortFirstMiddleLastCom(arr, first, last, comparisons);

    swap(arr[pivotIndex], arr[last - 1]);
    pivotIndex = last - 1;
    int pivot = arr[pivotIndex];

    int indexFromLeft = first + 1, indexFromRight = last - 2;
    bool done = false;
    while (!done)
    {

        while (++comparisons && arr[indexFromLeft] < pivot)
            indexFromLeft++;

        while (++comparisons && arr[indexFromRight] > pivot)
            indexFromRight--;

        if (++comparisons && indexFromLeft < indexFromRight)
        {
            swap(arr[indexFromLeft], arr[indexFromRight]);
            indexFromLeft++;
            indexFromRight--;
        }
        else
            done = true;
    }

    swap(arr[pivotIndex], arr[indexFromLeft]);
    pivotIndex = indexFromLeft;
    return pivotIndex;
}

void quickSort(int arr[], int first, int last, long long &comparisons)
{

    if (++comparisons && first >= last) return;
    else

    {

        int pivotIndex = partition(arr, first, last);

        quickSort(arr, first, pivotIndex - 1, comparisons);
        quickSort(arr, pivotIndex + 1, last, comparisons);
    }
}

void quickSort(int arr[], int n, long long &comparisons)
{

    quickSort(arr, 0, n - 1, comparisons);
}

/***************************************/
// counting sort
void countingSort(int arr[], int n) {
    int maxx = INT_MIN, minn = INT_MAX;

    // Finding the min and max values
    for (int i = 0; i < n; i++) {
        if (arr[i] > maxx) maxx = arr[i];
        if (arr[i] < minn) minn = arr[i];
    }

    int range = maxx - minn + 1;
    int* c = new int[range](); // Allocate and initialize to 0

    // Count occurrences
    for (int i = 0; i < n; i++) {
        c[arr[i] - minn]++;
    }

    // Accumulate the counts
    for (int i = 1; i < range; i++) {
        c[i] += c[i - 1];
    }

    // Sorting using the count array
    int* o = new int[n];
    for (int i = n - 1; i >= 0; i--) {
        int index = arr[i] - minn;
        o[c[index] - 1] = arr[i];
        c[index]--;
    }

    // Copy sorted elements back to original array
    for (int i = 0; i < n; i++) {
        arr[i] = o[i];
    }

    delete[] c; // Free allocated memory
    delete[] o; // Free allocated memory
}
void countingSort(int arr[], int n, long long& comparisons) {
    comparisons = 0;
    int maxx = INT_MIN, minn = INT_MAX;

    // Finding min and max values
    for (int i = 0; i < n; i++) {
        if (++comparisons && arr[i] > maxx) maxx = arr[i];
        if (++comparisons && arr[i] < minn) minn = arr[i];
    }

    int range = maxx - minn + 1;
    int* c = new int[range](); // Allocate and initialize to 0

    // Count occurrences
    for (int i = 0; i < n; i++) {
        c[arr[i] - minn]++;
        comparisons++;
    }

    // Accumulate the counts
    for (int i = 1; i < range; i++) {
        c[i] += c[i - 1];
        comparisons++;
    }

    // Sorting using the count array
    int* o = new int[n];
    for (int i = n - 1; i >= 0; i--) {
        int index = arr[i] - minn;
        o[c[index] - 1] = arr[i];
        c[index]--;
        comparisons++;
    }

    // Copy sorted elements back to original array
    for (int i = 0; i < n; i++) {
        arr[i] = o[i];
        comparisons++;
    }

    delete[] c;
    delete[] o;
}


void countingSort(int arr[], int n, int exp, int minn) {
    int* o = new int[n];
    int c[10] = {0};
    
    for (int i = 0;  i < n; i++) {
        c[((arr[i] - minn) / exp % 10)]++;
    }
    
    for (int i = 1;  i < 10; i++)
        c[i] += c[i - 1];
    
    for (int i = n - 1;  i >= 0; i--) {
        o[c[((arr[i] - minn) / exp % 10)] - 1] = arr[i];
        c[((arr[i] - minn) / exp % 10)]--;
    }

    for (int i = 0;  i < n; i++)
        arr[i] = o[i];
    
    delete[] o;
}
void countingSort(int arr[], int n, int exp, int minn, long long& comparisons) {
    int* o = new int[n];
    int c[10] = {0};
    
    for (int i = 0; ++comparisons && i < n; i++) {
        c[((arr[i] - minn) / exp % 10)]++;
    }
    
    for (int i = 1; ++comparisons && i < 10; i++)
        c[i] += c[i - 1];
    
    for (int i = n - 1; ++comparisons && i >= 0; i--) {
        o[c[((arr[i] - minn) / exp % 10)] - 1] = arr[i];
        c[((arr[i] - minn) / exp % 10)]--;
    }

    for (int i = 0; ++comparisons && i < n; i++)
        arr[i] = o[i];
    
    delete[] o;
}

/***************************************/
// radix sort
int getMax(int arr[], int n)
{
    int maxx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > maxx)
            maxx = arr[i];
    return maxx;
}
int getMax(int arr[], int n, long long &comparisons)
{
    int maxx = arr[0];
    for (int i = 1; ++comparisons && i < n; i++)
        if (++comparisons && arr[i] > maxx)
            maxx = arr[i];
    return maxx;
}
int getMin(int arr[], int n)
{
    int minn = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] < minn)
            minn = arr[i];
    return minn;
}
int getMin(int arr[], int n, long long &comparisons)
{
    int minn = arr[0];
    for (int i = 1; ++comparisons && i < n; i++)
        if (++comparisons && arr[i] < minn)
            minn = arr[i];
    return minn;
}

void radixSort(int arr[], int n)
{
    int minn = getMin(arr, n);

    int *shiftedArr = new int[n];
    for (int i = 0; i < n; i++)
    {
        shiftedArr[i] = arr[i] - minn;
    }

    int maxx = getMax(arr, n);
    long long temp = 0;
    for (int exp = 1; maxx / exp > 0; exp *= 10)
        countingSort(shiftedArr, n, exp, minn);

    for (int i = 0; i < n; i++)
    {
        arr[i] = shiftedArr[i] + minn;
    }

    delete[] shiftedArr;
}
void radixSort(int arr[], int n, long long &comparisons)
{
    comparisons = 0;

    int minn = getMin(arr, n, comparisons);

    int *shiftedArr = new int[n];
    for (int i = 0; ++comparisons && i < n; i++)
    {
        shiftedArr[i] = arr[i] - minn;
    }

    int maxx = getMax(arr, n, comparisons);
    for (int exp = 1; ++comparisons && maxx / exp > 0; exp *= 10)
        countingSort(shiftedArr, n, exp, minn, comparisons);

    for (int i = 0; ++comparisons && i < n; i++)
    {
        arr[i] = shiftedArr[i] + minn;
    }

    delete[] shiftedArr;
}

/***************************************/
// flash sort
int getBucketNum(int a, int m, int max, int min)
{
    return 1ll * (m - 1) * (a - min) / (max - min);
}

void flashSort(int arr[], int n)
{
    if (n <= 1)
        return;

    // Step 1
    int m = n * 0.45;
    if (m <= 2)
        m = 2;

    int *bucket = new int[m];
    for (int i = 0; i < m; ++i)
    {
        bucket[i] = 0;
    }

    int max = arr[0], min = arr[0];
    for (int i = 1; i < n; ++i)
    {
        if (max < arr[i])
            max = arr[i];
        if (min > arr[i])
            min = arr[i];
    }

    if (max == min)
    {
        delete[] bucket;
        return;
    }

    for (int i = 0; i < n; ++i)
    {
        ++bucket[getBucketNum(arr[i], m, max, min)];
    }
    for (int i = 1; i < m; ++i)
    {
        bucket[i] += bucket[i - 1];
    }

    // Step 2
    int count = 0;
    int i = 0;
    while (count < n)
    {
        int k = getBucketNum(arr[i], m, max, min);
        while (i >= bucket[k])
        {
            k = getBucketNum(arr[++i], m, max, min);
        }
        int z = arr[i];
        while (i != bucket[k])
        {
            k = getBucketNum(z, m, max, min);
            int y = arr[bucket[k] - 1];
            arr[--bucket[k]] = z;
            z = y;
            ++count;
        }
    }

    // Step 3
    for (int k = 1; k < m; ++k)
    {
        for (int i = bucket[k] - 2; i >= bucket[k - 1]; --i)
        {
            if (arr[i] > arr[i + 1])
            {
                int t = arr[i], j = i;
                while (t > arr[j + 1])
                {
                    arr[j] = arr[j + 1];
                    ++j;
                }
                arr[j] = t;
            }
        }
    }

    delete[] bucket;
}

void flashSort(int arr[], int n, long long &comparisons)
{
    if (++comparisons && n <= 1)
        return;

    // Step 1
    int m = n * 0.45;
    if (++comparisons && m <= 2)
        m = 2;

    int *bucket = new int[m];
    for (int i = 0; ++comparisons && i < m; ++i)
        bucket[i] = 0;

    int max = arr[0], min = arr[0];
    for (int i = 1; ++comparisons && i < n; ++i)
    {
        if (++comparisons && max < arr[i])
            max = arr[i];
        else if (++comparisons && min > arr[i])
            min = arr[i];
    }

    if (++comparisons && max == min)
    {
        delete[] bucket;
        return;
    }

    for (int i = 0; ++comparisons && i < n; ++i)
        ++bucket[getBucketNum(arr[i], m, max, min)];
    for (int i = 1; ++comparisons && i < m; ++i)
        bucket[i] += bucket[i - 1];

    // Step 2
    int count = 0;
    int i = 0;
    while (++comparisons && count < n)
    {
        int k = getBucketNum(arr[i], m, max, min);
        while (++comparisons && i >= bucket[k])
            k = getBucketNum(arr[++i], m, max, min);

        int z = arr[i];
        while (++comparisons && i != bucket[k])
        {
            k = getBucketNum(z, m, max, min);
            int y = arr[bucket[k] - 1];
            arr[--bucket[k]] = z;
            z = y;
            ++count;
        }
    }

    // Step 3
    for (int k = 1; ++comparisons && k < m; ++k)
    {
        for (int i = bucket[k] - 2; ++comparisons && i >= bucket[k - 1]; --i)
        {
            if (++comparisons && arr[i] > arr[i + 1])
            {
                int t = arr[i], j = i;
                while (++comparisons && t > arr[j + 1])
                {
                    arr[j] = arr[j + 1];
                    ++j;
                }
                arr[j] = t;
            }
        }
    }

    delete[] bucket;
}


