#include <iostream>
#include <string>
#include <vector>

void LongLongLSD(std::vector<std::pair<std::string, std::string>>& numbers,
                 int length, int max_length) {
  int now_length;
  const int kNumberSystem = 10;
  const int kNullInChar = 48;
  for (int i = 0; i < length; ++i) {
    now_length = static_cast<int>(numbers[i].first.length());
    for (int j = 0; j < max_length - now_length; ++j) {
      numbers[i].first = "0" + numbers[i].first;
    }
  }
  std::vector<std::pair<std::string, std::string>> numbers_copy(length);
  std::vector<int> count(kNumberSystem);
  int number;
  for (int i = max_length - 1; i >= 0; --i) {
    for (int j = 0; j < kNumberSystem; ++j) {
      count[j] = 0;
    }
    for (int j = 0; j < length; ++j) {
      ++count[static_cast<int>(numbers[j].first[i] - kNullInChar)];
    }
    for (int j = 1; j < kNumberSystem; ++j) {
      count[j] += count[j - 1];
    }

    for (int j = length - 1; j >= 0; --j) {
      number = static_cast<int>(numbers[j].first[i] - kNullInChar);
      numbers_copy[count[number] - 1] = numbers[j];
      --count[number];
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
  std::vector<std::pair<std::string, std::string>> numbers(length);
  int max_length = 0;
  int now_length;
  for (int i = 0; i < length; ++i) {
    std::cin >> numbers[i].second;
    numbers[i].first = numbers[i].second;
    now_length = static_cast<int>(numbers[i].first.length());
    max_length = std::max(max_length, now_length);
  }
  LongLongLSD(numbers, length, max_length);
  for (int i = 0; i < length; ++i) {
    std::cout << numbers[i].second << "\n";
  }
  return 0;
}
