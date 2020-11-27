#include <iostream>
#include <vector>

template <typename T>
void counting_sort(std::vector<T>& data, int max);

int main(int argc, char* argv[]) {
  std::vector<int> data = {11, 56, 237, 834, 2, 6, 3, 74, 3, 2, 56, 34, 11, 1000, 1, 6, 3, 8, 3, 8, 4, 1000};
  counting_sort(data, 1000);
  for (auto elem : data) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';
  return 0;
}

template <typename T>
void counting_sort(std::vector<T>& data, int max) {
  std::vector<T> count(max + 1);
  for (const T& elem : data) {
    ++count.at(elem);
  }
  int size_count = count.size();
  int k = 0;
  for (int i = 0; i < size_count; ++i) {
    for (int j = 0; j < count.at(i); ++j) {
      data.at(k++) = i;
    }
  }
}
