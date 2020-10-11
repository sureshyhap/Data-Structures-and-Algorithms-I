// Suresh Yhap
// Prof. Carl Sable
// Data Strucures and Algorithms I
// Programming Assignment #1

// The program implements stacks and queues as derived
// classes of a linked list class called SimpleList.
// The same call to push will do different things based
// on whether the pointer calling the function was pointing
// to a stack or a queue. This is possible because the
// push function was declared to be virtual in the base
// class. Pop is also virtual but it has the same effect
// for stacks and queues. This is the principle of
// polymorphism and dynamic binding.

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <sstream>

// Abstract Base Class that will provide
// Linked List functionality that will
// be extended for Stacks and Queues
template <typename T>
class SimpleList {
public:
  // SimpleList Default Constructor
  SimpleList(const std::string& s = std::string());
  // SimpleList Destructor
  virtual ~SimpleList();
  // Retrieves name of SimpleList
  inline std::string get_name() const;
  // Retrieves size of SimpleList
  inline int get_size() const;
  // Pure virtual push to be implemented
  // in derived classes
  virtual void push(T data) = 0;
  // Pure virtual pop to be implemented
  // in derived classes
  virtual T pop() = 0;
protected:
  // Inserts a Node to the front of the list
  void insert_front(T data);
  // Inserts a Node to the end of the list
  void insert_end(T data);
  // Removes a Node from the front of the list
  // and returns its data
  T remove_front();
private:
  // Represents a single element of the linked
  // list with data and pointer to next node
  class Node {
  public:
    // Node Default Constructor
    Node(T d = T(), Node* n = nullptr);
    T data;
    Node* next;
  };
  std::string name;
  int size;
  Node* header, * trailer;
};

// Stack implemented as a linked list
// with LIFO capability
template <typename T>
class Stack : public SimpleList<T> {
public:
  // Stack Default Constructor
  Stack(const std::string& n = std::string());
  // Implementation of base class' push
  void push(T data);
  // Implementation of base class' pop
  T pop();
};

// Queue implemented as a linked list
// with FIFO capability
template <typename T>
class Queue : public SimpleList<T> {
public:
  // Queue Default Constructor
  Queue(const std::string& n = std::string());
  // Implementation of base class' push
  void push(T data);
  // Implementation of base class' pop
  T pop();
};

template <typename T>
SimpleList<T>::SimpleList(const std::string& s) : name(s), size(0) {
  // Declaring the tail sentinel node with default data
  // value and a null next pointer
  trailer = new Node(T(), nullptr);
  // Declaring the header sentinel node with default
  // data value and makes it point to the tail node
  header = new Node(T(), trailer);
}

template <typename T>
SimpleList<T>::~SimpleList() {
  Node* temp = header->next;
  while (temp != nullptr) {
    header->next = header->next->next;
    delete temp;
    temp = header->next;
  }
  header = nullptr;
  trailer = nullptr;
}

template <typename T>
inline std::string SimpleList<T>::get_name() const {
  return name;
}

template <typename T>
inline int SimpleList<T>::get_size() const {
  return size;
}

template <typename T>
void SimpleList<T>::insert_front(T data) {
  // Create a new node which points to what the head
  // sentinel node is pointing to
  Node* new_data_node = new Node(data, header->next);
  // If the header node was not pointing to anything
  // then this new node is the only element
  // and after inserting it it becomes both the first
  // and last nodes so both the header and the trailer
  // nodes should point to it
  if (header->next == nullptr) {
    // Tell trailer to point to new node
    trailer->next = new_data_node;
  }
  // Tell header to point to new node
  header->next = new_data_node;
  ++size;
}

template <typename T>
void SimpleList<T>::insert_end(T data) {
  // Create a new node which points to nothing
  Node* new_data_node = new Node(data, nullptr);
  // If trailer node was not pointing to anything
  // this new node will be the only node when added
  // and thus header should also point to it
  if (trailer->next == nullptr) {
    header->next = new_data_node;
  }
  // Tell the old last element to point to
  // the new node (if there was an old last element)
  else {
    trailer->next->next = new_data_node;
  }
  // Tell trailer to point to new node
  trailer->next = new_data_node;
  ++size;
}

template <typename T>
T SimpleList<T>::remove_front() {
  // If list is empty, return default value of type
  if (header->next == nullptr) {
    return T();
  }
  // If the sentinel nodes point to the same
  // thing at this point then there is only
  // one element in the list
  bool only_one_node = (header->next == trailer->next ? true : false);
  // Saving the data of the first node
  T temp_data = header->next->data;
  // Saving a pointer to the node
  // up for deletion for later
  Node* temp = header->next;
  // Tell header to point to whatever the node
  // up for deletion was pointing to
  header->next = temp->next;
  // If there was only one node
  // before deletion, deletion will
  // affect the trailer node as well
  // as the header node
  if (only_one_node) {
    trailer->next = nullptr;
  }
  // Free the memory of the node up for deletion
  delete temp;
  --size;
  // Return the data of the deleted node
  return temp_data;
}

