#include<iostream>
#include<fstream>
#include<vector>
#include<cstring>
#include<sstream>
#include<stack>
#include<queue>

using namespace std;

//1. Calculate the sum of S = 1 + 2 + 3 + ... + n.

int sum(int n) {
    if(n == 0) return 0;

    return n + sum(n-1);
}

//2. Calculate the factorial n! = 1 × 2 × 3 × ... × n
int factorial(int n){
    if(n == 0 || n == 1) return 1;

    return n * factorial(n - 1);
}

//3. Calculate x^n.
int power(int x, int n){
    if(n == 0)  return 1;

    return x * power(x, n - 1); 
}

// 4. Determine the total number of digits in a given integer.

int totalDigit(int n ){
    if(n < 0) n = -n;
    if(n < 10) return 1;
    
    return 1 + totalDigit(n / 10);
}

// 5. Check if every digit of a given integer is even.

bool isEvenDigit(int  n) {
    if(n < 0) n = -n;
    if(n == 0) return true;
    if(n % 2 == 1) {
        return false;
    }
    return isEvenDigit(n / 10);        
}

// 6. Calculate the total number of common divisors for two given integers.
int GCD(int a, int b) {
    if(b == 0) return a;
    return GCD(b, a % b);
}

int CountDivisor(int n, int i = 1) {
    if(i > n) return 0;
    return (n % i == 0) + CountDivisor(n, i + 1);
}

int TotalGCD(int a, int b) {
    int g = GCD(a, b);

    return CountDivisor(g, 1);
}

// 7. Find the Greatest common divisor (gcd) and Least common multiple (lcm) of 2 given integers.
int LCM(int a, int b) {
    return a * b / GCD(a, b);
}

// 8. Find the reverse value of a given integer.
int reverseHelper(int n, int ref) {
    if(n == 0) return ref;
    return(n / 10, ref * 10 + n % 10);
}

int reverse(int n) {
    return reverseHelper(n, 0);
}

// 9. Find the reverse of a given array or string.
void ReverseString(string &input, int left, int right){
    if(left >= right) return;
    swap(input[left], input[right]);
    ReverseString(input, left + 1, right - 1);
}

void ReverseArrayHelper(int arr[], int left, int right){
    if(left >= right) return;
    swap(arr[left], arr[right]);
    ReverseArrayHelper(arr, left + 1, right - 1);
}

void ReverseArray(int arr[], int n) {
    return ReverseArrayHelper(arr, 0, n - 1);
}

// 10. Calculate the binary value of a given integer.

string BinHelper(int n) {
    if(n == 0) return "";
    return BinHelper(n / 2) + to_string(n % 2); 
}

string BinVal(int n) {
    if(n == 0) return "";
    return BinHelper(n);
}   

// Calculate the ith Fibonacci number.
// • F0 = 0, F1 = 1
// • Fn = Fn−1 + Fn−2, (n ≥ 2)

int Fibo(int n) {
    if(n == 0) return 0;
    if(n == 1) return 1;
    return Fibo(n - 1) + Fibo(n - 2);
}

//  Generate all possible combinations of k elements from a set of n elements (from 1 to n). 
// For example, if the set is {1, 2, 3, 4} and k = 2, 
// the combinations are {1, 2}, {1, 3}, {1, 4}, {2, 3}, {2, 4}, {3, 4}

void GenerateCombinations(vector<int> &s, int k, vector<vector<int>>& res, vector<int> &temp, int i = 0) {
    if(temp.size() == k) {
        res.push_back(temp);
        return;
    }

    for(i; i < s.size(); i++) {
        temp.push_back(s[i]);
        GenerateCombinations(s, k, res, temp, i + 1);
        temp.pop_back();
    }
    return;
}

// Generate all permutations for a set of 4 unique characters (from A to D). For an extra challenge,
// dapt it to handle an arbitrary number of characters (n). For example, ABCD, ABDC, ACBD

void GeneratePermutations(string& s, vector<string> &res, int left, int right) {
    if(left == right) return;
}

// Given a string s and a dictionary of words wordDict, 
// check if s can be segmented into a spaceseparated sequence of one or more dictionary words.

bool isFound(string word, vector<string> words) {
    for(string s : words) {
        if(word == s) return true;
    }
    return false;
}

//ChaoBan
bool WordBreak(string s, vector<string> words){
    if(s.empty()) return true;
    for(int i = 1; i <= s.size(); i++) {
        string prefix = s.substr(0, i);
        string suffix = s.substr(i);
        if(isFound(prefix, words) && WordBreak(suffix, words)) return true;
    }
    return false;
}

int main() {
    int n = 5;
    // cout << sum(5);
    // cout << factorial(5);
    // cout << power(3 , 5);
    // cout << totalDigit(-1493);
    // cout << GCD(8, 4);
    // cout << TotalGCD(8, 4);
    // cout << reverse(285);
    // string x = "Hello";
    // ReverseString(x, 0, 4);
    // cout << x;
    // string x = BinHelper(100, "");
    // cout << x << endl;
    // cout << BinVal(100);
    // vector<int> s = {1,2,3,4};
    // int k = 2;
    // vector<int> temp = {};
    // vector<vector<int>> res;
    // GenerateCombinations(s, k, res, temp, 0);
    // for(int i = 0; i < res.size(); i++) {
    //     for(int j = 0; j < k; j++) {
    //         cout << res[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // if(WordBreak("ChaoBan", {"Chao", "Ban"})) cout << "YES";
}