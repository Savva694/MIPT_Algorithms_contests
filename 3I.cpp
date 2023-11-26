#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

std::pair<int, int> FindFirstAndSecondMins(std::vector<int>& numbers,
                                           std::pair<int, int> first,
                                           std::pair<int, int> second) {
  std::vector<int> vector_for_sort(4);
  vector_for_sort[0] = first.first;
  vector_for_sort[1] = first.second;
  vector_for_sort[2] = second.first;
  vector_for_sort[3] = second.second;
  for (int i = 0; i < 3; ++i) {
    for (int j = i + 1; j < 4; ++j) {
      if (numbers[vector_for_sort[i]] > numbers[vector_for_sort[j]]) {
        std::swap(vector_for_sort[i], vector_for_sort[j]);
      }
    }
  }
  std::vector<int> answer;
  answer.push_back(vector_for_sort[0]);
  int last = answer[0];
  for (size_t i = 1; i < vector_for_sort.size(); ++i) {
    if (vector_for_sort[i] != last) {
      answer.push_back(vector_for_sort[i]);
      last = vector_for_sort[i];
    }
  }
  if (answer.size() == 1) {
    return {answer[0], answer[0]};
  }
  return {answer[0], answer[1]};
}

int main() {
  int length;
  int questions;
  std::cin >> length;
  std::cin >> questions;
  int height = static_cast<int>(log2(length)) + 1;
  std::vector<std::vector<std::pair<int, int>>> sparse(height);
  std::vector<int> numbers(length);
  sparse[0].resize(length);
  for (int i = 0; i < length; ++i) {
    std::cin >> numbers[i];
    sparse[0][i].first = i;
    sparse[0][i].second = i;
  }
  for (int i = 1; i < height; ++i) {
    sparse[i].resize(length);
    for (int j = 0; j < length; ++j) {
      std::pair<int, int> first = sparse[i - 1][j];
      std::pair<int, int> second = sparse[i - 1][std::min(
          length - 1, j + static_cast<int>(pow(2, i - 1)))];
      sparse[i][j] = FindFirstAndSecondMins(numbers, first, second);
    }
  }

  int left;
  int right;
  for (int question = 0; question < questions; ++question) {
    std::cin >> left >> right;
    --left;
    --right;
    int degree = static_cast<int>(log2(right - left + 1));
    std::pair<int, int> answer = FindFirstAndSecondMins(
        numbers, sparse[degree][left],
        sparse[degree][right - static_cast<int>(pow(2, degree)) + 1]);
    std::cout << numbers[answer.second] << std::endl;
  }
  return 0;
}
