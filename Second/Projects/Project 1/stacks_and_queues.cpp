// Suresh Yhap
// This program implements and manipulates the stack and queue data structures
// which are derived from a linked list class. All the stacks and queues are
// effectively stored in a list and their operations implement pure virtual
// functions like push and pop from their parent linked list class. The correct
// functions are called because of polymorphism.

#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

// A linked list data type
template <typename T>
class Simple_list {  
public:
  // Constructs empty list with given name
  Simple_list(const std::string& name);
  // Frees all the nodes in the list
  virtual ~Simple_list();
  // Pure virtual push function implemented in stack class and queue class
  virtual void push(const T& data) = 0;
  // Pure virtual pop function implemented in stack class and queue class
  virtual T pop() = 0;
  // Retrieves name of list
  std::string get_name() const;
  // Checks if list is empty
  bool is_empty() const;  
protected:  
  // Insert an element with given data to the front of the list
  void insert_front(const T& data);
  // Insert an element with given data to the back of the list
  void insert_back(const T& data);
  // Remove the element that is at the front of the list
  T remove_front();
private:
  // Base element of the linked list
  class Node {    
  public:
    // A Node will have data and a pointer to the next node
    Node(const T& d = T(), Node* n = nullptr);
    T data;
    Node* next;    
  };
  Node* first, * last;
  std::string name;
};

// A stack data type that derives from the linked list class
template <typename T>
class Stack : public Simple_list<T> {
public:
  Stack(const std::string& name);
  void push(const T& data);
  T pop();  
};

// A queue data type that derives from the linked list class
template <typename T>
class Queue : public Simple_list<T> {
public:
  Queue(const std::string& name);
  void push(const T& data);
  T pop();
};


template <typename T>
Simple_list<T>::Simple_list(const std::string& name) : first(nullptr), last(nullptr), name(name) {
  
}

template <typename T>
Simple_list<T>::~Simple_list() {
  // While there is at least one element, continue deleting. Deleting first to last
  while (first) {
    Node* temp = {first};
    first = {first->next};
    delete temp;
  }
}

template <typename T>
Simple_list<T>::Node::Node(const T& d, Node* n) : data(d), next(n) {
  
}

template <typename T>
void Simple_list<T>::insert_front(const T& data) {
  // If list is empty, both first and last will point to it
  if (is_empty()) {
    Node* p = {new Node(data, nullptr)};
    first = {last = {p}};
  }
  // Otherwise, the node will point to the previous first and first
  // will point to it
  else {
    Node* p = {new Node(data, first)};
    first = {p};
  }
}

template <typename T>
void Simple_list<T>::insert_back(const T& data) {
  // If list is empty, both first and last will point to it
  if (is_empty()) {
    Node* p = {new Node(data, nullptr)};
    first = {last = {p}};
  }
  // Otherwise, the previous last node will point to it and last
  // will point to it
  else {
    Node* p = {new Node(data, nullptr)};
    last->next = {p};
    last = {p};
  }
}

template <typename T>
T Simple_list<T>::remove_front() {
  // Nothing to remove
  if (is_empty()) {
    return T();
  }
  // Removal with only one element in list affects both first and last
  else if (first == last) {
    T data = {first->data};
    delete first;
    first = {last = {nullptr}};
    return data;
  }
  // Front removal otherwise only affects first. Bypass first node
  // and then delete it
  else {
    T data = {first->data};
    Node* temp = {first};
    first = {first->next};
    delete temp;
    return data;
  }
}

template <typename T>
std::string Simple_list<T>::get_name() const {
  return name;
}

template <typename T>
bool Simple_list<T>::is_empty() const {
  // If these pointers are both nullptr, then list is empty
  if (!first and !last) {
    return true;
  }
  else {
    return false;
  }
}

template <typename T>
Stack<T>::Stack(const std::string& name) : Simple_list<T>(name) {
  
}

template <typename T>
void Stack<T>::push(const T& data) {
  // Stack push to top of list
  this->insert_front(data);
}

template <typename T>
T Stack<T>::pop() {
  // Stack pop from top of list
  return this->remove_front();
}

template <typename T>
Queue<T>::Queue(const std::string& name) : Simple_list<T>(name) {

}

template <typename T>
void Queue<T>::push(const T& data) {
  // Queue push to end of list
  this->insert_back(data);
}

