#include <iostream>

template <typename T>
class Stack {
  template <typename T2>
  friend std::ostream& operator<<(std::ostream& os, const Stack<T2>& s);
public:
  Stack(int cap = default_cap);
  Stack(const Stack& other);
  ~Stack();
  Stack<T>& operator=(const Stack& other);
  void push(const T& element);
  inline void pop();
  inline T top();
  inline bool is_empty() const;
  inline int get_size() const;
  inline int get_cap() const;
  void print() const;
private:
  T* data;
  int size, capacity;
  static constexpr int default_cap = 4;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& s) {
  // Display stack from top to bottom
  for (int i {s.size - 1}; i >= 0; --i) {
    os << s.data[i] << '\n';
  }
  return os;
}

template <typename T>
Stack<T>::Stack(int cap) : data(new T[cap]), size(0), capacity(cap) {
  
}

template <typename T>
Stack<T>::Stack(const Stack& other) : data(new T[other.capacity]), size(other.size), capacity(other.capacity) {
  for (int i {0}; i < size; ++i) {
    data[i] = {other.data[i]};
  }
}

template <typename T>
Stack<T>::~Stack() {
  delete [] data;
  data = {nullptr};
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& other) {
  data = {new T[other.capacity]};
  size = {other.size};
  capacity = {other.capacity};
  for (int i {0}; i < size; ++i) {
    data[i] = {other.data[i]};
  }
}

template <typename T>
void Stack<T>::push(const T& element) {
  // If adding an element would exceed capacity, double it first
  if (size + 1 > capacity) {
    T* temp {new T[capacity * 2]};
    for (int i {0}; i < size; ++i) {
      temp[i] = {data[i]};
    }
    capacity *= 2;
    delete [] data;
    data = {nullptr};
    data = temp;
  }
  // At this point capacity is sufficient to hold more elements
  data[size++] = {element};
}

template <typename T>
inline void Stack<T>::pop() {
  // Pop only if there is a nonzero amount of elements
  if (size) {
    --size;
  }
}

template <typename T>
inline T Stack<T>::top() {
  try {
    if (size) {
      return data[size - 1];
    }
    else {
      // No top element
      throw std::runtime_error("Empty stack");
    }
  }
  catch (const std::runtime_error& err) {
    std::cerr << err.what() << '\n';
    // Returns default value of given type
    return T();
  }
}

template <typename T>
inline bool Stack<T>::is_empty() const {
  return not size;
}

template <typename T>
inline int Stack<T>::get_size() const {
  return size;
}

template <typename T>
inline int Stack<T>::get_cap() const {
  return capacity;
}

template <typename T>
void Stack<T>::print() const {
  std::cout << '\n' << *this << '\n';
}

int main(int argc, char* argv[]) {
  Stack<int> s;
  std::cout << s.get_size() << ' ' << s.get_cap() << '\n';
  s.print();
  s.pop();
  s.top();
  std::cout << s.is_empty() << std::endl;
  s.push(5);
  std::cout << s.get_size() << ' ' << s.get_cap() << '\n';
  s.print();
  std::cout << s.is_empty();
  std::cout << "\n\n";
  s.push(10);
  std::cout << s.get_size() << ' ' << s.get_cap() << '\n';
  s.print();
  s.push(15);
  std::cout << s.get_size() << ' ' << s.get_cap() << '\n';
  s.print();
  s.push(20);
  std::cout << s.get_size() << ' ' << s.get_cap() << '\n';
  s.print();
  s.push(25);
  std::cout << s.get_size() << ' ' << s.get_cap() << '\n';
  s.print();
  std::cout << s.top() << '\n';
  Stack<int> s2(s);
  std::cout << s2.get_size() << ' ' << s2.get_cap() << '\n';
  s2.print();
  Stack<int> s3;
  s3 = {s2};
  s3.push(1000);
  std::cout << s3.get_size() << ' ' << s3.get_cap() << '\n';
  s3.print();  
  return 0;
}
