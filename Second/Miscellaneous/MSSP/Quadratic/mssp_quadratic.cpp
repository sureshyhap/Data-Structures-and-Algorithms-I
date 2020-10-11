#include <iostream>
#include <vector>

int solve_MSSP(const std::vector<int>& numbers, int& start, int& end);

int main(int argc, char* argv[]) {
  std::vector<int> numbers {-10, 15, -10, 20, -50, 25, 10, -30, 15, -10, 40, -30, 20, -10, 5, -35, 20, -10, 15, -5};
  int start {0}, end {0};
  int solution {solve_MSSP(numbers, start, end)};
  std::cout << solution << '\n';
  if (start == -1 and end == -1) {
    std::cout << "No solution\n";
    return 0;
  }
  for (int i {start}; i <= end; ++i) {
    std::cout << numbers[i] << " ";
  }
  std::cout << '\n';
  return 0;
}

int solve_MSSP(const std::vector<int>& numbers, int& start, int& end) {
  int max_sum {0};
  start = {-1}, end = {-1};
  size_t length {numbers.size()};
  for (int i {0}; i < length; ++i) {
    int sum {0};
    for (int j {i}; j < length; ++j) {
      sum += numbers[j];
      if (sum > max_sum) {
	max_sum = sum;
	start = i;
	end = j;
      }
    }
  }
  return max_sum;
}
