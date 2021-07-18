#include <algorithm>
#include <cassert>
#include <iostream>
#include <list>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
  list<int> a = {1, 2, 3};
  auto it = std::next(a.begin(), -2);
  assert(it == a.end());
}
