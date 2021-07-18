#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using std::cout;
using std::endl;

template <typename Func, typename... Args>
double timeMyFunction(Func func, Args... args) {
  auto start_time = std::chrono::steady_clock::now();
  func(args...);
  auto end_time = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_time =
      std::chrono::duration_cast<std::chrono::duration<double>>(end_time -
                                                                start_time);
  return elapsed_time.count();
}

void linear_search(std::vector<int> &vec, int key) {
  for (size_t i = 0; i < vec.size(); i++) {
    if (key == vec[i]) {
      break;
    }
  }
}

int main() {
  srand(time(NULL));
  // will be {10,100,200,400,800,1600,3200,6400,12800,25600}
  std::vector<int> size_array(10, 0);
  size_array[0] = 10;
  size_array[1] = 100;
  for (int i = 2; i < 10; i++)
    size_array[i] = 2 * size_array[i - 1];
  size_array[0] = 10;
  double elapsed_time;

  std::vector<int> vec;
  for (auto &&size : size_array) {
    vec.assign(size, 0);
    std::generate(vec.begin(), vec.end(), [&]() { return rand() % size; });

    int val_to_search = vec[rand() % size];
    elapsed_time = timeMyFunction(linear_search, vec, val_to_search);
    printf("FoundCase:%d:%.10lf\n", size, elapsed_time);

    val_to_search = size + 100;
    elapsed_time = timeMyFunction(linear_search, vec, val_to_search);
    printf("NotfoundCase:%d:%.10lf\n", size, elapsed_time);
  }
}
