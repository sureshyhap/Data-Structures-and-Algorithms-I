#include <iostream>
#include <vector>

template <typename T>
void merge_sort(std::vector<T>& lyst, int left, int right);

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
  if (left == right) {
    return; //lyst.at(left);
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
