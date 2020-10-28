#include <iostream>

int fib_linear(int n);

int main(int argc, char* argv[]) {
  std::cout << fib_linear(11) << '\n';
  
  return 0;
}

int fib_linear(int n) {
  int current {1};
  int prev2 {1}, prev1 {1};
  for (int i {3}; i <= n; ++i) {
    current = {prev1 + prev2};
    prev2 = {prev1};
    prev1 = {current};
  }
  return current;
}
