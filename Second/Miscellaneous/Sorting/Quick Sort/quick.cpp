#include <iostream>
#include <vector>

template <typename T>
void quick_sort(typename std::vector<T>& lyst, int start, int end);

template <typename T>
inline void swap(T& first, T& second);

template <typename T>
void insertion_sort(std::vector<T>& lyst, int start, int end);

int main(int argc, char* argv[]) {
  std::vector<int> v = {4, 1, 3, 6, 78, 3, 5, 2, 6, 3, 23, 1};
  quick_sort(v, 0, v.size() - 1);
  for (auto elem : v) {
    std::cout << elem << ' ';
  }
  std::cout << std::endl;
  return 0;
}

template <typename T>
void quick_sort(typename std::vector<T>& lyst, int start, int end) {
  static int insertion_cutoff = 5;
 beginning:
  if (end - start < insertion_cutoff) {
    return insertion_sort(lyst, start, end);
  }
  int mid_index = {(start + end) / 2};
  T pivot = {lyst.at(mid_index)};
  swap(lyst.at(mid_index), lyst.at(end));
  int i = {start - 1}, j = {end};
  while (i < j) {
    while (lyst.at(++i) < pivot) {
      ;
    }
    while (j >= i and lyst.at(--j) > pivot) {
      ;
    }
    if (i < j) {
      swap(lyst.at(i), lyst.at(j));
    }
  }
  swap(lyst.at(i), lyst.at(end));
  quick_sort(lyst, start, i - 1);
  start = i + 1;
  goto beginning;
}

template <typename T>
inline void swap(T& first, T& second) {
  T temp = first;
  first = second;
  second = temp;
}

template <typename T>
void insertion_sort(std::vector<T>& lyst, int start, int end) {
  int length = {end - start + 1};
  for (int i = {start + 1}; i < start + length; ++i) {
    T data = {lyst.at(i)};
    int j = {i - 1};
    for (; j >= start; --j) {
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
