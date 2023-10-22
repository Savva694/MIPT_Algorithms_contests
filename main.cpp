#include <iostream>
#include <vector>

const int kLocalMin = 10004321;
const int kConditionNum1 = 123;
const int kConditionNum2 = 45;
const int kTen = 10;
std::vector<int> vector_for_long_sort(kTen);

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

int LongSort(int length, int position) {
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

int DetQuickSelect(std::vector<int>* numbers, int position, int left,
                   int right) {
  int length = right - left + 1;
  if (length <= kTen) {
    for (int i = left; i <= right; ++i) {
      vector_for_long_sort[i - left] = (*numbers)[i];
    }
    return LongSort(length, position - left);
  }
  int degree_five;
  degree_five = length;
  while (degree_five % 5 != 0) {
    ++degree_five;
  }
  std::vector<int> five_nums_medians;
  five_nums_medians.resize(degree_five / 5 + 5, kLocalMin);
  for (int i = left; i < left + degree_five; i += 5) {
    five_nums_medians[(i - left) / 5] =
        MedianOfFiveNumbers((*numbers)[i], (*numbers)[i + 1], (*numbers)[i + 2],
                            (*numbers)[i + 3], (*numbers)[i + 4]);
  }
  int part_elem;
  part_elem = DetQuickSelect(&five_nums_medians, degree_five / kTen, 0,
                             degree_five / 5 - 1);
  int indicator = left;
  int left_pivot;
  int right_pivot;
  for (int i = left; i <= right; ++i) {
    if ((*numbers)[i] < part_elem) {
      std::swap((*numbers)[i], (*numbers)[indicator]);
      ++indicator;
    }
  }
  left_pivot = indicator;
  for (int i = left_pivot; i <= right; ++i) {
    if ((*numbers)[i] == part_elem) {
      std::swap((*numbers)[i], (*numbers)[indicator]);
      ++indicator;
    }
  }
  right_pivot = indicator - 1;
  if (left_pivot > position) {
    return DetQuickSelect(numbers, position, left, left_pivot - 1);
  }
  if (left_pivot <= position && position <= right_pivot) {
    return part_elem;
  }
  return DetQuickSelect(numbers, position, right_pivot + 1, right);
}

int main() {
  int length;
  int position;
  std::cin >> length;
  std::cin >> position;
  std::vector<int> numbers;
  numbers.resize(length + 5, kLocalMin);
  std::cin >> numbers[0] >> numbers[1];
  for (int i = 2; i < length; ++i) {
    numbers[i] =
        (numbers[i - 1] * kConditionNum1 + numbers[i - 2] * kConditionNum2) %
        (kLocalMin);
  }
  std::cout << DetQuickSelect(&numbers, position - 1, 0, length - 1);
  return 0;
}
