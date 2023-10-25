#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

int main() {
  const int kNumsAfterComma = 6;
  int length;
  std::cin >> length;
  std::vector<double> volume(length);
  std::vector<double> log_volume(length + 1);
  for (int i = 0; i < length; ++i) {
    std::cin >> volume[i];
    volume[i] = std::log2(volume[i]);
  }
  log_volume[0] = 0;
  for (int i = 1; i <= length; ++i) {
    log_volume[i] = (log_volume[i - 1] + volume[i - 1]);
  }
  int questions;
  std::cin >> questions;
  int left;
  int right;
  for (int i = 0; i < questions; ++i) {
    std::cin >> left >> right;
    std::cout << std::fixed << std::setprecision(kNumsAfterComma)
              << std::pow(2, (log_volume[right + 1] - log_volume[left]) /
                                     (right - left + 1))
              << "\n";
  }
  return 0;
}
