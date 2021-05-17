// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2019

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
  string lastName;
  string firstName;
  string ssn;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {

  ifstream input(filename);
  if (!input) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    getline(input, line);
    stringstream ss2(line);
    Data *pData = new Data();
    ss2 >> pData->lastName >> pData->firstName >> pData->ssn;
    l.push_back(pData);
  }

  input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

  ofstream output(filename);
  if (!output) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << "\n";

  // Write the data
  for (auto pData:l) {
    output << pData->lastName << " " 
	   << pData->firstName << " " 
	   << pData->ssn << "\n";
  }

  output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;
  list<Data *> theList;
  loadDataList(theList, filename);

  cout << "Data loaded.\n";

  cout << "Executing sort...\n";
  clock_t t1 = clock();
  sortDataList(theList);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds.\n";

  cout << "Enter name of output file: ";
  cin >> filename;
  writeDataList(theList, filename);

  return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.

// Cutoff size for case 1
const int T1_CUTOFF = 102000;
// Cutoff size to activate insertion_sort_for_nlogn
const int INSERTION_SORT_CUTOFF = 20;

// For all of the array-based sorts
/////////////std::vector<Data*> v(1020000, NULL);
Data* v[1020000] = {NULL};

inline void swap(Data*& first, Data*& second);
void selection_sort(int size);
void bubble_sort(int size);
void insertion_sort(int size);
void insertion_sort_for_nlogn(int start, int end);
int median_of_three(int start, int end);
void quick_sort(int start, int end);
void quick_sort(int size);
void merge_sort(std::vector<Data*>& temp, int start, int end);
void merge_sort(int size);
int string_to_int(std::string ssn);
std::string int_to_string(int ssn);
void counting_sort(int size);
void lsd_radix_sort(int size);
bool names_less_or_eq(const Data& d1, const Data& d2);
bool operator<(const Data& d1, const Data& d2);
bool less_than(Data* pd1, Data* pd2);
int detect_case(const std::list<Data*>& l);

inline void swap(Data*& first, Data*& second) {
  Data* temp = first;
  first = second;
  second = temp;
}

void selection_sort(int size) {
  if (!size or size == 1) {
    return;
  }
  Data* min = {};
  for (int i = 0; i < size; ++i) {
    min = v[i];
    int min_index = i;
    for (int j = i + 1; j < size; ++j) {
      if (*v[j] < *min) {
	min = v[j];
	min_index = j;
      }
    }
    swap(v[i], v[min_index]);
  }
}

void bubble_sort(int size) {
  bool swapped = false;
  for (int i = 0; i < size - 1; ++i) {
    for (int j = 0; j < size - 1 - i; ++j) {
      if (*v[j + 1] < *v[j]) {
	swap(v[j], v[j + 1]);
	swapped = true;
      }
    }
    // No swaps on a pass through the elements
    // means it is sorted already
    if (!swapped) {
      return;
    }
    else {
      swapped = false;
    }
  }
}

void insertion_sort(int size) {
  Data* present_element = {};
  int new_spot = {};
  for (int i = 1; i < size; ++i) {
    present_element = v[i];
    for (int j = i - 1; j >= 0; --j) {
      if (*present_element < *v[j]) {
	v[j + 1] = v[j];
	if (!j) {
	  new_spot = 0;
	}
      }
      else {
	new_spot = j + 1;
	break;
      }
    }
    v[new_spot] = present_element;
  }
}

void insertion_sort_for_nlogn(int start, int end) {
  Data* present_element = {};
  int new_spot = {};
  for (int i = start + 1; i <= end; ++i) {
    present_element = v[i];
    for (int j = i - 1; j >= start; --j) {
      if (*present_element < *v[j]) {
	v[j + 1] = v[j];
	if (j == start) {
	  new_spot = start;
	}
      }
      else {
	new_spot = j + 1;
	break;
      }
    }
    v[new_spot] = present_element;
  }
}

// For quicksort
int median_of_three(int start, int end) {
  int mid = (start + end) / 2;
  if (*v[mid] < *v[start]) {
    swap(v[mid], v[start]);
  }
  if (*v[end] < *v[mid]) {
    swap(v[end], v[mid]);
  }
  if (*v[mid] < *v[start]) {
    swap(v[mid], v[start]);
  }
  return mid;
}

