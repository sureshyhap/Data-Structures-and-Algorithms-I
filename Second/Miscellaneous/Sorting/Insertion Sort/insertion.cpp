#include <iostream>
#include <vector>

template <typename T>
void insertion_sort(std::vector<T>& lyst);

int main(int argc, char* argv[]) {
  std::vector<int> v = {1, 67, 2, 7, 4, 8, 1, 5, 2, 2, 4, 6, 78, 3, 2};
  insertion_sort(v);
  for (auto elem : v) {
    std::cout << elem << ' ';
  }
  std::cout << std::endl;
  return 0;
}

template <typename T>
void insertion_sort(std::vector<T>& lyst) {
  int length = {lyst.size()};
  for (int i = {1}; i < length; ++i) {
    T data = {lyst.at(i)};
    int j = {i - 1};
    for (; j >= 0; --j) {
      if (lyst.at(j) > data) {
	lyst.at(j + 1) = {lyst.at(j)};
      }
      else {
	break;
      }
    }
    lyst.at(j + 1) = data;
  }
}
