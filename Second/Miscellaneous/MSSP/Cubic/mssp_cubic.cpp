#include <iostream>

int solve_MSSP(int a[], int size, int& start, int& end);

int main(int argc, char* argv[]) {
  int a[] {-10, 15, -10, 20, -50, 25, 10, -30, 15, -10, 40, -30, 20, -10, 5, -35, 20, -10, 15, -5};
  int size {sizeof(a) / sizeof(int)};
  int start {0}, end {0};
  int solution {solve_MSSP(a, size, start, end)};
  std::cout << solution << '\n';
  if (start == -1 and end == -1) {
    std::cout << "No solution";
    return 0;
  }
  for (int i {start}; i <= end; ++i) {
    std::cout << a[i] << " ";
  }
  std::cout << '\n';
  return 0;
}

int solve_MSSP(int a[], int size, int& start, int& end) {
  int max_sum {0};
  start = {-1}, end = {-1};
  for (int i {0}; i < size; ++i) {
    for (int j {i}; j < size; ++j) {
      int sum {0};
      for (int k {i}; k <= j; ++k) {
	sum += a[k];
      }
      if (sum > max_sum) {
	max_sum = {sum};
	start = {i};
	end = {j};
      }
    }
  }
  return max_sum;
}
