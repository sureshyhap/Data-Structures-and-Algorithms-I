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

bool operator<(const Data& d1, const Data& d2) {
  if (d1.lastName < d2.lastName) {
    return true;
  }
  else if (d1.lastName > d2.lastName) {
    return false;
  }
  // Last names match
  else {
    if (d1.firstName < d2.firstName) {
      return true;
    }
    else if (d1.firstName > d2.firstName) {
      return false;
    }
    // First names match as well
    else {
      if (d1.ssn < d2.ssn) {
	return true;
      }
      else {
	return false;
      }
    }
  }
}

bool less_than(Data* d1, Data* d2) {
  return *d1 < *d2;
}

vector<Data*> a(1010001, NULL);

const int SORT_BASE = 20;
const int T1_SIZE_CUTOFF = 200000;

void quick_sort(int start, int size);
void insertion_sort(int start, int size, int sorting_by = 0);
void merge_sort(int start, int size, int sorting_by = 0);
void bubble_sort(int size);
void selection_sort(int size);
void lsd_radix_sort(int n);
void counting_sort(int arr[], int n);

void sortDataList(list<Data *> &l) {
  int test_case = 0;
  if (l.size() < T1_SIZE_CUTOFF) {
    test_case = 1;
  }
  // Very unlikely for the following to occur and the test case not be T4
  else if (l.front()->firstName == l.back()->firstName &&
	   l.back()->lastName == l.back()->lastName) {
    test_case = 4;
  }
  if (!test_case) {
    list<Data*>::iterator it = l.begin(), it2 = l.begin();
    ++it2;
    // If two adjacent elements have matching last names, at this point
    // case T3 is highly likely
    if ((*it)->lastName == (*it2)->lastName) {
      test_case = 3;
    }
  }
  // If none of the above test cases, must be T2
  if (!test_case) {
    test_case = 2;
  }
  
  //  l.sort(less_than);

  int size_list = l.size();
  int size_vec = a.size();
  int diff = size_vec - size_list;
  list<Data*>::iterator it_copy = l.begin();
  // Copy to array
  for (int i = 0; i < size_list; ++i, ++it_copy) {
    a[i] = *it_copy;
  }

  if (test_case == 1) { 
    merge_sort(0, size_list);
  }
  else if (test_case == 2) {
    quick_sort(0, size_list);
  }
  else if (test_case == 3) {
    insertion_sort(0, size_list);
  }
  else if (test_case == 4) {
    // Remove dashes
    for (int i = 0; i < size_list; ++i) {
      string& s = (a[i])->ssn;
      int length = s.length();
      for (int j = 0; j < s.length(); ++j) {
	if (s[j] == '-') {
	  s.erase(j, 1);
	}
      }
    }
    lsd_radix_sort(size_list);
    // Reinsert dashes
    for (int i = 0; i < size_list; ++i) {
      string& s = a[i]->ssn;
      s.insert(3, "-");
      s.insert(6, "-");
    }
    /*
    int ssn_numbers[size_list] = {0};
    int k = 0;
    for (list<Data*>::iterator it = l.begin(); it != l.end(); ++it) {
      string& s = (*it)->ssn;
      int length = s.length();
      for (int j = 0; j < s.length(); ++j) {
	if (s[j] == '-') {
	  s.erase(j, 1);
	}
      }
      istringstream iss(s);
      iss >> ssn_numbers[k++];
    }
    counting_sort(ssn_numbers, size_list);
    int i = 0;
    for (list<Data*>::iterator it = l.begin(); it != l.end(); ++it, ++i) {
      string s_temp1, s_temp2, s_temp3;
      int temp1 = ssn_numbers[i] % 10000;
      int temp2 = (ssn_numbers[i] / 10000) % 100;
      int temp3 = (ssn_numbers[i] / 1000000);
      ostringstream oss1, oss2, oss3;
      oss1 << temp1;
      s_temp1 = oss1.str();
      if (s_temp1.length() < 4) {
	int zeros = 4 - s_temp1.length();
	for (int i = 0; i < zeros; ++i) {
	  s_temp1.insert(0, "0");
	}
      }
      oss2 << temp2;
      s_temp2 = oss2.str();
      if (s_temp2.length() < 2) {
	int zeros = 2 - s_temp2.length();
	for (int i = 0; i < zeros; ++i) {
	  s_temp2.insert(0, "0");
	}
      }
      oss3 << temp3;
      s_temp3 = oss3.str();
      if (s_temp3.length() < 3) {
	int zeros = 3 - s_temp3.length();
	for (int i = 0; i < zeros; ++i) {
	  s_temp3.insert(0, "0");
	}
      }
      (*it)->ssn = s_temp3 + "-" + s_temp2 + "-" + s_temp1;
    
    }
    */    
  }
  
  //  sort(a.begin(), a.end() - diff, less_than);

  // Copy back to list
  it_copy = l.begin();
  for (int i = 0; i < size_list; ++i, ++it_copy) {
    *it_copy = a[i];
  }  
}

