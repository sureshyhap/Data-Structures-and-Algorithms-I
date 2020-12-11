#include <iostream>
#include <vector>

template <typename T>
T quick_select(std::vector<T>& v, int left, int right, int k);

template <typename T>
inline void swap(T& first, T& second);

int main(int argc, char* argv[]) {
  std::vector<int> v = {5, 1, 2, 4, 3, 5, 2, 1, 7, 3, 3, 8, 7, 6, 9};
  std::cout << quick_select(v, 0, v.size() - 1, 3);
  return 0;
}

template <typename T>
T quick_select(std::vector<T>& v, int left, int right, int k) {
 beginning:
  if (left == right) {
    return v.at(left);
  }
  T pivot = {v.at(k)};
  swap(v.at(k), v.at(right));
  int i = {left - 1}, j = {right};
  while (i < j) {
    while (v.at(++i) < pivot) {
      ;
    }
    while (j >= i and v.at(--j) > pivot) {
      ;
    }
    if (i < j) {
      swap(v.at(i), v.at(j));
    }
  }
  swap(v.at(i), v.at(right));
  if (i == k) {
    return v.at(i);
  }
  else if (i < k) {
    //    quick_select(v, i + 1, right, k);
    left = {i + 1};
    goto beginning;
  }
  else {
    //    quick_select(v, left, i - 1, k);
    right = {i - 1};
    goto beginning;
  }
}

template <typename T>
inline void swap(T& first, T& second) {
  T temp = first;
  first = second;
  second = temp;
}