template <typename T>
SimpleList<T>::Node::Node(T d, Node* n) : data(d), next(n) {
}

template <typename T>
Stack<T>::Stack(const std::string& n) : SimpleList<T>(n) {  
}

template <typename T>
void Stack<T>::push(T data) {
  // Stacks will push from same side they pop from
  // so here they push to the front
  this->insert_front(data);
}

template <typename T>
T Stack<T>::pop() {
  // Pop from top of stack
  return this->remove_front();
}

template <typename T>
Queue<T>::Queue(const std::string& n) : SimpleList<T>(n) {
}

template <typename T>
void Queue<T>::push(T data) {
  // Queues will push from the opposite side they pop
  // from so here they push to the end
  this->insert_end(data);
}

template <typename T>
T Queue<T>::pop() {
  // Pop from front of queue
  return this->remove_front();
}

template <typename T>
// This function searches the designated list of SimpleList* for
// a stack or queue with a matching name.
// The second argument is a reference rather than a const reference because I
// could not work with regular iterators if it was a const&. I would
// need to use const iterators but I will eventually need to use
// the iterators to alter the SimpleList it corresponds to
typename std::list<SimpleList<T>*>::iterator find_s_or_q(const std::string& name, std::list<SimpleList<T>*>& list) {
  typename std::list<SimpleList<T>*>::iterator it = list.begin();
  for (; it != list.end(); ++it) {
    if ((*it)->get_name() == name) {
      return it;
    }
  }
  return it;
}