template <typename T>
T Queue<T>::pop() {
  // Queue pop from beginning of list
  return this->remove_front();
}

// Parse commands from input and then process those commands which create or
// alter the given stack or queue
void parse_and_process(std::ifstream& infile, std::ofstream& outfile);

int main(int argc, char* argv[]) {
  std::cout << "Enter name of input file: ";
  std::string input_file;
  std::cin >> input_file;
  std::cout << "Enter name of output file: ";
  std::string output_file;
  std::cin >> output_file;  
  std::ifstream infile(input_file);
  std::ofstream outfile(output_file);
  parse_and_process(infile, outfile);
  infile.close();
  outfile.close();
  return 0;
}

void parse_and_process(std::ifstream& infile, std::ofstream& outfile) {
  // The lists that will contain pointers to all the stacks and queues created
  std::list<Simple_list<int>*> list_sl_i;
  std::list<Simple_list<double>*> list_sl_d;
  std::list<Simple_list<std::string>*> list_sl_s;
  std::string line;
  while (std::getline(infile, line)) {
    outfile << "PROCESSING COMMAND: " << line << '\n';
    std::string word;
    // Array of each word in a command
    std::vector<std::string> words;
    std::istringstream iss(line);
    while (iss >> word) {
      words.push_back(word);
    }    
    if (words.front() == "create") {
      // First letter of name is the type
      std::string name = {words.at(1)};
      bool is_already_in = {false};
      if (name.front() == 'i') {
	
	// Search for name in list
	for (std::list<Simple_list<int>*>::const_iterator cit = list_sl_i.cbegin();
	     cit != list_sl_i.cend(); ++cit) {
	  // If stack/queue corresponding to the the iterator is found with the matching
	  // name, then the name is already in the list
	  if ((*cit)->get_name() == name) {
	    is_already_in = {true};
	    break;
	  }
	}
	if (is_already_in) {
	  outfile << "ERROR: This name already exists!\n";
	  continue;
	}
	// Will point to a stack or queue
	Simple_list<int>* p_sl_i = {nullptr};
	// Create a stack with the given name
	if (words.back() == "stack") {
	  p_sl_i = {new Stack<int>(name)};
	}
	// Create a queue with the given name
	else if (words.back() == "queue") {
	  p_sl_i = {new Queue<int>(name)};
	}
	// Add the new stack/queue to the list of stacks/queues with the correct type
	list_sl_i.push_front(p_sl_i);
      }
      else if (name.front() == 'd') {
	// Search for name in list
	for (std::list<Simple_list<double>*>::const_iterator cit = list_sl_d.cbegin();
	     cit != list_sl_d.cend(); ++cit) {
	  // If stack/queue corresponding to the the iterator is found with the matching
	  // name, then the name is already in the list
	  if ((*cit)->get_name() == name) {
	    is_already_in = {true};
	    break;
	  }
	}
	if (is_already_in) {
	  outfile << "ERROR: This name already exists!\n";
	  continue;
	}
	// Will point to a stack or queue
	Simple_list<double>* p_sl_d = {nullptr};
	// Create a stack with the given name
	if (words.back() == "stack") {
	  p_sl_d = {new Stack<double>(name)};
	}
	// Create a queue with the given name
	else if (words.back() == "queue") {
	  p_sl_d = {new Queue<double>(name)};
	}
	// Add the new stack/queue to the list of stacks/queues with the correct type
	list_sl_d.push_front(p_sl_d);
      }
      else if (name.front() == 's') {
	// Search for name in list
	for (std::list<Simple_list<std::string>*>::const_iterator cit = list_sl_s.cbegin();
	     cit != list_sl_s.cend(); ++cit) {
	  // If stack/queue corresponding to the the iterator is found with the matching
	  // name, then the name is already in the list
	  if ((*cit)->get_name() == name) {
	    is_already_in = {true};
	    break;
	  }
	}
	if (is_already_in) {
	  outfile << "ERROR: This name already exists!\n";
	  continue;
	}
	// Will point to a stack or queue
	Simple_list<std::string>* p_sl_s = {nullptr};
	// Create a stack with the given name
	if (words.back() == "stack") {
	  p_sl_s = {new Stack<std::string>(name)};
	}
	// Create a queue with the given name
	else if (words.back() == "queue") {
	  p_sl_s = {new Queue<std::string>(name)};
	}
	// Add the new stack/queue to the list of stacks/queues with the correct type
	list_sl_s.push_front(p_sl_s);
      }
    }
    else if (words.front() == "push") {
      std::string name = {words.at(1)};
      bool exists = {false};
      if (name.front() == 'i') {
	// Convert string to int
	std::istringstream iss(words.back());
	int value = {};
	iss >> value;
	// Search list of Simple_lists
	for (std::list<Simple_list<int>*>::iterator it = list_sl_i.begin();
	     it != list_sl_i.end(); ++it) {
	  // If found correct list, push value
	  if ((*it)->get_name() == name) {
	    exists = {true};
	    // Calls correct push because of polymorphism
	    (*it)->push(value);
	    break;
	  }
	}
	if (!exists) {
	  outfile << "ERROR: This name does not exist!\n";
	  continue;
	}
      }
      else if (name.front() == 'd') {
	// Convert string to double
	std::istringstream iss(words.back());
	double value = {};
	iss >> value;
	// Search list of Simple_lists
	for (std::list<Simple_list<double>*>::iterator it = list_sl_d.begin();
	     it != list_sl_d.end(); ++it) {
	  // If found correct list, push value
	  if ((*it)->get_name() == name) {
	    exists = {true};
	    // Calls correct push because of polymorphism
	    (*it)->push(value);
	    break;
	  }
	}
	if (!exists) {
	  outfile << "ERROR: This name does not exist!\n";
	  continue;
	}
      }
      else if (name.front() == 's') {
	std::string value = {words.back()};
	// Search list of Simple_lists
	for (std::list<Simple_list<std::string>*>::iterator it = list_sl_s.begin();
	     it != list_sl_s.end(); ++it) {
	  // If found correct list, push value
	  if ((*it)->get_name() == name) {
	    exists = {true};
	    // Calls correct push because of polymorphism
	    (*it)->push(value);
	    break;
	  }
	}
	if (!exists) {
	  outfile << "ERROR: This name does not exist!\n";
	  continue;
	}
      }
    }
    else if (words.front() == "pop") {
      std::string name = {words.back()};
      bool exists = {false}, empty = {false};
      if (name.front() == 'i') {
	for (std::list<Simple_list<int>*>::iterator it = list_sl_i.begin();
	     it != list_sl_i.end(); ++it) {
	  if ((*it)->get_name() == name) {
	    exists = {true};
	    // If found but empty, can't pop
	    if ((*it)->is_empty()) {
	      empty = {true};
	      break;
	    }
	    // Calls correct pop because of polymorphism
	    outfile << "Value popped: " << (*it)->pop() << '\n';
	    break;
	  }
	}
	if (empty) {
	  outfile << "ERROR: This list is empty!\n";
	  continue;
	}
	if (!exists) {
	  outfile << "ERROR: This name does not exist!\n";
	  continue;
	}
      }
      else if (name.front() == 'd') {
	for (std::list<Simple_list<double>*>::iterator it = list_sl_d.begin();
	     it != list_sl_d.end(); ++it) {
	  if ((*it)->get_name() == name) {
	    exists = {true};
	    // If found but empty, can't pop
	    if ((*it)->is_empty()) {
	      empty = {true};
	      break;
	    }
	    // Calls correct pop because of polymorphism
	    outfile << "Value popped: " << (*it)->pop() << '\n';
	    break;
	  }
	}
	if (empty) {
	  outfile << "ERROR: This list is empty!\n";
	  continue;
	}
	if (!exists) {
	  outfile << "ERROR: This name does not exist!\n";
	  continue;
	}	
      }
      else if (name.front() == 's') {
	for (std::list<Simple_list<std::string>*>::iterator it = list_sl_s.begin();
	     it != list_sl_s.end(); ++it) {
	  if ((*it)->get_name() == name) {
	    exists = {true};
	    // If found but empty, can't pop
	    if ((*it)->is_empty()) {
	      empty = {true};
	      break;
	    }
	    // Calls correct pop because of polymorphism
	    outfile << "Value popped: " << (*it)->pop() << '\n';
	    break;
	  }
	}
	if (empty) {
	  outfile << "ERROR: This list is empty!\n";
	  continue;
	}
	if (!exists) {
	  outfile << "ERROR: This name does not exist!\n";
	  continue;
	}
      }
    }  
  }
}

