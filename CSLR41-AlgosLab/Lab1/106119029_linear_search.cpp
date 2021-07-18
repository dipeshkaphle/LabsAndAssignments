#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

int main() {
  srand(time(NULL));
  // will be {10,100,200,400,800,1600,3200,6400,12800,25600}
  std::vector<int> size_array(10, 0);
  size_array[0] = 10;
  size_array[1] = 100;
  for (int i = 2; i < 10; i++)
    size_array[i] = 2 * size_array[i - 1];
  size_array[0] = 10;

  std::vector<int> vec;
  for (auto &&size : size_array) {
    vec.assign(size, 0);
    std::generate(vec.begin(), vec.end(), [&]() { return rand() % size; });

    int val_to_search = vec[rand() % size];

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; i++) {
      if (val_to_search == vec[i]) {
        break;
      }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed =
        std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    printf("FoundCase:%d:%.10lf\n", size, elapsed.count());

    val_to_search = size + 100;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; i++) {
      if (val_to_search == vec[i]) {
        break;
      }
    }
    end = std::chrono::high_resolution_clock::now();
    elapsed =
        std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    printf("NotfoundCase:%d:%.10lf\n", size, elapsed.count());
  }
}
