#include "sorting.h"

using namespace std;

vector<string> Algorithms = {"selection-sort", "insertion-sort", "bubble-sort", "shaker-sort", "shell-sort", "heap-sort",
                             "merge-sort", "quick-sort", "counting-sort", "radix-sort", "flash-sort"};

vector<string> OutputParams = {"-time", "-comp", "-both"};

vector<string> InputOrders = {"-rand", "-nsorted", "-sorted", "-rev"};

bool isNumber(string input) {
    for (int i = 0; i < input.size(); i++) {
        if (!isdigit(input[i])) {
            return false;
        }
    }
    return true;
}

void ReadFile(string filename, int arr[], int& size) {
    ifstream file(filename);
    if (!file) {
        cout << "Error: Cannot open file " << filename << " for reading!" << endl;
        return;
    }
    file >> size;
    for (int i = 0; i < size; i++) {
        file >> arr[i];
    }
    file.close();
}

void WriteFile(string filename, int arr[], int size) {
    ofstream file(filename);
    if (!file) {
        cout << "Error: Cannot open file " << filename << " for writing!" << endl;
        return;
    }
    file << size << "\n";
    for (int i = 0; i < size; i++) {
        file << arr[i] << " ";
    }
    file.close();
}


void GenerateAndWriteData(string filename, int n, int dataType) {
    ofstream file;
    file.open(filename);
    int *arr = new int[n];
    GenerateData(arr, n, dataType);
    WriteFile(filename, arr, n);
    file.close();
    delete[] arr;
}

void Sort_Project(vector<string> algorithms, string input_file, string Output_Parameter, int check = 0) {
    vector<long long> running_times, comparisons;
    
    for (int i = 0; i < algorithms.size(); i++) {
        ifstream file(input_file);
        int n;
        file >> n;
        int *arr = new int[n];
        for (int i = 0; i < n; i++) {
            file >> arr[i];
        }
        file.close();

        long long comparison = 0, time = 0;

        if (algorithms[i] == "selection-sort") {
            MeasureSortTime(selectionSort, arr, n, time);
            MeasureSortComparisons(selectionSort, arr, n, comparison);
        } else if (algorithms[i]== "insertion-sort") {
            MeasureSortTime(insertionSort, arr, n, time);
            MeasureSortComparisons(insertionSort, arr, n, comparison);
        } else if (algorithms[i] == "bubble-sort") {
            MeasureSortTime(bubbleSort, arr, n, time);
            MeasureSortComparisons(bubbleSort, arr, n, comparison);
        } else if (algorithms[i] == "shaker-sort") {
            MeasureSortTime(shakerSort, arr, n, time);
            MeasureSortComparisons(shakerSort, arr, n, comparison);
        } else if (algorithms[i] == "shell-sort") { 
            MeasureSortTime(shellSort, arr, n, time);
            MeasureSortComparisons(shellSort, arr, n, comparison);
        } else if (algorithms[i] == "heap-sort") {
            MeasureSortTime(heapSort, arr, n, time);
            MeasureSortComparisons(heapSort, arr, n, comparison);
        } else if (algorithms[i] == "merge-sort") {
            MeasureSortTime(mergeSort, arr, n, time);
            MeasureSortComparisons(mergeSort, arr, n, comparison);
        } else if (algorithms[i] == "quick-sort") {
            MeasureSortTime(quickSort, arr, n, time);
            MeasureSortComparisons(quickSort, arr, n, comparison);
        } else if (algorithms[i] == "counting-sort") {
            MeasureSortTime(countingSort, arr, n, time);
            MeasureSortComparisons(countingSort, arr, n, comparison);
        } else if (algorithms[i] == "radix-sort") {
            MeasureSortTime(radixSort, arr, n, time);
            MeasureSortComparisons(radixSort, arr, n, comparison);
        } else if (algorithms[i] == "flash-sort") {
            MeasureSortTime(flashSort, arr, n, time);
            MeasureSortComparisons(flashSort, arr, n, comparison);
        } else if (algorithms[i] == "binary-insertion-sort") {
            MeasureSortTime(binaryInsertionSort, arr, n, time);
            MeasureSortComparisons(binaryInsertionSort, arr, n, comparison);
        }
        running_times.push_back(time);
        comparisons.push_back(comparison);

        if (algorithms.size() == 1 && check == 0) {
            ofstream of;
            of.open("output.txt");
            of << n << "\n";
            for (int i = 0; i < n; i++) {
                of << arr[i] << " ";
            }
        }

        delete[] arr;
    }


    if (Output_Parameter == "-time" || Output_Parameter == "-both" || Output_Parameter.empty()) {
        cout << "Running time: ";
        for (int i = 0; i < running_times.size(); i++) {
            cout << running_times[i];
            if(i < running_times.size() - 1) {
                cout << " | ";
            }
        }
        cout << '\n';
    }

    if (Output_Parameter == "-comp" || Output_Parameter == "-both" || Output_Parameter.empty()) {
        cout << "Comparisons: ";
        for (int i = 0; i < comparisons.size(); i++) {
            cout << comparisons[i];
            if(i < comparisons.size() - 1)
                cout << " | ";   
        }
        cout <<  "\n";
    }
}

