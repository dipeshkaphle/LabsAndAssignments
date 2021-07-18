#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

size_t fibonacci(int n) {
  // makes sure the number is positive
  assert(n >= 1);

  if (n <= 2)
    return n - 1;
  vector<size_t> fibs(n, 0);
  fibs[1] = 1;
  for (int i = 2; i < n; i++)
    fibs[i] = fibs[i - 1] + fibs[i - 2];
  return fibs[n - 1];
}

int main() {
  for (int i = 1; i <= 46; i += 5) {

    auto start_time = std::chrono::steady_clock::now();
    size_t fibonacci_answer = fibonacci(i);
    auto end_time = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_time =
        std::chrono::duration_cast<std::chrono::duration<double>>(end_time -
                                                                  start_time);
    cout << i << ':' << fibonacci_answer << ':' << elapsed_time.count() << '\n';
  }
}
