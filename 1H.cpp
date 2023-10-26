#include <iostream>
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

int LongSort(int length, int position, std::vector<int>& vector_for_long_sort) {
  const int kLocalMin = 1000000001;
  int local_min;
  int min_index;
  min_index = 0;
  for (int i = 0; i < length; ++i) {
    local_min = kLocalMin + 1;
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
      std::swap(numbers[i], numbers[indicator]);
      ++indicator;
    }
  }
  int left_pivot = indicator;
  for (int i = left_pivot; i <= right; ++i) {
    if (numbers[i] == pivot) {
      std::swap(numbers[i], numbers[indicator]);
      ++indicator;
    }
  }
  int right_pivot = indicator - 1;
  return std::make_pair(left_pivot, right_pivot);
}

int DetQuickSelect(std::vector<int>& numbers, int position, int left, int right,
                   std::vector<int>& vector_for_long_sort) {
  const int kLocalMin = 1000000001;
  const int kTen = 10;
  int length = right - left + 1;
  if (length <= kTen) {
    for (int i = left; i <= right; ++i) {
      vector_for_long_sort[i - left] = numbers[i];
    }
    return LongSort(length, position - left, vector_for_long_sort);
  }
  int degree_five = length;
  while (degree_five % 5 != 0) {
    ++degree_five;
  }
  std::vector<int> five_nums_medians(degree_five / 5 + 5, kLocalMin);
  for (int i = left; i < left + degree_five; i += 5) {
    five_nums_medians[(i - left) / 5] =
        MedianOfFiveNumbers(numbers[i], numbers[i + 1], numbers[i + 2],
                            numbers[i + 3], numbers[i + 4]);
  }
  int part_elem = DetQuickSelect(five_nums_medians, degree_five / kTen, 0,
                                 degree_five / 5 - 1, vector_for_long_sort);
  int indicator = left;
  for (int i = left; i <= right; ++i) {
    if (numbers[i] < part_elem) {
      std::swap(numbers[i], numbers[indicator]);
      ++indicator;
    }
  }
  int left_pivot = indicator;
  for (int i = left_pivot; i <= right; ++i) {
    if (numbers[i] == part_elem) {
      std::swap(numbers[i], numbers[indicator]);
      ++indicator;
    }
  }
  int right_pivot = indicator - 1;
  if (left_pivot > position) {
    return DetQuickSelect(numbers, position, left, left_pivot - 1,
                          vector_for_long_sort);
  }
  if (left_pivot <= position && position <= right_pivot) {
    return part_elem;
  }
  return DetQuickSelect(numbers, position, right_pivot + 1, right,
                        vector_for_long_sort);
}

void DetQuickSort(std::vector<int>& numbers, int left, int right,
                  std::vector<int>& vector_for_long_sort) {
  int length;
  length = right - left + 1;
  if (length != 1 && length != 0) {
    int part_elem = DetQuickSelect(numbers, left + length / 2, left, right,
                                   vector_for_long_sort);
    std::pair<int, int> l_and_r_pivots;
    l_and_r_pivots = Partition(numbers, part_elem, left, right);
    DetQuickSort(numbers, left, l_and_r_pivots.first - 1, vector_for_long_sort);
    DetQuickSort(numbers, l_and_r_pivots.second + 1, right,
                 vector_for_long_sort);
  }
}

int main() {
  const int kLocalMin = 1000000001;
  const int kTen = 10;
  std::vector<int> vector_for_long_sort(kTen);
  int length;
  std::cin >> length;
  std::vector<int> numbers(length + 5, kLocalMin);
  for (int i = 0; i < length; ++i) {
    std::cin >> numbers[i];
  }
  DetQuickSort(numbers, 0, length - 1, vector_for_long_sort);
  for (int i = 0; i < length; ++i) {
    std::cout << numbers[i] << " ";
  }
  return 0;
}