/* CommandLine1: [Execution file] -a [Algorithm] [Input filename]| [Output parameter(s)]
   CommandLine2: [Execution file] -a [Algorithm] [Input size] [Input order] [Output parameter(s)]
   CommandLine3: [Execution file] -a [Algorithm] [Input size] [Output parameter(s)]
   CommandLine4: [Execution file] -c [Algorithm 1] [Algorithm 2] [Input filename] 
   CommandLine5: [Execution file] -c [Algorithm 1] [Algorithm 2] [Input size] [Input order]
*/

void CommandLine1(string algorithm, string filename, string outputParams, int size) {
    cout << "ALGORITHM MODE\n";
    cout << "Algorithm\n";
    cout << "Input file: " << filename <<"\n";
    cout << "Input size: " << size << "\n";
    cout << "----------------------------\n";
    Sort_Project({algorithm}, filename, outputParams, 0);
}

void CommandLine2(string algorithm, int size, string input_order, string outputParams){
    int datatype;
    cout << "ALGORITHM MODE\n";
    cout << "Algorithm\n";
    cout << "Input size: " << size << "\n";
    cout << "Input order: " << input_order << "\n";
    cout << "----------------------------\n";
    string file = "input.txt";
    if(input_order == "-rand") datatype = 0;
    if(input_order == "-sorted") datatype = 1;
    if(input_order == "-rev") datatype = 2;
    if(input_order == "-nsorted") datatype = 3;
    GenerateAndWriteData(file, size, datatype);
    Sort_Project({algorithm}, file, outputParams, 0);
}

/*vector<string> InputOrders = {"-rand", "-nsorted", "-sorted", "-rev"};*/
void CommandLine3(string algorithm, int size, string outputParams) {
    for (int i = 0; i < 4; i++) {
        
        cout << "Input order: " << InputOrders[i] << "\n";
        cout << "--------------------\n";
        int num;
        int datatype;
        if(i == 0) num = 1, datatype = 0;
        if(i == 1) num = 2, datatype = 3;
        if(i == 2) num = 3, datatype = 1;
        if(i == 3) num = 4, datatype = 2;
        string inputFile = "input_" + to_string(num) + ".txt";
        GenerateAndWriteData(inputFile, size, datatype);

        Sort_Project({algorithm}, inputFile, outputParams, 1);
        cout << "\n";
    }
}

void CommandLine4(string algorithm1, string algorithm2, string filename, int size) {
    cout << "COMPARE MODE\n";
    cout << "Algorithm: " << algorithm1 << " | " << algorithm2 << "\n";
    cout << "Input file: " << filename << "\n";
    cout << "Input size: " << size << "\n";
    cout << "----------------------------\n";
    vector<string> algorithms;
    Sort_Project({algorithm1, algorithm2}, filename, "-both", 1);
}

