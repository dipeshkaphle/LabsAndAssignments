#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <unistd.h>
#include <unordered_map>
#include <vector>

using namespace std;

template <typename Func, typename... Args>
double timeMyFunction(Func func, Args &...args) {
  auto start_time = std::chrono::steady_clock::now();
  func(args...);
  auto end_time = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_time =
      std::chrono::duration_cast<std::chrono::duration<double>>(end_time -
                                                                start_time);
  return elapsed_time.count();
}

void merge_sorted_arrays(vector<int> &vec, int l, int m, int r) {
  vector<int> left_arr(m - l);
  vector<int> right_arr(r - m);
  copy(vec.begin() + l, vec.begin() + m, left_arr.begin());
  copy(vec.begin() + m, vec.begin() + m, right_arr.begin());
  int i = l;
  int l_i = 0;
  int r_i = 0;
  while (i < r) {
    if (l_i < left_arr.size() && r_i < right_arr.size()) {
      if (left_arr[l_i] <= right_arr[r_i]) {
        vec[i] = left_arr[l_i];
        l_i++;
      } else {
        vec[i] = right_arr[r_i];
        r_i++;
      }
      i++;
    } else if (l_i < left_arr.size()) {
      copy(left_arr.begin() + l_i, left_arr.end(), vec.begin() + i);
      break;
    } else {
      copy(right_arr.begin() + r_i, right_arr.end(), vec.begin() + i);
      break;
    }
  }
  return;
}

void mergesort(vector<int> &vec, int l, int r) {
  if (r - l == 1) {
    return;
  }
  int m = (l + r) / 2;
  mergesort(vec, l, m);
  mergesort(vec, m, r);
  merge_sorted_arrays(vec, l, m, r);
}

int main() {
  nice(-20);
  srand(time(0));
  ofstream merge_sort("MergeSort.txt");
  double time_elapsed;
  for (int size : {800, 1600, 3200, 6400, 12800, 25600, 51200, 102400}) {
    // vector<int> sizes(100);
    // iota(sizes.begin(), sizes.end(), 4);
    // a will be reverse sorted array
    int l = 0;
    vector<int> reverseSorteda(size);
    iota(reverseSorteda.begin(), reverseSorteda.end(), 1);
    reverse(reverseSorteda.begin(), reverseSorteda.end());

    // will generate random numbers and put it in array of size =size
    vector<int> randomArrA(size);
    generate(randomArrA.begin(), randomArrA.end(), []() { return rand(); });

    //
    //
    // worst cases
    time_elapsed = timeMyFunction(mergesort, reverseSorteda, l, size);
    cout << "Merge Sort Worst for  "
         << "size " << size << ": " << fixed << setprecision(30) << time_elapsed
         << endl;
    merge_sort << "Worst:" << size << ":" << fixed << setprecision(30)
               << time_elapsed << endl;

    assert(is_sorted(reverseSorteda.begin(), reverseSorteda.end()));

    //
    //
    //
    //
    //
    //
    // Random cases
    time_elapsed = timeMyFunction(mergesort, randomArrA, l, size);
    cout << "Merge Sort Random Case for  "
         << "size " << size << ": " << fixed << setprecision(30) << time_elapsed
         << endl;
    merge_sort << "Random:" << size << ":" << fixed << setprecision(30)
               << time_elapsed << endl;
    assert(is_sorted(randomArrA.begin(), randomArrA.end()));
    //
    //
    //
    // Best case
    // I'll just use the arrays from last sort, as they'll be sorted and  hence
    // it should be best case
    time_elapsed = timeMyFunction(mergesort, randomArrA, l, size);
    cout << "Merge Sort Best Case for  "
         << "size " << size << ": " << fixed << setprecision(30) << time_elapsed
         << endl;
    merge_sort << "Best:" << size << ":" << fixed << setprecision(30)
               << time_elapsed << endl;
    assert(is_sorted(randomArrA.begin(), randomArrA.end()));
    cout << endl;
    cout << endl;
  }
}
