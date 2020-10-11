#include <iostream>
#include <vector>
#include <iterator>

int solve_MSSP(const std::vector<int>& numbers, int& max_start, int& max_end);

int main(int argc, char* argv[]) {
  int a[20] = {-10, 15, -10, 20, -50, 25, 10, -30, 15, -10, 40, -30, 20, -10, 5, -35, 20, -10, 15, -5};
  std::vector<int> nums(std::begin(a), std::end(a));
  int solution_start {0}, solution_end {0};
  int solution {solve_MSSP(nums, solution_start, solution_end)};
  for (std::vector<int>::const_iterator cit {nums.begin()};
       cit != nums.end(); ++cit) {
    std::cout << *cit << " ";
  }
  std::cout << '\n';
  if (solution_start == -1 && solution_end == -1) {
    std::cout << "No solution\n";
    return 0;
  }
  for (int i {solution_start}; i <= solution_end; ++i) {
    std::cout << nums[i] << " ";
  }
  std::cout << "\nLargest sum: " << solution << '\n';

  return 0;
}

int solve_MSSP(const std::vector<int>& numbers, int& max_start, int& max_end) {
  size_t length {numbers.size()};
  int max_sum {0}, temp_sum {0};
  max_start = {-1}, max_end = {-1};
  int start {0};
  for (int i {0}; i < length; ++i) {
    temp_sum += numbers[i];
    if (temp_sum < 0) {
      start = {i + 1};
      temp_sum = {0};
    }
    else if (temp_sum > max_sum) {
      max_sum = {temp_sum};
      max_start = {start};
      max_end = {i};
    }
  }
  return max_sum;
}
