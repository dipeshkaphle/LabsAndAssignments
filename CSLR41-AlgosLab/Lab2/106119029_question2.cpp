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
    ofstream SSearch("SSearch.txt");
    ofstream BSearch("BSearch.txt");
    chrono::duration<double> elapsed_time;
    // an array of size 1000
    vector<int> arr(200, 0);
    // this will put 1,2,3..1000 in the array
    iota(arr.begin(), arr.end(), 1);
    int index;
    for (int i = 0; i < arr.size(); i++)
    {
        cout << "For element at index " << i << '\n';
        // for ssearch
        cout << "WorstCaseLinearSearch: ";
        auto start_time = chrono::high_resolution_clock::now();
        index = linearsearch(arr, arr[i]);
        auto end_time = chrono::high_resolution_clock::now();
        elapsed_time = chrono::duration_cast<chrono::duration<double>>(end_time - start_time);
        cout << fixed << setprecision(20) << elapsed_time.count() << '\n';
        SSearch << fixed << setprecision(20) << i << ':' << elapsed_time.count() << '\n';

        cout << "WorstCase BinarySearch: ";
        start_time = chrono::high_resolution_clock::now();
        index = binarySearch(arr, arr[i]);
        end_time = chrono::high_resolution_clock::now();
        elapsed_time = chrono::duration_cast<chrono::duration<double>>(end_time - start_time);
        cout << fixed << setprecision(20) << elapsed_time.count() << '\n';
        BSearch << fixed << setprecision(20) << i << ':' << elapsed_time.count() << '\n';
    }
}