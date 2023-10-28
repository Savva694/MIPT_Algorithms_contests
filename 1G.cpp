#include <cmath>
#include <iostream>
#include <vector>

void LongLongLSD(std::vector<unsigned long long>& numbers, int length) {
  const int kNumberSystem = 10;
  int max_length = 0;
  for (int i = 0; i < length; ++i) {
    max_length = std::max(
        max_length,
        static_cast<int>(std::log(numbers[i]) / std::log(kNumberSystem)));
  }
  std::vector<unsigned long long> numbers_copy(length);
  std::vector<int> count_of_numbers(kNumberSystem);
  unsigned long long divider = 1;
  for (int i = 1; i <= max_length + 2; ++i) {
    divider *= kNumberSystem;
    for (int j = 0; j < kNumberSystem; ++j) {
      count_of_numbers[j] = 0;
    }
    for (int j = 0; j < length; ++j) {
      ++count_of_numbers[(numbers[j] % divider) / (divider / kNumberSystem)];
    }
    for (int j = 1; j < kNumberSystem; ++j) {
      count_of_numbers[j] += count_of_numbers[j - 1];
    }

    for (int j = length - 1; j >= 0; --j) {
      numbers_copy[count_of_numbers[(numbers[j] % divider) /
                                    (divider / kNumberSystem)] -
                   1] = numbers[j];
      --count_of_numbers[(numbers[j] % divider) / (divider / kNumberSystem)];
    }
    for (int j = 0; j < length; ++j) {
      numbers[j] = numbers_copy[j];
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int length;
  std::cin >> length;
  std::vector<unsigned long long> numbers(length);
  for (int i = 0; i < length; ++i) {
    std::cin >> numbers[i];
  }
  LongLongLSD(numbers, length);
  for (int i = 0; i < length; ++i) {
    std::cout << numbers[i] << "\n";
  }
}
