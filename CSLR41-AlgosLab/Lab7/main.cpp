#include <algorithm>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

using namespace std;

#define INF INT32_MAX

void solve_rec(vector<vector<int>> &m, vector<vector<int>> &s,
               vector<int> &mats, int i, int j) {
  if (m[i][j] != INF) {
    return;
  }
  for (int k = i; k < j; k++) {
    solve_rec(m, s, mats, i, k);
    solve_rec(m, s, mats, k + 1, j);
    if (m[i][j] > m[i][k] + m[k + 1][j] + mats[i - 1] * mats[k] * mats[j]) {
      s[i][j] = k;
      m[i][j] = m[i][k] + m[k + 1][j] + mats[i - 1] * mats[k] * mats[j];
    }
  }
}

void solve_non_rec(vector<vector<int>> &m, vector<vector<int>> &s,
                   vector<int> &mats, int n) {
  for (int len = 2; len <= n; len++) { // len is length of chain
    for (int i = 1; i <= n - len + 1;
         i++) { // take all possible l length matrix sets
      int j = i + len - 1;
      for (int k = i; k <= j - 1; k++) {
        int cost = m[i][k] + m[k + 1][j] + mats[i - 1] * mats[k] * mats[j];
        if (cost < m[i][j]) {
          m[i][j] = cost;
          s[i][j] = k;
        }
      }
    }
  }
}

void print_parens(vector<vector<int>> &s, int i, int j) {
  if (i == j) {
    std::cout << "A" << i;
  } else {
    std::cout << "(";
    print_parens(s, i, s[i][j]);
    print_parens(s, s[i][j] + 1, j);
    std::cout << ")";
  }
}

int main() {
  // for (auto mats : vector<vector<int>>{
  //          {77, 43, 26}, {46, 32, 55, 53, 35}, {62, 47, 79, 29, 81, 23, 70}})
  //          {
  for (auto mats : vector<vector<int>>{
           {62, 47, 79, 45, 65, 65, 43, 45, 78, 65, 98, 76, 78, 23, 46, 75}}) {
    // vector<int> mats{10, 20, 30, 40, 30};
    for (auto x : mats) {
      std::cout << x << " ";
    }
    std::cout << std::endl;
    int n = mats.size() - 1;
    vector<vector<int>> m(mats.size(), vector<int>(mats.size(), INF));
    vector<vector<int>> s(mats.size(), vector<int>(mats.size(), INF));
    for (int i = 0; i <= n; i++) {
      m[i][i] = 0;
    }
    solve_non_rec(m, s, mats, n);
    std::cout << m[1].back() << std::endl;
    print_parens(s, 1, n);
    std::cout << std::endl;
  }
}
