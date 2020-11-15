#include <iostream>
#include <vector>

template <typename T>
void bubble_sort(typename std::vector<T>& lyst);

int main(int argc, char* argv[]) {
  std::vector<int> v = {4, 1, 7, 3, 7, 2, 6, 6, 1, 3, 6};
  bubble_sort(v);
  for (auto elem : v) {
    std::cout << elem << ' ';
  }
  std::cout << std::endl;
  return 0;
}

template <typename T>
void bubble_sort(typename std::vector<T>& lyst) {
  typename std::vector<T>::size_type length = {lyst.size()};
  for (typename std::vector<T>::size_type i = {0}; i < length - 1; ++i) {
    bool swapped = {false};
    for (typename std::vector<T>::size_type j = 0; j < length - i - 1; ++j) {
      if (lyst.at(j) > lyst.at(j + 1)) {
	T temp = {lyst.at(j)};
	lyst.at(j) = {lyst.at(j + 1)};
	lyst.at(j + 1) = {temp};
	swapped = {true};
      }
    }
    if (!swapped) {
      return;
    }
  }
}
