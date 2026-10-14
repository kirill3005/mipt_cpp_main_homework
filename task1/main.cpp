#include <algorithm>
#include <iomanip>
#include <iostream>

struct TemperatureRange {
  int minimum;
  int maximum;
};

double AverageTemperature(const int* temperatures, int days_count) {
  long long sum = 0;
  for (int i = 0; i < days_count; ++i) {
    sum += temperatures[i];
  }
  return static_cast<double>(sum) / days_count;
}

TemperatureRange MinMaxTemperature(const int* temperatures, int days_count) {
  TemperatureRange range;
  range.minimum = temperatures[0];
  range.maximum = temperatures[0];
  for (int i = 1; i < days_count; ++i) {
    range.minimum = std::min(range.minimum, temperatures[i]);
    range.maximum = std::max(range.maximum, temperatures[i]);
  }
  return range;
}

int FrostDaysCount(const int* temperatures, int days_count) {
  int frost_days = 0;
  for (int i = 0; i < days_count; ++i) {
    if (temperatures[i] < 0) {
      ++frost_days;
    }
  }
  return frost_days;
}

int main() {
  int days_count;
  std::cin >> days_count;
  if (days_count <= 0) {
    return 0;
  }
  int* temperatures = new int[days_count];
  for (int i = 0; i < days_count; ++i) {
    std::cin >> temperatures[i];
  }

  TemperatureRange range = MinMaxTemperature(temperatures, days_count);

  std::cout << std::fixed << std::setprecision(1)
            << AverageTemperature(temperatures, days_count) << '\n';
  std::cout << range.minimum << ' ' << range.maximum << '\n';
  std::cout << FrostDaysCount(temperatures, days_count) << '\n';

  delete[] temperatures;
}
