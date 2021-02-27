#include <iostream>
#include <vector>

int solve_MSSP(const std::vector<int>& numbers, int i, int j, int& start, int& end);

int main(int argc, char* argv[]) {
  std::vector<int> nums{-10, 15, -10, 20, -50, 25, 10, -30, 15, -10, 40, -30, 20, -10, 5, -35, 20, -10, 15, -5};
  // std::vector<int> nums{-10, 15, -10, 20, -50, 25, 10, -30, 15, -10, 40, -30, 20, -10, 5, -35, 20, -10, 15, -5, -10, -20, -30};
  // std::vector<int> nums{-10, -15, -10, -20, -50, -25, -10, -30, -15, -10, -40, -30, -20, -10, -5, -35, 20, -10, -15, -5};
  // std::vector<int> nums{-10, -15, -10, -20, -50, -25, -10, -30, -15, -10, -40, -30, -20, -10, -5, -35, -20, -10, -15, -5};
  int start {-1}, end {-1};
  int solution {solve_MSSP(nums, 0, nums.size() - 1, start, end)};
  std::cout << solution << '\n';
  if (start == -1 and end == -1) {
    std::cout << "No solution\n";
    return 0;
  }
  for (int i {start}; i <= end; ++i) {
    std::cout << nums[i] << ' ';
  }
  std::cout << '\n';
  return 0;
}

int solve_MSSP(const std::vector<int>& numbers, int i, int j, int& start, int& end) {
  if (j <= i) {
    return numbers[i];
  }
  int max_sum_left {solve_MSSP(numbers, i, (i + j) / 2, start, end)};
  int left_start = start, left_end = end;
  int max_sum_right {solve_MSSP(numbers, ((i + j) / 2) + 1, j, start, end)};
  int right_start = start, right_end = end;
  int max_sum_middle {0};
  int middle {(i + j) / 2};
  int mid_start = {middle}, mid_end = {middle};
  int sum {0};
  for (int k {middle}; k >= i; --k) {
    sum += numbers[k];
    if (sum > max_sum_middle) {
      max_sum_middle = {sum};
      mid_start = {k};
    }
  }
  sum = {max_sum_middle};
  for (int k {middle + 1}; k <= j; ++k) {
    sum += numbers[k];
    if (sum > max_sum_middle) {
      max_sum_middle = {sum};
      mid_end = {k};
    }
  }
  int max = {max_sum_left > max_sum_right ? max_sum_left : max_sum_right};  
  max = {max > max_sum_middle ? max : max_sum_middle};
  if (max) {
    int intermediate_start = {max_sum_left > max_sum_right ? left_start : right_start};
    int intermediate_end = {max_sum_left > max_sum_right ? left_end : right_end};
    intermediate_start = {max > max_sum_middle ? intermediate_start : mid_start};
    intermediate_end = {max > max_sum_middle ? intermediate_end : mid_end};
    start = intermediate_start;
    end = intermediate_end;
  }
  return max;
}


