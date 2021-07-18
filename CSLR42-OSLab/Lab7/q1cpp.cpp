#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int sum(const vector<int> &vec) {
  return accumulate(vec.begin(), vec.end(), 0);
}
int maxi(const vector<int> &vec) {
  return *std::max_element(vec.begin(), vec.end());
}

int main() {
  vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  future<int> sum_res = async(launch::async, sum, ref(vec));
  future<int> max_res = async(launch::async, maxi, ref(vec));
  future<int> max_res1 = async(launch::async, maxi, ref(vec));
  future<int> max_res2 = async(launch::async, maxi, ref(vec));
  // sum_res.wait();
  // max_res.wait();
  // max_res1.wait();
  // max_res2.wait();
  std::cout << sum_res.get() << " | " << max_res1.get() << max_res.get()
            << max_res2.get() << std::endl;
}
