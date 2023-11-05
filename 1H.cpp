#include <iostream>
#include <limits>
#include <vector>

int MedianOfFiveNumbers(int num1, int num2, int num3, int num4, int num5) {
  if (num1 > num2) {
    std::swap(num1, num2);
  }
  if (num3 > num4) {
    std::swap(num3, num4);
  }
  if (num4 > num5) {
    std::swap(num4, num5);
  }
  if (num3 > num4) {
    std::swap(num3, num4);
  }
  if (num3 < num1) {
    std::swap(num3, num1);
  }
  if (num3 < num2) {
    std::swap(num3, num2);
  }
  return std::min(num3, num4);
}

int LongSort(int position, std::vector<int>& vector_for_long_sort) {
  const int kLocalMax = std::numeric_limits<int>::max() - 1;
  int length = static_cast<int>(vector_for_long_sort.size());
  int local_min;
  int min_index = 0;
  for (int i = 0; i < length; ++i) {
    local_min = kLocalMax + 1;
    for (int j = i; j < length; ++j) {
      if (vector_for_long_sort[j] < local_min) {
        local_min = vector_for_long_sort[j];
        min_index = j;
      }
    }
    if (vector_for_long_sort[i] > vector_for_long_sort[min_index]) {
      std::swap(vector_for_long_sort[i], vector_for_long_sort[min_index]);
    }
  }
  return vector_for_long_sort[position];
}

std::pair<int, int> Partition(std::vector<int>& numbers, int pivot, int left,
                              int right) {
  int indicator = left;
  for (int i = left; i <= right; ++i) {
    if (numbers[i] < pivot) {
      std::swap(numbers[i], numbers[indicator++]);
    }
  }
  int left_pivot = indicator;
  for (int i = left_pivot; i <= right; ++i) {
    if (numbers[i] == pivot) {
      std::swap(numbers[i], numbers[indicator++]);
    }
  }
  int right_pivot = indicator - 1;
  return std::make_pair(left_pivot, right_pivot);
}

int DeterministicQuickSelect(std::vector<int>& numbers, int position, int left,
                             int right) {
  const int kLocalMax = std::numeric_limits<int>::max() - 1;
  const int kBaseLength = 10;
  int length = right - left + 1;
  if (length <= kBaseLength) {
    std::vector<int> vector_for_long_sort(length);
    for (int i = left; i <= right; ++i) {
      vector_for_long_sort[i - left] = numbers[i];
    }
    return LongSort(position - left, vector_for_long_sort);
  }
  int degree_five = length;
  while (degree_five % 5 != 0) {
    ++degree_five;
  }
  std::vector<int> five_nums_medians(degree_five / 5 + 5, kLocalMax);
  for (int i = left; i < left + degree_five; i += 5) {
    five_nums_medians[(i - left) / 5] =
        MedianOfFiveNumbers(numbers[i], numbers[i + 1], numbers[i + 2],
                            numbers[i + 3], numbers[i + 4]);
  }
  const int kNewPosition = 10;
  int partition_element = DeterministicQuickSelect(
      five_nums_medians, degree_five / kNewPosition, 0, degree_five / 5 - 1);
  int indicator = left;
  for (int i = left; i <= right; ++i) {
    if (numbers[i] < partition_element) {
      std::swap(numbers[i], numbers[indicator++]);
    }
  }
  int left_pivot = indicator;
  for (int i = left_pivot; i <= right; ++i) {
    if (numbers[i] == partition_element) {
      std::swap(numbers[i], numbers[indicator++]);
    }
  }
  int right_pivot = indicator - 1;
  if (left_pivot > position) {
    return DeterministicQuickSelect(numbers, position, left, left_pivot - 1);
  }
  if (left_pivot <= position && position <= right_pivot) {
    return partition_element;
  }
  return DeterministicQuickSelect(numbers, position, right_pivot + 1, right);
}

void DeterministicQuickSort(std::vector<int>& numbers, int left, int right) {
  int length = right - left + 1;
  if (length != 1 && length != 0) {
    int partition_element =
        DeterministicQuickSelect(numbers, left + length / 2, left, right);
    std::pair<int, int> left_and_right_pivots =
        Partition(numbers, partition_element, left, right);
    DeterministicQuickSort(numbers, left, left_and_right_pivots.first - 1);
    DeterministicQuickSort(numbers, left_and_right_pivots.second + 1, right);
  }
}

int main() {
  const int kLocalMax = std::numeric_limits<int>::max() - 1;
  int length;
  std::cin >> length;
  std::vector<int> numbers(length + 5, kLocalMax);
  for (int i = 0; i < length; ++i) {
    std::cin >> numbers[i];
  }
  DeterministicQuickSort(numbers, 0, length - 1);
  for (int i = 0; i < length; ++i) {
    std::cout << numbers[i] << " ";
  }
  return 0;
}
