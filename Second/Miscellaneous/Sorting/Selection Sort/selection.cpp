#include <iostream>
#include <vector>

template <typename T>
void selection_sort(std::vector<T>& lyst);

int main(int argc, char* argv[]) {
  std::vector<int> v = {3, 6, 1, 45, 1, 7, 3, 56, 78, 1};
  selection_sort(v);
  for (auto elem : v) {
    std::cout << elem << ' ';
  }
  std::cout << std::endl;
  return 0;
}

template <typename T>
void selection_sort(std::vector<T>& lyst) {
  typename std::vector<T>::size_type length = {lyst.size()};
  for (typename std::vector<T>::size_type i = {0}; i < length; ++i) {
    typename std::vector<T>::size_type min_index = {i}, j = {i};
    for (; j < length; ++j) {
      if (lyst.at(j) < lyst.at(min_index)) {
	min_index = {j};
      }
    }
    T temp = {lyst.at(i)};
    lyst.at(i) = {lyst.at(min_index)};
    lyst.at(min_index) = {temp};
  }
}
