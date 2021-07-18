#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

double fractionalKnapsack(vector<pair<int, int>> &w_v, int MAX_WT) {
  sort(w_v.begin(), w_v.end(), [](auto x, auto y) {
    return (((double)(x.first)) / x.second > ((double)y.first) / y.second);
  });

  int cur_weight = 0;
  double final_value = 0;
  for (pair<int, int> x : w_v) {
    if (cur_weight + x.second <= MAX_WT) {
      cur_weight += x.second;
      final_value += (x.first);
    } else {
      int remaining_wt = MAX_WT - cur_weight;
      final_value += (((double)(remaining_wt * x.first)) / x.second);
      break;
    }
  }
  return final_value;
}

int main() {
  int MAX_WT = 50;
  vector<int> weights = {10, 20, 30};
  vector<int> values = {60, 100, 120};
  vector<pair<int, int>> w_v; // first is value and ssecond in weight
  transform(values.begin(), values.end(), weights.begin(), back_inserter(w_v),
            [](auto x, auto y) { return make_pair(x, y); });
  auto ans = fractionalKnapsack(w_v, MAX_WT);
  cout << ans << endl;
}