void quick_sort(int start, int end) {
 beginning:
  // Use insertion sort if problem is small enough
  if (end - start <= INSERTION_SORT_CUTOFF) {
    insertion_sort_for_nlogn(start, end);
    return;
  }
  int mid = median_of_three(start, end);
  swap(v[mid], v[end - 1]);
  int i = start, j = end - 1;
  while (i < j) {
    while (*v[++i] < *v[end - 1]) {
      ;
    }
    while (*v[end - 1] < *v[--j] and j > i) {
      ;
    }
    if (i < j) {
      swap(v[i], v[j]);
    }
  }
  swap(v[i], v[end - 1]);
  quick_sort(start, i - 1);
  start = i + 1;
  goto beginning;
}

void quick_sort(int size) {
  quick_sort(0, size - 1);
}

void merge_sort(std::vector<Data*>& temp, int start, int end) {
  // Use insertion sort if problem is small enough
  if (end - start <= INSERTION_SORT_CUTOFF) {
    insertion_sort_for_nlogn(start, end);
    return;
  }
  int mid = (start + end) / 2;
  merge_sort(temp, start, mid);
  merge_sort(temp, mid + 1, end);
  int i = start, j = mid + 1, k = start;
  while (i <= mid and j <= end) {
    if (*v[j] < *v[i]) {
      temp[k++] = v[j++];
    }
    else {
      temp[k++] = v[i++];
    }
  }
  while (j <= end) {
    temp[k++] = v[j++];
  }
  while (i <= mid) {
    temp[k++] = v[i++];
  }
  for (int a = start; a <= end; ++a) {
    v[a] = temp[a];
  }
}

void merge_sort(int size) {
  std::vector<Data*> temp(size);
  merge_sort(temp, 0, size - 1);
}

int string_to_int(std::string ssn) {
  // Removing the dashes
  ssn.erase(3, 1);
  ssn.erase(5, 1);
  // Convert to int
  std::istringstream iss(ssn);
  int equiv_num = {};
  iss >> equiv_num;
  return equiv_num;
}

std::string int_to_string(int ssn) {
  // Convert to string
  std::ostringstream oss;
  oss << ssn;
  std::string s = oss.str();
  int length = s.length();
  // 9 is the length of a ssn without dashes
  for (int i = 0; i < 9 - length; ++i) {
    s.insert(0, "0");
  }
  // Insert dashes
  s.insert(3, "-");
  s.insert(6, "-");
  return s;
}

// For counting and lsd radix sort
const int MAX_NUM = 999999999;

// For counting sort. Since ssns are unique
// can only have a max of 1 in a bin. So save
// space using an array of booleans
bool nums[MAX_NUM + 1] = {false};

void counting_sort(int size) {
  int ssn = {};
  for (int i = 0; i < size; ++i) {
    ssn = string_to_int(v[i]->ssn);
    nums[ssn] = true;
  }
  int i = 0;
  std::string ssn_str;
  for (int bucket = 0; bucket <= MAX_NUM; ++bucket) {
    if (nums[bucket]) {
      ssn_str = int_to_string(bucket);
      v[i++]->ssn = ssn_str;
    }
  }
}

// For lsd radix sort
// Sort by groups of SORT_BY_LAST digits
const int SORT_BY_LAST = 1000;
// The average bin size will be total number of elements
// divided by the number os bins. Multiply by 5 in case there
// is an excess of values in a particular bin
const int BIN_SIZE = 5 * (1020000 / SORT_BY_LAST);
// RUNS is the amount of times we extract the least significant
// groups of digits that have not been extracted so far
const int RUNS = ceil(log(MAX_NUM) / log(SORT_BY_LAST));

// Holds the integer values of ssns
int v_int_ssns[1020000] = {0};
// The temporary 2D array to hold the integers for radix sort
int radix[BIN_SIZE][SORT_BY_LAST] = {{0}};

void lsd_radix_sort(int size) {
  // Copy over the ssns as numbers to an auxiliary array
  for (int i = 0; i < size; ++i) {
    v_int_ssns[i] = string_to_int(v[i]->ssn);
  }
  int ssn = {};
  int last_digits = {};
  // Keeps track of how many numbers are in each bin
  int spot_in_bin[SORT_BY_LAST] = {0};
  int k = {};
  for (int runs = 0; runs < RUNS; ++runs) {
    for (int i = 0; i < size; ++i) {
      ssn = v_int_ssns[i];
      // Drop the last set of digits based on the run number
      // and then strip the remaining last set of digits
      last_digits = static_cast<int>(ssn / pow(SORT_BY_LAST, runs)) % SORT_BY_LAST;
      // Insert the number in the correct bin and spot in the bin based on
      // its last digits and the value of spot_in_bin for that bin. Spot in
      // bin is incremented for the given bin to hold the next potential number
      radix[(spot_in_bin[last_digits])++][last_digits] = ssn;
    }
    k = 0;
    for (int i = 0; i < SORT_BY_LAST; ++i) {
      for (int j = 0; j < spot_in_bin[i]; ++j) {
	// Read from the radix 2D array back to the array of numerical ssns
	// after a given pass through all the numbers
	v_int_ssns[k++] = radix[j][i];
      }
    }
    // Resetting the spot_in_bin for each bin to 0 effectively
    // "clears" each bin (not truly clearing but acts like it)
    for (int i = 0; i < SORT_BY_LAST; ++i) {
      spot_in_bin[i] = 0;
    }
  }
  // Finally rewriting the numerical ssns back to string ssns that
  // are data members associated with the original array of pointers
  for (int i = 0; i < size; ++i) {
    v[i]->ssn = int_to_string(v_int_ssns[i]);
  }
}