/* CommandLine5: [Execution file] -c [Algorithm 1] [Algorithm 2] [Input size] [Input order]*/
void CommandLine5(string algorithm1, string algorithm2, int size, string input_order) {
    cout << "COMPARE MODE\n";
    cout << "Algorithm: " << algorithm1 << " | " << algorithm2 << "\n";
    cout << "Input size: " << size << "\n";
    cout << "Input order: " << input_order <<"\n";
    cout << "----------------------------\n";
    string inputFile = "input.txt";

    int datatype;
    if(input_order == "-rand") datatype = 0;
    if(input_order == "-sorted") datatype = 1;
    if(input_order == "-rev") datatype = 2;
    if(input_order == "-nsorted") datatype = 3;
    GenerateAndWriteData(inputFile, size, datatype);

    Sort_Project({algorithm1, algorithm2}, inputFile, "-both", 1);

}

/*-------------------------Project Argument------------------------*/
void Project_Arg(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Error: Not enough arguments provided!\n";
        return;
    }

    string mode = argv[1];

    if (mode == "-a") {  // Algorithm Mode
        string algorithm = argv[2];

        if (isNumber(argv[3])) {  
            int size = stoi(argv[3]);
            bool flag = false;
            for (int i = 0; i < InputOrders.size(); i++) {
                if (InputOrders[i] == string(argv[4])) {
                    flag = true;
                    break;
                }
            }
            if (flag) {
                /*CommandLine2: [Execution file] -a [Algorithm] [Input size] [Input order] [Output parameter(s)]*/
                string input_order = argv[4];
                string outputParams;
                if(argc > 5){
                    outputParams = argv[5];
                } else {
                    outputParams = "";
                }
                CommandLine2(algorithm, size, input_order, outputParams);
            } 
            else {
                /*CommandLine3: [Execution file] -a [Algorithm] [Input size] [Output parameter(s)]*/
                string outputParams;
                if(argc > 4) {
                    outputParams = argv[4];
                } else {
                    outputParams = "";
                } 
                CommandLine3(algorithm, size, outputParams);
            }
        } 
        else {  
            /*CommandLine1: [Execution file] -a [Algorithm] [Input filename]| [Output parameter(s)]*/
            int size;
            string input_file = argv[3];
            string outputParams;
            if(argc > 4){
                outputParams = argv[4];
            } else {
                outputParams = "";
            }
            
            ifstream file(input_file);
            if (file.is_open()) {
                file >> size; 
                file.close();
            } else {
                cout << "Error: Can't open file " << input_file  << "\n";
                return;
            }
            CommandLine1(algorithm, input_file, outputParams, size);
        }
    } 
    else if (mode == "-c") {  // Comparison Mode
        if (argc < 5) {
            cout << "Error: Not enough arguments for comparison mode!\n";
            return;
        }

        string algorithm1 = argv[2], algorithm2 = argv[3];

        if (isNumber(argv[4])) {  
            /*CommandLine5: [Execution file] -c [Algorithm 1] [Algorithm 2] [Input size] [Input order]*/
            int size = stoi(argv[4]);
            string input_order = argv[5];
            CommandLine5(algorithm1, algorithm2, size, input_order);
        } 
        else {  
            /*CommandLine4: [Execution file] -c [Algorithm 1] [Algorithm 2] [Input filename]*/
            int size;
            string input_file = argv[4];

            ifstream file(input_file);
            if (file.is_open()) {
                file >> size; 
                file.close();
            } else {
                cout << "Error: Can't open file " << input_file << "\n";
                return;
            }

            CommandLine4(algorithm1, algorithm2, input_file, size);
        }
    } 
    else {
        cout << "Error: Invalid mode!\n";
    }
}

