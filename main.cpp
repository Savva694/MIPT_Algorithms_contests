#include <iostream>
#include <vector>

int main() {
  size_t count;
  int sum_weight;
  std::cin >> count;
  std::cin >> sum_weight;
  std::vector<int> weights(count);
  std::vector<int> values(count);

  for (size_t i = 0; i < count; ++i) {
    std::cin >> weights[i];
  }
  for (size_t i = 0; i < count; ++i) {
    std::cin >> values[i];
  }

  std::vector<std::vector<int>> max_sum_of_values(count + 1);
  std::vector<std::vector<bool>> last_move(count + 1);

  for (size_t i = 0; i <= count; ++i) {
    max_sum_of_values[i].resize(sum_weight + 1);
    last_move[i].resize(sum_weight + 1);
    for (int weight = 0; weight <= sum_weight; ++weight) {
      if (i == 0 || weight == 0) {
        max_sum_of_values[i][weight] = 0;
        continue;
      }
      if (weights[i - 1] <= weight &&
          max_sum_of_values[i - 1][weight] <
              max_sum_of_values[i - 1][weight - weights[i - 1]] +
                  values[i - 1]) {
        max_sum_of_values[i][weight] =
            max_sum_of_values[i - 1][weight - weights[i - 1]] + values[i - 1];
        last_move[i][weight] = true;
      } else {
        max_sum_of_values[i][weight] = max_sum_of_values[i - 1][weight];
        last_move[i][weight] = false;
      }
    }
  }

  int weight_now = sum_weight;
  for (size_t i = count; i > 0; --i) {
    if (weight_now >= 0 && last_move[i][weight_now]) {
      std::cout << i << "\n";
      weight_now -= weights[i - 1];
    }
  }
}