void quick_sort(int start, int size) {
 start:
  if (size < SORT_BASE) {
    insertion_sort(start, size);
    return;
  }
  // int pivot = a[start + size - 1];
  // Median-of-three partitioning
  int left = start;
  int right = start + size - 1;
  int median = (left + right) / 2;
  if (*a[median] < *a[left]) {
    Data* temp = a[median];
    a[median] = a[left];
    a[left] = temp;
  }
  if (*a[right] < *a[median]) {
    Data* temp = a[right];
    a[right] = a[median];
    a[median] = temp;
  }
  if (*a[median] < *a[left]) {
    Data* temp = a[median];
    a[median] = a[left];
    a[left] = temp;
  }
  Data* temp = a[median];
  a[median] = a[right - 1];
  a[right - 1] = temp;
  Data* pivot = a[right - 1];
  int i = left + 1, j = right - 2;
  while (true) {
    while (*a[i] < *pivot) {
      ++i;
    }
    while (j >= i && *pivot < *a[j]) {
      --j;
    }
    if (i < j) {
      Data* temp = a[i];
      a[i] = a[j];
      a[j] = temp;
    }
    else {
      a[right - 1] = a[i];
      a[i] = pivot;
      break;
    }
  }
  quick_sort(start, i - start);
  int s1 = start, s2 = size;
  start = i + 1;
  size = s1 + s2 - (i + 1);
  goto start;
}

void insertion_sort(int start, int size, int sorting_by) {
  for (int i = start + 1; i < start + size; ++i) {
    Data* present_num = a[i];
    int j = i - 1;
    for (; j >= start; --j) {
      if (!sorting_by) {
	if (*present_num < *a[j]) {
	  a[j + 1] = a[j];
	}
	else {
	  a[j + 1] = present_num;
	  goto end_first_loop;
	}
      }
      // Sorting by first name
      else if (sorting_by == 1) {
	if (present_num->firstName < a[j]->firstName) {
	  a[j + 1] = a[j];
	}
	else {
	  a[j + 1] = present_num;
	  goto end_first_loop;
	}	
      }
      // Sorting by last name
      else if (sorting_by == 2) {
	if (present_num->lastName < a[j]->lastName) {
	  a[j + 1] = a[j];
	}
	else {
	  a[j + 1] = present_num;
	  goto end_first_loop;
	}	
      }
      else if (sorting_by == 3) {
	if (present_num->ssn < a[j]->ssn) {
	  a[j + 1] = a[j];
	}
	else {
	  a[j + 1] = present_num;
	  goto end_first_loop;
	}		
      }
    }
    a[start] = present_num;
  end_first_loop:
    ;
  }
}

