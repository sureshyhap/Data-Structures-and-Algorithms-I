template <typename T>
int median_of_five(std::vector<T>& v, int left, int right);

template <typename T>
int median_of_five(std::vector<T>& v, int left, int right) {
  int size = {v.size()};
  int num_groups = {size / 5};
  std::vector<int> medians_index;
  for (int i = {0}; i < num_groups; ++i) {
    medians_index.push_back(quick_select(v, left + i * 5, left + ((i + 1) * 5) - 1, (left + right) / 2));
  }
  std::vector<T> medians;
  for (int i = {0}; i < num_groups; ++i) {
    medians.push_back(v.at(medians_index.at(i)));
  }
  int group_num = quick_select(medians, 0, medians.size() - 1, (medians.size() - 1) / 2);
  return medians_index.at(group_num);
}
