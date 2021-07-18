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

int linearsearch(vector<int> &arr, int key)
{
    int len = arr.size();
    for (int i = 0; i < len; i++)
    {
        if (arr[i] == key)
            return i;
    }
    return -1;
}

int main()
{
    srand(time(0));
    vector<int> size_array{100, 200, 400, 800, 1600, 3200, 6400, 12800, 25600, 51200, 102400};
    ofstream SSearch("WorstCaseSSearch.txt");
    ofstream BSearch("WorstCaseBSearch.txt");
    chrono::duration<double> elapsed_time;
    vector<int> arr;
    int index, key;
    for (int size : size_array)
    {
        cout << "FOR SIZE=" << size << '\n';
        arr.clear();
        arr.resize(size);
        // puts 1,2,3,4..size in the array
        iota(arr.begin(), arr.end(), 1);
        // the value size+1 will never be in the record, so this will always yield worst time
        key = size + 1;
        // for ssearch
        cout << "LinearSearch: ";
        auto start_time = chrono::high_resolution_clock::now();
        index = linearsearch(arr, key);
        auto end_time = chrono::high_resolution_clock::now();
        elapsed_time = chrono::duration_cast<chrono::duration<double>>(end_time - start_time);
        cout << fixed << setprecision(20) << elapsed_time.count() << '\n';
        SSearch << fixed << setprecision(20) << size << ':' << elapsed_time.count() << '\n';

        cout << "BinarySearch: ";
        start_time = chrono::high_resolution_clock::now();
        index = binarySearch(arr, key);
        end_time = chrono::high_resolution_clock::now();
        elapsed_time = chrono::duration_cast<chrono::duration<double>>(end_time - start_time);
        cout << fixed << setprecision(20) << elapsed_time.count() << '\n';
        BSearch << fixed << setprecision(20) << size << ':' << elapsed_time.count() << '\n';
    }
}