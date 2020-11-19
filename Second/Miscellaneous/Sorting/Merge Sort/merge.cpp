#include <iostream>
#include <vector>

template <typename T>
void merge_sort(std::vector<T>& lyst, int left, int right);

template <typename T>
void insertion_sort(std::vector<T>& lyst, int start, int end);

int main(int argc, char* argv[]) {
  std::vector<int> v = {1, 6, 3, 5, 3, 5, 7, 8, 45, 3, 6, 4, 6, 2};
  merge_sort(v, 0, v.size() - 1);
  for (auto elem : v) {
    std::cout << elem << ' ';
  }
  std::cout << std::endl;
  return 0;
}

template <typename T>
void merge_sort(typename std::vector<T>& lyst, int left, int right) {
  static int insertion_cutoff = {3};
  if (right - left < insertion_cutoff) {
    return insertion_sort(lyst, left, right);
  }
  int middle = {(left + right) / 2};
  merge_sort(lyst, left, middle);
  merge_sort(lyst, middle + 1, right);
  typename std::vector<T> aux;
  int i = left, j = middle + 1;
  while (i <= middle and j <= right) {
    if (lyst.at(i) <= lyst.at(j)) {
      aux.push_back(lyst.at(i++));
    }
    else {
      aux.push_back(lyst.at(j++));
    }
  }
  if (i > middle) {
    while (j <= right) {
      aux.push_back(lyst.at(j++));
    }
  }
  else if (j > right) {
    while (i <= middle) {
      aux.push_back(lyst.at(i++));
    }
  }
  for (int a = left; a <= right; ++a) {
    lyst.at(a) = {aux.at(a - left)};
  }
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
