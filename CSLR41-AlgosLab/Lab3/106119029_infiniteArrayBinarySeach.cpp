#include <algorithm>
#include <chrono>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int BSearch(vector<int> &vec, int key) {
  int l = 0;
  int r = 1;
  // we'll find the range here, within l to r the key will have to be searched
  // again
  while (true) {
    try {
      if (vec.at(r) <= key) {
        l = r;
        r = 2 * r;
      } else {
        break;
      }
    } catch (std::exception &e) {
      break;
    }
  }

  int m;
  // normal bseearch on the range we found
  while (l < r) {
    try {
      m = (l + r) / 2;
      if (vec.at(m) == key) {
        return m;
      } else if (vec[m] < key) {
        l = m + 1;
      } else {
        r = m;
      }
    } catch (std::exception &e) {
      r = m;
    }
  }
  return -1;
}

int main() {
  srand(0);
  vector<int> vec;
  ofstream random_case("RandomCase.txt");
  ofstream worst_case("WorstCase.txt");
  ofstream best_case("BestCase.txt");
  chrono::duration<double> elapsed_time;
  vector<int> sizes(10);
  sizes[0] = 16000;
  for (int i = 1; i < 10; i++)
    sizes[i] = 2 * sizes[i - 1];
  for (int size : sizes) {
    vec.resize(size, 0);
    iota(vec.begin(), vec.end(), 1);
    // Worst Case would be something at the absoulte end of list
    // since our array is 1...size, the size will take worst time
    int key = size;
    auto start_time = chrono::steady_clock::now();
    BSearch(vec, key);
    auto end_time = chrono::steady_clock::now();

    // gets the elapsed time
    elapsed_time =
        chrono::duration_cast<chrono::duration<double>>(end_time - start_time);
    cout << "WORST FOR SIZE " << size << " : " << fixed << setprecision(30)
         << elapsed_time.count() << '\n';
    worst_case << size << ':' << fixed << setprecision(30)
               << elapsed_time.count() << '\n';

    // random case
    // uses rand()
    key = vec[rand() % size];
    start_time = chrono::steady_clock::now();
    BSearch(vec, key);
    end_time = chrono::steady_clock::now();

    // gets the elapsed time
    elapsed_time =
        chrono::duration_cast<chrono::duration<double>>(end_time - start_time);
    cout << "RANDOM FOR SIZE " << size << " : " << fixed << setprecision(30)
         << elapsed_time.count() << '\n';
    random_case << size << ':' << fixed << setprecision(30)
                << elapsed_time.count() << '\n';

    // best case is index 0
    key = vec[0];
    start_time = chrono::steady_clock::now();
    BSearch(vec, key);
    end_time = chrono::steady_clock::now();

    // gets the elapsed time
    elapsed_time =
        chrono::duration_cast<chrono::duration<double>>(end_time - start_time);
    cout << "BEST FOR SIZE " << size << " : " << fixed << setprecision(30)
         << elapsed_time.count() << '\n';
    best_case << size << ':' << fixed << setprecision(30)
              << elapsed_time.count() << '\n';
  }
}