// Used in the case detection function to check if elements are sorted
bool name_less_or_eq(const Data& d1, const Data& d2) {
  if (d1.lastName < d2.lastName) {
    return true;
  }
  else if (d1.lastName > d2.lastName) {
    return false;
  }
  // If reached here, last names are the same
  if (d1.firstName < d2.firstName) {
    return true;
  }
  else if (d1.firstName > d2.firstName) {
    return false;
  }
  // If reached here, both names are the same
  return true;
}

bool operator<(const Data& d1, const Data& d2) {  
  if (d1.lastName < d2.lastName) {
    return true;
  }
  else if (d1.lastName > d2.lastName) {
    return false;
  }
  // If reached here, last names are the same
  if (d1.firstName < d2.firstName) {
    return true;
  }
  else if (d1.firstName > d2.firstName) {
    return false;
  }
  // If reached here, both names are the same
  if (d1.ssn < d2.ssn) {
    return true;
  }
  // Since ssns are unique, if not < must be >
  else {
    return false;
  }
}

bool less_than(Data* pd1, Data* pd2) {
  return *pd1 < *pd2;
}

int detect_case(const std::list<Data*>& l) {
  // If list is small, case is T1
  if (l.size() < T1_CUTOFF) {
    return 1;
  }
  Data* first = l.front();
  bool same_names = true;
  // Check the first 5 names to see if they are the same
  std::list<Data*>::const_iterator cit = l.begin();
  for (int i = 0; i < 5; ++i) {
    if (((*cit)->lastName != first->lastName) ||
	((*cit)->firstName != first->firstName)) {
      same_names = false;
      break;
    }
    ++cit;
  }
  // If the names are the same, case is T4
  if (same_names) {
    return 4;
  }
  bool names_sorted = true;
  // Check if the first 20 names are sorted already by names
  cit = l.begin();
  for (int i = 0; i < 20; ++i) {
    // Check if two names are sorted with respect to each other
    if (!(names_less_or_eq(**cit, **std::next(cit)))) {
      names_sorted = false;
      break;
    }
    ++cit;
  }
  // If the names are sorted, case is T3
  if (names_sorted) {
    return 3;
  }
  // If none of the above cases, case is T2
  else {
    return 2;
  }
}

void sortDataList(std::list<Data*>& l) {
  // Copy list over to a vector
  ////////////////////////  v.assign(l.begin(), l.end());
  int size = l.size();
  int i = 0;
  for (std::list<Data*>::const_iterator cit = l.begin();
       cit != l.end(); ++cit) {
    v[i++] = *cit;
  }
  switch (detect_case(l)) {
  case 1:
    //    l.sort(less_than);
    //    std::sort(v.begin(), v.end(), less_than);
    quick_sort(size);
    //    merge_sort(size);
    break;
  case 2:
    //    l.sort(less_than);
    //    std::sort(v.begin(), v.end(), less_than);
    quick_sort(size);
    //    merge_sort(size);
    break;
  case 3:
    //    l.sort(less_than);
    //    std::sort(v.begin(), v.end(), less_than);
    //    std::stable_sort(v.begin(), v.end(), less_than);
    //    bubble_sort(size);
    insertion_sort(size);
    //    quick_sort(size);
    //    merge_sort(size);
    break;
  case 4:
    //    l.sort(less_than);
    //    std::sort(v.begin(), v.end(), less_than);
    //    quick_sort(size);
    //    merge_sort(size);
    //    counting_sort(size);
    lsd_radix_sort(size);
    break;
  }
  i = 0;
  for (std::list<Data*>::iterator it = l.begin();
       it != l.end(); ++it) {
    *it = v[i++];
  }
}
