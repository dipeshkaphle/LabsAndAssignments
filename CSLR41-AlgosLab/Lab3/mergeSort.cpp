#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
void mergeSort(vector<int> &vec, int l, int r) {
  if (r - l == 1) {
    return;
  }
  int m = (l + r) / 2;
  mergeSort(vec, l, m);
  mergeSort(vec, m, r);
  inplace_merge(vec.begin() + l, vec.begin() + m, vec.begin() + r);
}

int main() {
  vector<int> arr{10, 9, 8, 7, 6, 5, 4, 3};
  mergeSort(arr, 0, arr.size());
  copy(arr.begin(), arr.end(), ostream_iterator<int>(cout, " "));
}
