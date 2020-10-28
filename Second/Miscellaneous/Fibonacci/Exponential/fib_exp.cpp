#include <iostream>

int fib_exp(int n);

int main(int argc, char* argv[]) {
  std::cout << fib_exp(11) << '\n';
  return 0;
}

int fib_exp(int n) {
  if (n <= 2) {
    return 1;
  }
  return fib_exp(n - 1) + fib_exp(n - 2);
}
