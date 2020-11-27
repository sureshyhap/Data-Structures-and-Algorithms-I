#include <iostream>
#include <vector>
#include <list>
#include <cmath>

template <typename T>
void lsd_radix_sort(std::vector<T>& data);

template <typename T>
T get_max(std::vector<T>& data);

int main(int argc, char* argv[]) {
  std::vector<int> data = {329, 457, 657, 839, 436, 720, 355};
  lsd_radix_sort(data);
  for (auto elem : data) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';
  return 0;
}

template <typename T>
void lsd_radix_sort(std::vector<T>& data) {
  std::vector<std::list<T>> digits(10);
  T max = get_max(data);
  int runs = log10(max) + 1;
  int size = data.size();
  for (int pow_10 = 0; pow_10 < runs; ++pow_10) {
    for (int i = 0; i < size; ++i) {
      int reduced = data[i] / pow(10, pow_10);
      int digit = reduced % 10;
      digits[digit].push_back(data[i]);
    }
    int k = 0;
    for (int i = 0; i < 10; ++i) {
      for (typename std::list<T>::iterator it = digits[i].begin();
	   it != digits[i].end(); ++it) {
	data[k++] = *it;
      }
      digits[i].clear();
    }
  }
}

template <typename T>
T get_max(std::vector<T>& data) {
  try {
    if (!data.empty()) {
      T max = data.front();
      for (const T& elem : data) {
	if (elem > max) {
	  max = elem;
	}
      }
      return max;
    }
    else {
      throw std::runtime_error("No max since empty");
    }
  }
  catch (const std::runtime_error& re) {
    std::cerr << re.what();
    return T();
  }
}
