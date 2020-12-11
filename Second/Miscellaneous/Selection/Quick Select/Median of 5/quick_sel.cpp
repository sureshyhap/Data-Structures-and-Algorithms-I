#include <iostream>
#include <vector>
#include <cmath>

template <typename T>
int quick_select_index(std::vector<T>& v, int left, int right, int k, bool original_index = false);

template <typename T>
inline void swap(T& first, T& second);

template <typename T>
int median_of_median_of_five(std::vector<T>& v, int left, int right);

int main(int argc, char* argv[]) {
  //  std::vector<int> v = {5, 1, 2};
  std::vector<int> v = {5, 1, 2, 4, 3, 5, 2, 6, 7, 3, 3, 8, 7, 6, 9};
  std::cout << v[quick_select_index(v, 0, v.size() - 1, 10)];
  return 0;
}

template <typename T>
int quick_select_index(std::vector<T>& v, int left, int right, int k, bool original_index) {
  int size = v.size();
  std::vector<int> indices(size);
  for (int i = 0; i < size; ++i) {
    indices[i] = i;
  }
 beginning:
  if (left == right) {
    // If want original index before the array was modified
    if (original_index) {
      return indices[left];
    }
    else {
      return left;
    }
  }
  int mid = {};
  if (size <= 5) {
    mid = (left + right) / 2;
  }
  else {
    mid = median_of_median_of_five(v, 0, size - 1);
  }
  T pivot = v[mid];
  swap(v[mid], v[right]);
  swap(indices[mid], indices[right]);
  int i = {left - 1}, j = {right};
  while (i < j) {
    while (v[++i] < pivot) {
      ;
    }
    while (j >= i and v[--j] > pivot) {
      ;
    }
    if (i < j) {
      swap(v.at(i), v.at(j));
      swap(indices.at(i), indices.at(j));
    }
  }
  swap(v.at(i), v.at(right));
  swap(indices.at(i), indices.at(right));
  if (i == k) {
    if (original_index) {
      return indices[i];
    }
    else {
      return i;
    }
  }
  else if (i < k) {
    left = {i + 1};
    goto beginning;
  }
  else {
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

template <typename T>
int median_of_median_of_five(std::vector<T>& v, int left, int right) {
  int size = {right - left + 1};
  int num_groups = {ceil(size / 5)};
  std::vector<int> medians_index;
  for (int i = {0}; i < num_groups; ++i) {
    // 0-4, 5-9, etc.
    int l = left + i * 5;
    int r = left + ((i + 1) * 5) - 1;
    if (r > right) {
      r = right;
    }
    std::vector<T> w(v.begin() + l, v.begin() + r + 1);
    int size2 = w.size();
    // Holds indices of the median of each group w
    // i * 5 to convert it into an index of the original array
    medians_index.push_back((i * 5) + quick_select_index(w, 0, size2 - 1, (size2 - 1) / 2));
  }
  std::vector<T> medians;
  for (int i = 0; i < num_groups; ++i) {
    // Hold values of the medians
    medians.push_back(v[medians_index[i]]);
  }
  // After finding median of medians, its index is used to get the position of the median of medians in the original array
  int index_med = quick_select_index(medians, 0, num_groups - 1, (num_groups - 1) / 2, true);
  return medians_index[index_med];
}
