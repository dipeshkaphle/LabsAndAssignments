#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

template <typename Func, typename... Args>
double timeMyFunction(Func func, Args &&...args) {
  auto start_time = std::chrono::steady_clock::now();
  func(args...);
  auto end_time = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_time =
      std::chrono::duration_cast<std::chrono::duration<double>>(end_time -
                                                                start_time);
  return elapsed_time.count();
}
inline int qsort_partition(vector<int> &vec, int l, int r, int offset = 0) {
  int k = l;
  swap(vec[l + offset], vec[l]);
  for (int i = l + 1; i < r; i++) {
    if (vec[i] <= vec[l]) {
      swap(vec[++k], vec[i]);
    }
  }
  swap(vec[l], vec[k]);
  return k;
}

void qSort(vector<int> &vec, int l, int r, bool randomized = false) {
  srand(time(NULL));
  if (r - l <= 1) {
    return;
  }
  int off = randomized ? rand() % (r - l) : 0;
  int m = qsort_partition(vec, l, r, off);
  qSort(vec, l, m, randomized);
  qSort(vec, m + 1, r, randomized);
  return;
}

void stl_sort(vector<int> &vec) { sort(vec.begin(), vec.end()); }

void printDetails(ostream &os, const string &algo_name, const string &case_name,
                  double time_elapsed, size_t size) {
  os << algo_name << case_name << ":" << size << ": " << fixed
     << setprecision(30) << time_elapsed << endl;
}

int main() {
  srand(time(0));
  ofstream q_sort("QuickSort.txt");
  ofstream q_sort_rand("QuickSortRandom.txt");
  ofstream stlsort("StlSort.txt");
  double time_elapsed;

  for (int size : {800, 1600, 3200, 6400, 12800, 25600, 51200}) {
    int l = 0;
    vector<int> reverseSorteda(size);
    iota(reverseSorteda.begin(), reverseSorteda.end(), 1);
    reverse(reverseSorteda.begin(), reverseSorteda.end());
    vector<int> reverseSortedb = reverseSorteda;
    vector<int> reverseSortedc = reverseSorteda;

    // will generate random numbers and put it in array of size =size
    vector<int> randomArrA(size);
    generate(randomArrA.begin(), randomArrA.end(), []() { return rand(); });
    vector<int> randomArrB = randomArrA;
    vector<int> randomArrC = randomArrA;

    // Random pivot quick sort
    // Reverse Sorted
    time_elapsed = timeMyFunction(qSort, reverseSorteda, 0, size, true);
    printDetails(q_sort_rand, "", "Worst", time_elapsed, size);
    printDetails(cout, "QuickSortRand ", "Worst", time_elapsed, size);
    assert(is_sorted(reverseSorteda.begin(), reverseSorteda.end()));

    // Random
    time_elapsed = timeMyFunction(qSort, randomArrA, 0, size, true);
    printDetails(q_sort_rand, "", "Random", time_elapsed, size);
    printDetails(cout, "QuickSortRand ", "Random", time_elapsed, size);
    assert(is_sorted(randomArrA.begin(), randomArrA.end()));

    // Sorted
    time_elapsed = timeMyFunction(qSort, randomArrA, 0, size, true);
    printDetails(q_sort_rand, "", "Sorted", time_elapsed, size);
    printDetails(cout, "QuickSortRand ", "Sorted", time_elapsed, size);
    assert(is_sorted(randomArrA.begin(), randomArrA.end()));

    // pivot is first elem quick sort
    // Reverse Sorted
    time_elapsed = timeMyFunction(qSort, reverseSortedb, 0, size, false);
    printDetails(q_sort, "", "Worst", time_elapsed, size);
    printDetails(cout, "QuickSort ", "Worst", time_elapsed, size);
    assert(is_sorted(reverseSortedb.begin(), reverseSortedb.end()));

    // Random
    time_elapsed = timeMyFunction(qSort, randomArrB, 0, size, false);
    printDetails(q_sort, "", "Random", time_elapsed, size);
    printDetails(cout, "QuickSort ", "Random", time_elapsed, size);
    assert(is_sorted(randomArrB.begin(), randomArrB.end()));

    // Sorted
    time_elapsed = timeMyFunction(qSort, randomArrB, 0, size, false);
    printDetails(q_sort, "", "Sorted", time_elapsed, size);
    printDetails(cout, "QuickSort ", "Sorted", time_elapsed, size);

    // Built in Sort
    // Reverse Sorted
    time_elapsed = timeMyFunction(stl_sort, reverseSortedc);
    printDetails(stlsort, "", "Worst", time_elapsed, size);
    printDetails(cout, "StlSort ", "Worst", time_elapsed, size);
    assert(is_sorted(reverseSortedc.begin(), reverseSortedc.end()));

    // Random
    time_elapsed = timeMyFunction(stl_sort, randomArrC);
    printDetails(stlsort, "", "Random", time_elapsed, size);
    printDetails(cout, "StlSort ", "Random", time_elapsed, size);
    assert(is_sorted(randomArrC.begin(), randomArrC.end()));

    // Sorted
    time_elapsed = timeMyFunction(stl_sort, randomArrC);
    printDetails(stlsort, "", "Sorted", time_elapsed, size);
    printDetails(cout, "StlSort ", "Sorted", time_elapsed, size);
    assert(is_sorted(randomArrC.begin(), randomArrC.end()));

    cout << endl << endl;
  }
}
