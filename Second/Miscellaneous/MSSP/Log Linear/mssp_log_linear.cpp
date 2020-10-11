#include <iostream>
#include <vector>

int solve_MSSP(const std::vector<int>& numbers, int i, int j, int& start, int& end);

int main(int argc, char* argv[]) {
  std::vector<int> nums{-10, 15, -10, 20, -50, 25, 10, -30, 15, -10, 40, -30, 20, -10, 5, -35, 20, -10, 15, -5};
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
  int max_sum_right {solve_MSSP(numbers, ((i + j) / 2) + 1, j, start, end)};
  int max_sum_middle {0};
  int middle {(i + j) / 2};
  int sum {0};
  for (int k {middle}; k >= i; --k) {
    sum += numbers[k];
    if (sum > max_sum_middle) {
      max_sum_middle = {sum};
      start = {k};
    }
  }
  end = {middle};
  sum = {max_sum_middle};
  for (int k {middle + 1}; k <= j; ++k) {
    sum += numbers[k];
    if (sum > max_sum_middle) {
      max_sum_middle = {sum};
      end = {k};
    }
  }
  int max1 {max_sum_left > max_sum_right ? max_sum_left : max_sum_right};
  int max {max1 > max_sum_middle ? max1 : max_sum_middle};
  return max;
}


