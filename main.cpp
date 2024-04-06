#include <iostream>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  size_t height;
  size_t planes;
  std::cin >> height;
  std::cin >> planes;
  if (planes == 0) {
    if (height == 1) {
      std::cout << 0;
    } else {
      std::cout << -1;
    }
    return 0;
  }
  int int_height = static_cast<int>(height);
  std::vector<int> previous(planes + 1, 1);
  std::vector<int> now(planes + 1);
  for (size_t i = 1; i <= height; ++i) {
    now[0] = 1;
    for (size_t j = 1; j <= planes; ++j) {
      now[j] = previous[j] + previous[j - 1];
    }
    if (now[planes] >= int_height) {
      std::cout << i;
      return 0;
    }
    previous = now;
  }
}
