#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int binarySearch(vector<int> &arr, int key) {
  int l = 0;
  int r = arr.size();
  int mid;
  while (l < r) {
    mid = (l + r) / 2;
    if (arr[mid] == key) {
      return mid;
    } else if (arr[mid] < key) {
      l = mid + 1;
    } else
      r = mid;
  }
  return -1;
}

int main() {
  vector<int> arr{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  cout << binarySearch(arr, 1) << '\n';
  cout << binarySearch(arr, 10) << '\n';
  cout << binarySearch(arr, 11) << '\n';
  cout << binarySearch(arr, 2) << '\n';
  cout << binarySearch(arr, 5) << '\n';
  cout << binarySearch(arr, 8) << '\n';
}
