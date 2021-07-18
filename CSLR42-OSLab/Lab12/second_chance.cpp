#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

bool is_present(int x, vector<int> &arr, vector<bool> &bit) {
  for (int i = 0; i < arr.size(); i++) {
    if (arr[i] == x) {
      bit[i] = true;
      return true;
    }
  }
  return false;
}
int replace(int x, vector<int> &arr, vector<bool> &bits, int p) {
  while (true) {
    if (!bits[p]) {
      bits[p] = true;
      arr[p] = x;
      return (p + 1) % arr.size();
    }
    bits[p] = false;
    (p += 1) %= arr.size();
  }
}

void print_state(vector<int> &arr, vector<bool> &bits) {
  for (int i = 0; i < arr.size(); i++) {
    if (arr[i] == -1)
      break;
    cout << arr[i] << ' ' << bits[i] << '\n';
  }
}

void second_chance(const vector<int> &inp, int frames) {
  vector<int> arr(frames, -1);
  vector<bool> bit(frames, false);
  int ptr = 0;
  int page_faults = 0;
  int iter = 0;
  cout << "Iteration " << iter++ << '\n';
  print_state(arr, bit);
  cout << '\n';
  for (auto c : inp) {
    if (!is_present(c, arr, bit)) {
      ptr = replace(c, arr, bit, ptr);
      page_faults++;
    }
    cout << "Iteration " << iter++ << '\n';
    print_state(arr, bit);
    cout << '\n';
  }
  cout << "Total page faults are " << page_faults << "\n";
}

int main() {
  second_chance({}, 4);
  // second_chance({1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5}, 3);
  // second_chance({1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5}, 4);
}
