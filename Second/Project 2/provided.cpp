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

const int T1_CUTOFF = 102000;
bool operator<(const Data& d1, const Data& d2);
int detect_case(const std::list<Data*>& l);

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
    if (!(**cit < **std::next(cit))) {
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
  // Fill this in
  switch (detect_case(l)) {
  case 1:
    std::cout << '1' << '\n';
    break;
  case 2:
    std::cout << '2' << '\n';
    break;
  case 3:
    std::cout << '3' << '\n';
    break;
  case 4:
    std::cout << '4' << '\n';
    break;
  }
}