// This function parses the commands, executes them, and outputs to a file
void parse_and_process(const std::string& inf, const std::string& outf) {
  // Opening the input and output files
  std::ifstream infile(inf);
  std::ofstream outfile(outf);
  // The three lists of stacks and queues of
  // the specified type
  std::list<SimpleList<int>*> listSLi;
  std::list<SimpleList<double>*> listSLd;
  std::list<SimpleList<std::string>*> listSLs;
  std::string line;
  while (getline(infile, line)) {
    outfile << "PROCESSING COMMAND: " << line << '\n';
    std::istringstream iss(line);
    // Considering the pops which only have two words
    // Command is to pop
    if (line[0] == 'p' && line[1] == 'o') {
      std::string s1, s2;
      // Extracting the two individual words
      iss >> s1;
      iss >> s2;
      // The SimpleList is one of integers
      if (s2[0] == 'i') {
	std::list<SimpleList<int>*>::iterator it = find_s_or_q(s2, listSLi);
	// If the name was not found
	if (it == listSLi.end()) {
	  outfile << "ERROR: This name does not exist!" << '\n';
	  continue;
	}
	// If the size of the SimpleList is zero
	if ((*it)->get_size() == 0) {
	  outfile << "ERROR: This list is empty!" << '\n';
	  continue;
	}
	// If passed above tests, valid pop possible
	outfile << "Value popped: " << (*it)->pop() << '\n';
      }
      else if (s2[0] == 'd') {
	std::list<SimpleList<double>*>::iterator it = find_s_or_q(s2, listSLd);
	// If the name was not found
	if (it == listSLd.end()) {
	  outfile << "ERROR: This name does not exist!" << '\n';
	  continue;
	}
	// If the size of the SimpleList is zero
	if ((*it)->get_size() == 0) {
	  outfile << "ERROR: This list is empty!" << '\n';
	  continue;
	}
	// If passed above tests, valid pop possible
	outfile << "Value popped: " << (*it)->pop() << '\n';
      }
      else if (s2[0] == 's') {
	std::list<SimpleList<std::string>*>::iterator it = find_s_or_q(s2, listSLs);
	// If the name was not found
	if (it == listSLs.end()) {
	  outfile << "ERROR: This name does not exist!" << '\n';
	  continue;
	}
	// If the size of the SimpleList is zero
	if ((*it)->get_size() == 0) {
	  outfile << "ERROR: This list is empty!" << '\n';
	  continue;
	}
	// If passed above tests, valid pop possible
	outfile << "Value popped: " << (*it)->pop() << '\n';
      }
    }
    // Considering create and push which have three "words"
    else {
      std::string s1, s2, s3;
      iss >> s1;
      iss >> s2;
      iss >> s3;
      // Command is to create
      if (s1 == "create") {
	// The SimpleList is one of integers
	if (s2[0] == 'i') {
	  // If name has been found in list of SimpleList*
	  if (find_s_or_q(s2, listSLi) != listSLi.end()) {
	    outfile << "ERROR: This name already exists!" << '\n';
	    continue;
	  }
	  SimpleList<int>* pSLi;
	  if (s3 == "stack") {
	    // Create stack of integers
	    pSLi = new Stack<int>(s2);
	    // Push to collection of stacks and queues
	    listSLi.push_front(pSLi);
	  }
	  else if (s3 == "queue") {
	    // Create queue of integers
	    pSLi = new Queue<int>(s2);
	    // Push to collection of stacks and queues
	    listSLi.push_front(pSLi);
	  }
	}
	// The SimpleList is one of doubles
	else if (s2[0] == 'd') {
	  // If name has been found in list of SimpleList*
	  if (find_s_or_q(s2, listSLd) != listSLd.end()) {
	    outfile << "ERROR: This name already exists!" << '\n';
	    continue;
	  }
	  SimpleList<double>* pSLd;
	  if (s3 == "stack") {
	    // Create stack of doubles
	    pSLd = new Stack<double>(s2);
	    // Push to collection of stacks and queues
	    listSLd.push_front(pSLd);
	  }
	  else if (s3 =="queue") {
	    // Create queue of doubles
	    pSLd = new Queue<double>(s2);
	    // Push to collection of stacks and queues
	    listSLd.push_front(pSLd);
	  }
	}
	// The SimpleList is one of strings
	else if (s2[0] == 's') {
	  // It name has been found in list of SimpleList*
	  if (find_s_or_q(s2, listSLs) != listSLs.end()) {
	    outfile << "ERROR: This name already exists!" << '\n';
	    continue;	    
	  }
	  SimpleList<std::string>* pSLs;
	  if (s3 == "stack") {
	    // Create stack of strings
	    pSLs = new Stack<std::string>(s2);
	    // Push to collection of stacks and queues
	    listSLs.push_front(pSLs);
	  }
	  else if (s3 == "queue") {
	    // Create queue of strings
	    pSLs = new Queue<std::string>(s2);
	    // Push to collection of stacks and queues
	    listSLs.push_front(pSLs);
	  }
	}
      }
      // COMMAND50 is to push
      else if (s1 == "push") {
	// The SimpleList is one of integers
	if (s2[0] == 'i') {
	  std::list<SimpleList<int>*>::iterator it = find_s_or_q(s2, listSLi);
	  // If name has not been found in the list
	  if (it == listSLi.end()) {
	    outfile << "ERROR: This name does not exist!" << '\n';
	    continue;
	  }
	  // Now need to convert the string representation of the
	  // integer to an actual integer
	  std::istringstream value(s3);
	  int val = 0;
	  value >> val;
	  // Now push val onto either a stack or a queue
	  // The correct push will be chosen based on
	  // which class type the pointer points to since
	  // it was made to be virtual. This is
	  // polymorphism
	  (*it)->push(val);
	}
	// The SimpleList is one of doubles
	else if (s2[0] == 'd') {
	  std::list<SimpleList<double>*>::iterator it = find_s_or_q(s2, listSLd);
	  // If name has not been found in the list
	  if (it == listSLd.end()) {
	    outfile << "ERROR: This name does not exist!" << '\n';
	    continue;
	  }
	  // Now need to convert the string representation of the
	  // double to an actual double
	  std::istringstream value(s3);
	  double val = 0.0;
	  value >> val;
	  // Now push val onto either a stack or a queue
	  // The correct push will be chosen based on
	  // which class type the pointer points to since
	  // it was made to be virtual. This is
	  // polymorphism
	  (*it)->push(val);
	}
	// The SimpleList is one of strings
       	else if (s2[0] == 's') {
	  std::list<SimpleList<std::string>*>::iterator it = find_s_or_q(s2, listSLs);
	  // If name has not been found in the list
	  if (it == listSLs.end()) {
	    outfile << "ERROR: This name does not exist!" << '\n';
	    continue;
	  }
	  // Now push val onto either a stack or a queue
	  // The correct push will be chosen based on
	  // which class type the pointer points to since
	  // it was made to be virtual. This is
	  // polymorphism
	  (*it)->push(s3);
	}
      }
    }
  }
}

int main(int argc, char* argv[]) {
  std::cout << "Enter name of input file: ";
  std::string in;
  std::cin >> in;  
  std::cout << "Enter name of output file: ";
  std::string out;
  std::cin >> out;
  parse_and_process(in, out);
  return 0;
}
