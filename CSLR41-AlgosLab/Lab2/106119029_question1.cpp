#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <numeric>
#include <iomanip>
#include <cstdlib>

using namespace std;

int binarySearch(vector<int> &arr, int key)
{ // iterative binary search
    int l = 0;
    int r = arr.size();
    int mid;
    while (l < r)
    {
        mid = (l + r) / 2;
        if (arr[mid] == key)
        {
            return mid;
        }
        else if (arr[mid] < key)
        {
            l = mid + 1;
        }
        else
            r = mid;
    }
    return -1;
}
int main()
{
    srand(time(0));
    vector<int> size_array{100, 200, 400, 800, 1600, 3200, 6400, 12800, 25600, 51200, 102400};
    ofstream best_case("BestCaseQ1.txt");
    ofstream worst_case("WorstCaseQ1.txt");
    ofstream random_case("RandomCaseQ1.txt");
    vector<int> arr;
    int key;   // this will store the value to be searched
    int index; // the returned index will be stored
    chrono::duration<double> elapsed_time;
    for (auto size : size_array)
    {
        cout << "FOR ARRAY OF SIZE " << size << '\n';
        arr.clear();
        // allocates size for array
        arr.resize(size);
        // this fills the array  with 1,2,3... size
        iota(arr.begin(), arr.end(), 1);

        // for best time , the value should be in the middle for binary search
        // so i'll assign key that value
        // so itll find the answer in first attempt itself
        key = arr[arr.size() / 2];
        cout << "BEST TIME: ";
        // stores start time
        auto start_time = chrono::high_resolution_clock::now();
        index = binarySearch(arr, key);
        //stores end point
        auto end_time = chrono::high_resolution_clock::now();

        // gets the elapsed time
        elapsed_time = chrono::duration_cast<chrono::duration<double>>(end_time - start_time);
        cout << fixed << setprecision(30) << elapsed_time.count() << '\n';
        best_case << size << ':' << fixed << setprecision(30) << elapsed_time.count() << '\n';

        // for worst case
        // the key shuldnt be there
        // this value will not be present in arr because it only
        // has 1..size
        key = size + 1;
        cout << "WORST TIME: ";
        start_time = chrono::high_resolution_clock::now();
        index = binarySearch(arr, key);
        end_time = chrono::high_resolution_clock::now();

        elapsed_time = chrono::duration_cast<chrono::duration<double>>(end_time - start_time);
        cout << fixed << setprecision(30) << elapsed_time.count() << '\n';
        worst_case << size << ':' << fixed << setprecision(30) << elapsed_time.count() << '\n';

        // for random case
        //
        key = arr[rand() % size];
        cout << "RANDOM CASE TIME: ";
        start_time = chrono::high_resolution_clock::now();
        index = binarySearch(arr, key);
        end_time = chrono::high_resolution_clock::now();

        elapsed_time = chrono::duration_cast<chrono::duration<double>>(end_time - start_time);
        cout << fixed << setprecision(30) << elapsed_time.count() << '\n';
        random_case << size << ':' << fixed << setprecision(30) << elapsed_time.count() << '\n';
        cout << "\n\n\n";
    }
}