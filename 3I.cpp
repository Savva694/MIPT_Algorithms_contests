#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

class SparseTable {
 private:
  std::vector<std::vector<std::pair<int, int>>> sparse_;
  std::vector<int> numbers_;

  std::pair<int, int> FindFirstAndSecondMins(std::pair<int, int> first,
                                             std::pair<int, int> second) {
    std::vector<int> vector_for_sort(4);
    vector_for_sort[0] = first.first;
    vector_for_sort[1] = first.second;
    vector_for_sort[2] = second.first;
    vector_for_sort[3] = second.second;
    for (int i = 0; i < 3; ++i) {
      for (int j = i + 1; j < 4; ++j) {
        if (numbers_[vector_for_sort[i]] > numbers_[vector_for_sort[j]]) {
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

 public:
  SparseTable(int length, std::vector<int>& new_numbers) {
    numbers_ = new_numbers;
    int height = static_cast<int>(log2(length)) + 1;
    sparse_.resize(height);
    sparse_[0].resize(length);
    for (int i = 0; i < length; ++i) {
      sparse_[0][i].first = i;
      sparse_[0][i].second = i;
    }
    for (int i = 1; i < height; ++i) {
      sparse_[i].resize(length);
      for (int j = 0; j < length; ++j) {
        std::pair<int, int> first = sparse_[i - 1][j];
        std::pair<int, int> second = sparse_[i - 1][std::min(
            length - 1, j + static_cast<int>(pow(2, i - 1)))];
        sparse_[i][j] = FindFirstAndSecondMins(first, second);
      }
    }
  }

  int GetBorders(int left, int right) {
    --left;
    --right;
    int degree = static_cast<int>(log2(right - left + 1));
    std::pair<int, int> answer = FindFirstAndSecondMins(
        sparse_[degree][left],
        sparse_[degree][right - static_cast<int>(pow(2, degree)) + 1]);
    return numbers_[answer.second];
  }
};

int main() {
  int length;
  int questions;
  std::cin >> length;
  std::cin >> questions;
  std::vector<int> numbers(length);
  for (int i = 0; i < length; ++i) {
    std::cin >> numbers[i];
  }
  SparseTable sparse_table(length, numbers);
  int left;
  int right;
  for (int question = 0; question < questions; ++question) {
    std::cin >> left >> right;
    std::cout << sparse_table.GetBorders(left, right) << "\n";
  }
  return 0;
}
