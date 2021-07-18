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
double timeMyFunction(Func func, Args &...args) {
  auto start_time = std::chrono::steady_clock::now();
  func(args...);
  auto end_time = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_time =
      std::chrono::duration_cast<std::chrono::duration<double>>(end_time -
                                                                start_time);
  return elapsed_time.count();
}

double time_stl_sort(vector<int> &vec) {
  auto start_time = std::chrono::steady_clock::now();
  std::sort(vec.begin(), vec.end());
  auto end_time = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_time =
      std::chrono::duration_cast<std::chrono::duration<double>>(end_time -
                                                                start_time);
  return elapsed_time.count();
}

bool heapify_at_index(vector<int> &hp, int index, int size) {
  int br1 = 2 * index + 1;
  int br2 = br1 + 1;
  bool swapped = false;
  if (br1 < size && br2 < size) {
    int i = min(hp[br1], hp[br2]) == hp[br1] ? br1 : br2;
    if (hp[i] < hp[index]) {
      std::swap(hp[i], hp[index]);
      heapify_at_index(hp, i, size);
      swapped = true;
    }
  } else if (br1 < size && hp[br1] < hp[index]) {
    std::swap(hp[br1], hp[index]);
    heapify_at_index(hp, br1, size);
    swapped = true;
  }
  return swapped;
}

inline void extract_min_to_back(vector<int> &vec, int size) {
  std::swap(vec[size - 1], vec[0]);
  heapify_at_index(vec, 0, size - 1);
}

void heapSort(vector<int> &vec) {
  for (int i = vec.size() / 2; i >= 0; i--) {
    heapify_at_index(vec, i, vec.size());
  }
  for (int i = vec.size(); i >= 1; i--) {
    extract_min_to_back(vec, i);
  }
  reverse(vec.begin(), vec.end());
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
  srand(time(0));
  ofstream merge_sort("MergeSort.txt");
  ofstream heap_sort("HeapSort.txt");
  ofstream stl_sort("StlSort.txt");
  double time_elapsed;
  for (int size : {800, 1600, 3200, 6400, 12800, 25600, 51200, 102400}) {
    int l = 0;
    vector<int> reverseSorteda(size);
    iota(reverseSorteda.begin(), reverseSorteda.end(), 1);
    reverse(reverseSorteda.begin(), reverseSorteda.end());

    vector<int> reverseSorteda2 = reverseSorteda;
    vector<int> reverseSorteda3 = reverseSorteda;

    // will generate random numbers and put it in array of size =size
    vector<int> randomArrA(size);
    generate(randomArrA.begin(), randomArrA.end(), []() { return rand(); });
    vector<int> randomArrA2 = randomArrA;
    vector<int> randomArrA3 = randomArrA;

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

    time_elapsed = timeMyFunction(heapSort, reverseSorteda2);
    cout << "Heap Sort Worst for  "
         << "size " << size << ": " << fixed << setprecision(30) << time_elapsed
         << endl;
    heap_sort << "Worst:" << size << ":" << fixed << setprecision(30)
              << time_elapsed << endl;

    assert(is_sorted(reverseSorteda2.begin(), reverseSorteda2.end()));

    time_elapsed = time_stl_sort(reverseSorteda3);
    cout << "Built in Sort Worst for  "
         << "size " << size << ": " << fixed << setprecision(30) << time_elapsed
         << endl;
    stl_sort << "Worst:" << size << ":" << fixed << setprecision(30)
             << time_elapsed << endl;

    assert(is_sorted(reverseSorteda3.begin(), reverseSorteda3.end()));

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

    time_elapsed = timeMyFunction(heapSort, randomArrA2);
    cout << "Heap Sort Random for  "
         << "size " << size << ": " << fixed << setprecision(30) << time_elapsed
         << endl;
    heap_sort << "Random:" << size << ":" << fixed << setprecision(30)
              << time_elapsed << endl;

    assert(is_sorted(randomArrA2.begin(), randomArrA2.end()));

    time_elapsed = time_stl_sort(randomArrA3);
    cout << "Built in Sort Random for  "
         << "size " << size << ": " << fixed << setprecision(30) << time_elapsed
         << endl;
    stl_sort << "Random:" << size << ":" << fixed << setprecision(30)
             << time_elapsed << endl;

    assert(is_sorted(randomArrA3.begin(), randomArrA3.end()));

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

    time_elapsed = timeMyFunction(heapSort, randomArrA2);
    cout << "Heap Sort Best for  "
         << "size " << size << ": " << fixed << setprecision(30) << time_elapsed
         << endl;
    heap_sort << "Best:" << size << ":" << fixed << setprecision(30)
              << time_elapsed << endl;

    assert(is_sorted(randomArrA2.begin(), randomArrA2.end()));

    time_elapsed = time_stl_sort(randomArrA3);
    cout << "Built in Sort Best for  "
         << "size " << size << ": " << fixed << setprecision(30) << time_elapsed
         << endl;
    stl_sort << "Best:" << size << ":" << fixed << setprecision(30)
             << time_elapsed << endl;

    assert(is_sorted(randomArrA3.begin(), randomArrA3.end()));
    cout << endl;
    cout << endl;
  }
}