void merge_sort(int start, int size, int sorting_by) {
  // Base case
  if (size < SORT_BASE) {
    insertion_sort(start, size, sorting_by);
    return;
  }  
  /*
    if (size == 1) {
    return;
    }
  */

  // Dividing the problem into halves
  merge_sort(start, size / 2, sorting_by);
  merge_sort(start + (size / 2), size - (size / 2), sorting_by);

  // Merging
  int i = start, j = start + (size / 2), k = 0;
  Data* b[size] = {NULL};
  while (i < start + (size / 2) && j < start + size) {
    if (!sorting_by) {
      if (*a[j] < *a[i]) {
	b[k] = a[j];
	++j;
	++k;
      }
      else {
	b[k] = a[i];
	++i;
	++k;
      }
    }
    // Sorting by first_name
    else if (sorting_by == 1) {
      if (a[j]->firstName < a[i]->firstName) {
	b[k] = a[j];
	++j;
	++k;
      }
      else {
	b[k] = a[i];
	++i;
	++k;
      }      
    }
    // Sorting by last_name
    else if (sorting_by == 2) {
      if (a[j]->lastName < a[i]->lastName) {
	b[k] = a[j];
	++j;
	++k;
      }
      else {
	b[k] = a[i];
	++i;
	++k;
      }            
    }
    // Sorting by SSN
    else if (sorting_by == 3) {
      if (a[j]->ssn < a[i]->ssn) {
	b[k] = a[j];
	++j;
	++k;
      }
      else {
	b[k] = a[i];
	++i;
	++k;
      }            
    }
  }
  if (i == start + (size / 2)) {
    while (j < start + size) {
      b[k] = a[j];
      ++j;
      ++k;
    }
  }
  else if (j == start + size) {
    while (i < start + (size / 2)) {
      b[k] = a[i];
      ++i;
      ++k;
    }
  }
  
  for (int count = 0; count < size; ++count) {
    a[start + count] = b[count];
  }
}

void bubble_sort(int size) {
  for (int i = 1; i < size; ++i) {
    bool swap = false;
    for (int j = 0; j < size - i; ++j) {
      if (*a[j + 1] < *a[j]) {
	Data* temp = a[j];
	a[j] = a[j + 1];
	a[j + 1] = temp;
	swap = true;
      }
    }
    if (!swap) {
      break;
    }
  }
}

void selection_sort(int size) {
  for (int j = 0; j < size; ++j) {
    int i = 0, max_index = 0;
    Data* max = a[0];
    for (; i < size - j; ++i) {
      if (*max < *a[i]) {
	max = a[i];
	max_index = i;
      }
    }
    a[max_index] = a[--i];
    a[i] = max;
  }
}

/*
  const int MAX_NUM = 999999999;
  bool b[MAX_NUM + 1] = {0};

  void counting_sort(int arr[], int n) {
  if (n < 1) {
  return;
  }
  for (int i = 0; i < n; ++i) {
  b[arr[i]] = 1;
  }
  for (int i = 0, k = 0; i <= MAX_NUM; ++i) {
  if (b[i]) {
  arr[k++] = i;
  }
  }
  return;
  }
*/

const int PASSES = 2;
const int VALUE_RANGE = 32000;
const int PER_BIN = 2 * (1000000 / VALUE_RANGE);
Data* bins[VALUE_RANGE][PER_BIN] = {{NULL}};

void lsd_radix_sort(int n) {

  for (int div_by_range = 0; div_by_range < PASSES; ++div_by_range) {
    for (int i = 0; i < n; ++i) {
      ///////////////////////////////////// Try to do string->int conversion just one time ///////////////////
      istringstream iss(a[i]->ssn);
      int value = 0;
      iss >> value;
      int temp_value = value / pow(VALUE_RANGE, div_by_range);
      int index = temp_value % VALUE_RANGE;
      int j = 0;
      for (; bins[index][j] != NULL; ++j) {
	;
      }
      bins[index][j] = a[i];
    }
    int k = 0;
    for (int i = 0; i < VALUE_RANGE; ++i) {
      for (int j = 0; j < PER_BIN; ++j) {
	if (bins[i][j] == NULL) {
	  break;
	}
	a[k++] = bins[i][j];
	bins[i][j] = NULL;
	
      }
    }
  }
}


