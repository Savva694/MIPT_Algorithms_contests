#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class RacersAndCars {
 private:
  std::vector<std::pair<std::string, std::string>> racers_cars_;
  std::vector<std::pair<std::string, std::string>> cars_racers_;

  std::string Find(std::vector<std::pair<std::string, std::string>>& array,
                   std::string& object, int left, int right) {
    int middle = (left + right) / 2;
    if (array[middle].first == object) {
      return array[middle].second;
    }
    if (left == right) {
      return "";
    }
    if (array[middle].first >= object) {
      return Find(array, object, left, middle);
    }
    if (array[middle].first < object) {
      return Find(array, object, middle + 1, right);
    }
    return Find(array, object, left, middle);
  }

 public:
  void Start() {
    std::sort(racers_cars_.begin(), racers_cars_.end());
    std::sort(cars_racers_.begin(), cars_racers_.end());
  }

  void Insert(std::string new_racer, std::string new_car) {
    racers_cars_.emplace_back(std::make_pair(new_racer, new_car));
    cars_racers_.emplace_back(std::make_pair(new_car, new_racer));
  }

  std::string Find(std::string racer_or_car) {
    std::string answer = Find(racers_cars_, racer_or_car, 0,
                              static_cast<int>(racers_cars_.size()) - 1);
    if (!answer.empty()) {
      return answer;
    }
    return Find(cars_racers_, racer_or_car, 0,
                static_cast<int>(cars_racers_.size()) - 1);
  }
};

int main() {
  RacersAndCars racers_and_cars;
  int racers_count;
  std::cin >> racers_count;
  std::string racer;
  std::string car;
  for (int i = 0; i < racers_count; ++i) {
    std::cin >> racer >> car;
    racers_and_cars.Insert(racer, car);
  }
  racers_and_cars.Start();
  int questions;
  std::cin >> questions;
  std::string car_or_racer;
  std::string answer;
  for (int question = 0; question < questions; ++question) {
    std::cin >> car_or_racer;
    std::cout << racers_and_cars.Find(car_or_racer) << "\n";
  }
  return 0;
}
