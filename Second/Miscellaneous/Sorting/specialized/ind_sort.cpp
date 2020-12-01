#include <iostream>
#include <vector>

template <typename T>
void quick_sort_ind(const std::vector<T>& lyst, std::vector<T*>& indirect, int start, int end);

template <typename T>
inline void swap(T& first, T& second);

template <typename T>
void insertion_sort(const std::vector<T>& lyst, std::vector<T*>& indirect, int start, int end);

template <typename T>
int median_of_three(const std::vector<T>& lyst, std::vector<T*>& indirect, int start, int end);

template <typename T>
void final_sort(std::vector<T>& lyst, const std::vector<T*> indirect);

int main(int argc, char* argv[]) {
  std::vector<int> v = {4, 1, 3, 6, 78, 3, 5, 2, 6, 3, 23, 1};
  int size = v.size();
  std::vector<int*> indirect(size, nullptr);
  for (int i = 0; i < size; ++i) {
    indirect[i] = &(v[i]);
  }
  quick_sort_ind(v, indirect, 0, v.size() - 1);
  final_sort(v, indirect);
  for (auto elem : v) {
    std::cout << elem << ' ';
  }
  std::cout << std::endl;
  return 0;
}

template <typename T>
void quick_sort_ind(const std::vector<T>& lyst, std::vector<T*>& indirect, int start, int end) {
  static int insertion_cutoff = {3};
 beginning:
  if (end - start < insertion_cutoff) {
    return insertion_sort(lyst, indirect, start, end);
  }
  int mid_index = median_of_three(lyst, indirect, start, end);
  T* pivot = {indirect.at(mid_index)};
  swap(indirect.at(mid_index), indirect.at(end - 1));
  int i = {start - 1}, j = {end - 1};
  while (i < j) {
    while (*(indirect.at(++i)) < *pivot) {
      ;
    }
    while (j >= i and *(indirect.at(--j)) > *pivot) {
      ;
    }
    if (i < j) {
      swap(indirect.at(i), indirect.at(j));
    }
  }
  swap(indirect.at(i), indirect.at(end - 1));
  quick_sort_ind(lyst, indirect, start, i - 1);
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
void insertion_sort(const std::vector<T>& lyst, std::vector<T*>& indirect, int start, int end) {
  int length = {end - start + 1};
  for (int i = {start + 1}; i < start + length; ++i) {
    T* data = {indirect.at(i)};
    int j = {i - 1};
    for (; j >= start; --j) {
      if (*(indirect.at(j)) > *data) {
	indirect.at(j + 1) = {indirect.at(j)};
      }
      else {
	break;
      }
    }
    indirect.at(j + 1) = data;
  }
}

template <typename T>
int median_of_three(const std::vector<T>& lyst, std::vector<T*>& indirect, int start, int end) {
  int mid_index = {(start + end) / 2};
  int*& s = indirect.at(start), *& m = indirect.at(mid_index), *& e = indirect.at(end);
  if (*s > *m) {
    swap(s, m);
  }
  if (*m > *e) {
    swap(m, e);
  }
  if (*s > *m) {
    swap(s, m);
  }
  return mid_index;
}

template <typename T>
void final_sort(std::vector<T>& lyst, const std::vector<T*> indirect) {
  int size = lyst.size();
  std::vector<T> aux(size);
  for (int i = 0; i < size; ++i) {
    aux[i] = *(indirect[i]);
  }
  for (int i = 0; i < size; ++i) {
    lyst[i] = aux[i];
  }
}
