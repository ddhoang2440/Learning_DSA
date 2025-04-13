#include "sorting.h"

using namespace std;

vector<string> Algorithms = {"selection-sort", "insertion-sort", "bubble-sort", "shaker-sort", "shell-sort", "heap-sort",
                             "merge-sort", "quick-sort", "counting-sort", "radix-sort", "flash-sort"};

vector<string> InputOrders = {"-rand", "-nsorted", "-sorted", "-rev"};

void RunExperimentAllAlgorithms(vector<int> sizes) {
    ofstream outFile("experiment.txt");
    if (!outFile) {
        cout << "Error: Cannot create experiment.txt file!" << endl;
        return;
    }

    outFile << "Algorithm, Input Order, Size, Time (ms), Comparisons\n";

    for (string algorithm : Algorithms) {
        for (string order : InputOrders) {
            for (int size : sizes) {
                string inputFile = "temp_input.txt";
                int dataType;
                if (order == "-rand") dataType = 0;
                if (order == "-sorted") dataType = 1;
                if (order == "-rev") dataType = 2;
                if (order == "-nsorted") dataType = 3;

                GenerateAndWriteData(inputFile, size, dataType);

                ifstream file(inputFile);
                int n;
                file >> n;
                int *arr = new int[n];
                for (int i = 0; i < n; i++) {
                    file >> arr[i];
                }
                file.close();

                long long comparisons = 0, time = 0;

                if (algorithm == "selection-sort") 
                    MeasureSortTime_Comp(selectionSort, selectionSort, arr, n, comparisons, time);
                else if (algorithm == "insertion-sort") 
                    MeasureSortTime_Comp(insertionSort, insertionSort, arr, n, comparisons, time);
                else if (algorithm == "bubble-sort") 
                    MeasureSortTime_Comp(bubbleSort, bubbleSort, arr, n, comparisons, time);
                else if (algorithm == "shaker-sort") 
                    MeasureSortTime_Comp(shakerSort, shakerSort, arr, n, comparisons, time);
                else if (algorithm == "shell-sort") 
                    MeasureSortTime_Comp(shellSort, shellSort, arr, n, comparisons, time);
                else if (algorithm == "heap-sort") 
                    MeasureSortTime_Comp(heapSort, heapSort, arr, n, comparisons, time);
                else if (algorithm == "merge-sort") 
                    MeasureSortTime_Comp(mergeSort, mergeSort, arr, n, comparisons, time);
                else if (algorithm == "quick-sort") 
                    MeasureSortTime_Comp(quickSort, quickSort, arr, n, comparisons, time);
                else if (algorithm == "counting-sort") 
                    MeasureSortTime_Comp(countingSort, countingSort, arr, n, comparisons, time);
                else if (algorithm == "radix-sort") 
                    MeasureSortTime_Comp(radixSort, radixSort, arr, n, comparisons, time);
                else if (algorithm == "flash-sort") 
                    MeasureSortTime_Comp(flashSort, flashSort, arr, n, comparisons, time);

                outFile << algorithm << ", " << order << ", " << size << ", " << time << ", " << comparisons << "\n";

                delete[] arr;
            }
        }
    }

    outFile.close();
    cout << "Experiment completed! Results saved to experiment.txt" << endl;
}