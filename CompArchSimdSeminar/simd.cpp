#include <array>
#include <iostream>
#include <numeric>

constexpr int N = 32;
template <size_t N>
void saxpy(std::array<float, N> &X, std::array<float, N> &Y, float a) {
  for (int i = 0; i < N; i++) {
    Y[i] = a * X[i] + Y[i];
  }
}
int main() {
  std::array<float, N> X;
  std::array<float, N> Y;
  // fills a and b with 1..N
  std::iota(X.begin(), X.end(), 1);
  std::iota(Y.begin(), Y.end(), 1);
  // will use simd intrinsics
  saxpy(X, Y, 10.0);
  for (int i = 0; i < N; i++) {
    printf("%f ", Y[i]);
  }
  printf("\n");
}
