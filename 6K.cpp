#include <iostream>
#include <vector>

std::vector<size_t> BackpackProblem(int sum_weight, std::vector<int>& weights,
                                    std::vector<int>& values,
                                    std::vector<std::vector<bool>>& last_move) {
  size_t count = weights.size();
  std::vector<std::vector<int>> max_sum_of_values(count + 1);

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
  std::vector<size_t> elements;

  for (size_t i = count; i > 0; --i) {
    if (weight_now >= 0 && last_move[i][weight_now]) {
      elements.push_back(i);
      weight_now -= weights[i - 1];
    }
  }

  return elements;
}

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

  std::vector<std::vector<bool>> last_move(count + 1);
  std::vector<size_t> elements =
      BackpackProblem(sum_weight, weights, values, last_move);

  for (size_t element : elements) {
    std::cout << element << "\n";
  }
}
