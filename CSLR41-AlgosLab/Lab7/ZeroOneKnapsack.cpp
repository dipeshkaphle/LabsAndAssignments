#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

void zeroOneKnapsack(const vector<int> &weights, const vector<int> &values,
                     vector<vector<int>> &dp) {
  int MAX_WT = dp[0].size() - 1;
  int ind = 0;
  for (int &x : dp[0]) {
    if (weights[0] > ind) {
      x = 0;
    } else {
      x = weights[0];
    }
    ind++;
  }
  for (size_t i = 1; i < weights.size(); i++) {
    for (int j = 0; j <= MAX_WT; j++) {
      if (weights[i] > j) {
        dp[i][j] = dp[i - 1][j];
      } else {
        dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weights[i]] + values[i]);
      }
    }
  }
}

int main() {
  vector<int> weights{10, 20, 30};
  vector<int> values{60, 100, 120};
  int MAX_WT = 50;
  vector<vector<int>> dp(weights.size(), vector<int>(MAX_WT + 1, INT32_MIN));
  zeroOneKnapsack(weights, values, dp);
  cout << dp.back().back() << endl;
}
