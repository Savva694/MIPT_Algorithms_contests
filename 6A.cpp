#include <algorithm>
#include <cmath>
#include <iostream>
#include <stack>
#include <vector>

size_t BinarySearch(std::vector<int>& numbers, size_t left, size_t right,
                    int element) {
  if (left + 1 == right) {
    return right - 1;
  }
  size_t middle = (left + right) / 2;
  if (numbers[middle - 1] >= element) {
    return BinarySearch(numbers, middle, right, element);
  }
  return BinarySearch(numbers, left, middle, element);
}

std::vector<size_t> LargestNonDecreasingSubsequence(
    const std::vector<int>& numbers) {
  const int kInf = 2147483647;
  size_t number_count = numbers.size();
  std::vector<int> max_last_number(number_count, -kInf);
  std::vector<size_t> index_changes(number_count);
  size_t length = 0;
  max_last_number[0] = numbers[0];
  index_changes[0] = 0;

  for (size_t k = 2; k <= number_count; ++k) {
    size_t index =
        BinarySearch(max_last_number, 0, number_count, numbers[k - 1]);
    index_changes[k - 1] = index;
    length = std::max(length, index + 1);
    max_last_number[index] = numbers[k - 1];
  }

  std::vector<size_t> sequence;
  size_t index = length - 1;

  for (size_t i = number_count; i > 0; --i) {
    if (index_changes[i - 1] == index) {
      sequence.push_back(i);
      --index;
    }
  }

  std::reverse(sequence.begin(), sequence.end());
  return sequence;
}

int main() {
  size_t number_count;
  std::cin >> number_count;
  std::vector<int> numbers(number_count);

  for (size_t i = 0; i < number_count; ++i) {
    std::cin >> numbers[i];
  }

  std::vector<size_t> sequence = LargestNonDecreasingSubsequence(numbers);

  std::cout << sequence.size() << "\n";
  for (size_t number : sequence) {
    std::cout << number << " ";
  }
}
