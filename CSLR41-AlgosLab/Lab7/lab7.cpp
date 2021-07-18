#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

template <typename Func, typename... Args>
double timeMyFunction(Func func, Args &&...args) {
  auto start_time = std::chrono::steady_clock::now();
  func(forward<Args>(args)...);
  auto end_time = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_time =
      std::chrono::duration_cast<std::chrono::duration<double>>(end_time -
                                                                start_time);
  return elapsed_time.count();
}

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

void fractionalKnapsack(vector<pair<int, int>> &v_w, int MAX_WT, double *ans) {
  sort(v_w.begin(), v_w.end(), [](auto x, auto y) {
    return (((double)(x.first)) / x.second > ((double)y.first) / y.second);
  });

  int cur_weight = 0;
  double final_value = 0;
  for (pair<int, int> x : v_w) {
    if (cur_weight + x.second <= MAX_WT) {
      cur_weight += x.second;
      final_value += (x.first);
    } else {
      int remaining_wt = MAX_WT - cur_weight;
      final_value += (((double)(remaining_wt * x.first)) / x.second);
      break;
    }
  }
  *ans = final_value;
}

int main(int argc, char **argv) {
  ofstream zeroOne("ZeroOne.txt");
  ofstream frac("Fractional.txt");
  srand(time(0));
  int size_opt;
  if (argc == 2) {
    size_opt = atoi(argv[1]);
  } else {
    size_opt = 0;
  }
  double time_elapsed;
  for (int size :
       {10,  20,  30,  40,  50,  60,  70,  80,  90,  100, 110, 120, 130,
        140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250}) {
    int MAX_WT;
    if (size_opt == 0)
      MAX_WT = size;
    else if (size_opt == 1)
      MAX_WT = size * size;
    else if (size_opt == 2)
      MAX_WT = log2(size);
    else
      MAX_WT = size * (rand() % size);
    double fractional_ans;
    vector<int> values(size);
    vector<int> weights(size);
    // for fractional knapsack
    vector<pair<int, int>> v_w;
    // for zeroOneKnapsack
    vector<vector<int>> dp(weights.size(), vector<int>(MAX_WT + 1, INT32_MIN));
    generate(values.begin(), values.end(), []() { return rand() % 1000; });
    generate(weights.begin(), weights.end(),
             [size]() { return rand() % size; });
    transform(values.begin(), values.end(), weights.begin(), back_inserter(v_w),
              [](auto x, auto y) { return make_pair(x, y); });
    time_elapsed =
        timeMyFunction(zeroOneKnapsack, ref(weights), ref(values), ref(dp));
    cout << "DP:" << size << "," << MAX_WT << ":" << fixed << setprecision(20)
         << time_elapsed << ":";
    cout << dp.back().back() << endl;
    zeroOne << size << ":" << MAX_WT << ":" << fixed << setprecision(20)
            << time_elapsed << endl;
    time_elapsed =
        timeMyFunction(fractionalKnapsack, ref(v_w), MAX_WT, &fractional_ans);
    cout << "Fractional:" << size << "," << MAX_WT << ":" << fixed
         << setprecision(20) << time_elapsed << ":";
    cout << fractional_ans << endl;
    frac << size << ":" << MAX_WT << ":" << fixed << setprecision(20)
         << time_elapsed << endl;
    cout << endl << endl;
  }
}
