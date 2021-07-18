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

void bubble_sort(vector<int> &arr) {
  int n = arr.size();
  int flag = 1;
  int pos = n - 2;
  int pos_tmp = pos;
  while (flag) {
    flag = 0;
    for (int i = 0; i <= pos_tmp; i++) {
      if (arr[i] > arr[i + 1]) {
        swap(arr[i], arr[i + 1]);
        pos = i;
        flag = 1;
      }
    }
    pos_tmp = pos;
  }
}
// void bubble_sort(vector<int> &vec) {
//   int swapped = 1;
//   int last = vec.size() - 1;
//   while (swapped) {
//     swapped = 0;
//     for (int i = 1; i <= last; i++) {
//       if (vec[i] < vec[i - 1]) {
//         swap(vec[i], vec[i - 1]);
//         swapped = 1;
//         last = i;
//       }
//     }
//     // last--;
//   }
// }

void straight_insertion_sort(vector<int> &vec) {
  size_t j;
  size_t last = vec.size();
  for (size_t i = 1; i < last; i++) {
    j = i;
    while (j > 0 && vec[j] < vec[j - 1]) {
      swap(vec[j], vec[j - 1]);
      j--;
    }
  }
}
//
void straight_selection_sort(vector<int> &vec) {
  int last = vec.size() - 1;
  vector<int>::iterator min_iterator;
  for (int i = 0; i < last; i++) {
    min_iterator = min_element(vec.begin() + i, vec.end());
    swap(vec[i], *min_iterator);
  }
}

int main() {
  srand(time(0));
  ofstream bubble("Bubble.txt");
  ofstream insertion("Insertion.txt");
  ofstream selection("Selection.txt");
  double time_elapsed;
  for (int size : {25, 50, 100, 200, 400, 800, 1600, 3200, 6400}) {
    // a will be reverse sorted array
    vector<int> reverseSorteda(size);
    iota(reverseSorteda.begin(), reverseSorteda.end(), 1);
    reverse(reverseSorteda.begin(), reverseSorteda.end());
    // copy(a.begin(), a.end(), ostream_iterator<int>(cout, " "));
    vector<int> reverseSortedb = reverseSorteda;
    vector<int> reverseSortedc = reverseSorteda;

    // will generate random numbers and put it in array of size =size
    vector<int> randomArrA(size);
    generate(randomArrA.begin(), randomArrA.end(), []() { return rand(); });
    vector<int> randomArrB = randomArrA;
    vector<int> randomArrC = randomArrA;

    //
    //
    //
    //
    //
    // worst cases
    time_elapsed = timeMyFunction(straight_selection_sort, reverseSorteda);
    cout << "Straight Selection Sort Worst for  "
         << "size " << size << ": " << fixed << setprecision(30) << time_elapsed
         << endl;
    selection << "Worst:" << size << ":" << fixed << setprecision(30)
              << time_elapsed << endl;

    time_elapsed = timeMyFunction(straight_insertion_sort, reverseSortedb);
    cout << "Straight Insertion Sort Worst for  "
         << "size " << size << ": " << fixed << setprecision(30) << time_elapsed
         << endl;
    insertion << "Worst:" << size << ":" << fixed << setprecision(30)
              << time_elapsed << endl;
    time_elapsed = timeMyFunction(bubble_sort, reverseSortedc);
    cout << "Bubble Sort Worst for  "
         << "size " << size << ": " << fixed << setprecision(30) << time_elapsed
         << endl;
    bubble << "Worst:" << size << ":" << fixed << setprecision(30)
           << time_elapsed << endl;
    assert(is_sorted(reverseSorteda.begin(), reverseSorteda.end()));
    assert(is_sorted(reverseSortedb.begin(), reverseSortedb.end()));
    assert(is_sorted(reverseSortedc.begin(), reverseSortedc.end()));

    //
    //
    //
    //
    //
    //
    // Random cases
    time_elapsed = timeMyFunction(straight_selection_sort, randomArrA);
    cout << "Straight Selection Sort Random Case for  "
         << "size " << size << ": " << fixed << setprecision(30) << time_elapsed
         << endl;
    selection << "Random:" << size << ":" << fixed << setprecision(30)
              << time_elapsed << endl;
    time_elapsed = timeMyFunction(straight_insertion_sort, randomArrB);
    cout << "Straight Insertion Sort Random Case for  "
         << "size " << size << ": " << fixed << setprecision(30) << time_elapsed
         << endl;
    insertion << "Random:" << size << ":" << fixed << setprecision(30)
              << time_elapsed << endl;
    time_elapsed = timeMyFunction(bubble_sort, randomArrC);
    cout << "Bubble Sort Random Case for  "
         << "size " << size << ": " << fixed << setprecision(30) << time_elapsed
         << endl;
    bubble << "Random:" << size << ":" << fixed << setprecision(30)
           << time_elapsed << endl;
    assert(is_sorted(randomArrA.begin(), randomArrA.end()));
    assert(is_sorted(randomArrB.begin(), randomArrB.end()));
    assert(is_sorted(randomArrC.begin(), randomArrC.end()));
    //
    //
    //
    // Best case
    // I'll just use the arrays from last sort, as they'll be sorted and  hence
    // it should be best case
    time_elapsed = timeMyFunction(straight_selection_sort, randomArrA);
    cout << "Straight Selection Sort Best Case for  "
         << "size " << size << ": " << fixed << setprecision(30) << time_elapsed
         << endl;
    selection << "Best:" << size << ":" << fixed << setprecision(30)
              << time_elapsed << endl;
    time_elapsed = timeMyFunction(straight_insertion_sort, randomArrB);
    cout << "Straight Insertion Sort Best Case for  "
         << "size " << size << ": " << fixed << setprecision(30) << time_elapsed
         << endl;
    insertion << "Best:" << size << ":" << fixed << setprecision(30)
              << time_elapsed << endl;
    time_elapsed = timeMyFunction(bubble_sort, randomArrC);
    cout << "Bubble Sort Best Case for  "
         << "size " << size << ": " << fixed << setprecision(30) << time_elapsed
         << endl;
    cout << endl;
    bubble << "Best:" << size << ":" << fixed << setprecision(30)
           << time_elapsed << endl;
    assert(is_sorted(randomArrA.begin(), randomArrA.end()));
    assert(is_sorted(randomArrB.begin(), randomArrB.end()));
    assert(is_sorted(randomArrC.begin(), randomArrC.end()));
    cout << endl;
    cout << endl;
  }
}
