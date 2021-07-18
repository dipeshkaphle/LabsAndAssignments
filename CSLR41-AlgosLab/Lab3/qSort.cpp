#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

void qSort(vector<int> &vec, int l, int r) {
  if (r - l <= 1) {
    return;
  }
  auto it = partition(vec.begin() + l, vec.begin() + r,
                      std::bind2nd(std::less<int>(), vec[(l + r - 1) / 2]));
  int m = std::distance(vec.begin(), it);
  qSort(vec, l, m + 1);
  qSort(vec, m + 1, r);
  return;
}

int main() {
  vector<int> arr{10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  qSort(arr, 0, arr.size());
  copy(arr.begin(), arr.end(), ostream_iterator<int>(cout, " "));
}
