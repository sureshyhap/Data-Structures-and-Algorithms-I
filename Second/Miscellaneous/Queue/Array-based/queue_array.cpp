#include <iostream>

template <typename T>
class Queue {
  template <typename T2>
  friend std::ostream& operator<<(std::ostream& os, const Queue<T2>& q);
public:
  Queue(int cap = default_cap);
  Queue(const Queue& other);
  ~Queue();
  Queue& operator=(const Queue& other);
  void push(const T& element);
  inline void pop();
  inline T front() const;
  inline T back() const;
  inline bool is_empty() const;
  inline int get_size() const;
  inline int get_cap() const;
  void print() const;
private:
  T* data;
  int first, last;
  int size, capacity;
  constexpr static int default_cap = 4;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Queue<T>& q) {
  for (int i {0}; i < q.size; ++i) {
    os << q.data[(i + q.first) % q.capacity] << ' ';
  }
  return os;
}

template <typename T>
Queue<T>::Queue(int cap) : first(0), last(-1), size(0), capacity(cap), data(new T[cap]) {
  
}

template <typename T>
Queue<T>::Queue(const Queue& other) : first(other.first), last(other.last), size(other.size), capacity(other.capacity), data(new T[capacity]) {
  for (int i {0}; i < size; ++i) {
    data[i] = {other.data[i]};
  }
}

template <typename T>
Queue<T>::~Queue() {
  delete [] data;
  data = {nullptr};
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue& other) {
  first = {other.first};
  last = {other.last};
  size = {other.size};
  capacity = {other.capacity};
  data = new T[capacity];
  for (int i {0}; i < size; ++i) {
    data[i] = other.data[i];
  }
}

template <typename T>
void Queue<T>::push(const T& element) {
  if (size + 1 > capacity) {
    T* temp = new T[capacity * 2];
    for (int i {0}; i < size; ++i) {
      temp[i] = {data[(i + first) % capacity]};
    }
    first = {0};
    last = {size - 1};
    capacity *= 2;
    delete [] data;
    data = {nullptr};
    data = {temp};
  }
  last = (last + 1) % capacity;
  data[last] = {element};
  ++size;
}

template <typename T>
inline void Queue<T>::pop() {
  if (size) {
    first = (first + 1) % capacity;
    --size;
  }
}

template <typename T>
inline T Queue<T>::front() const {
  try {
    if (size) {
      return data[first];
    }
    else {
      throw std::runtime_error("Empty queue");
    }
  }
  catch (const std::runtime_error& err) {
    std::cerr << err.what() << '\n';
    // Returns default value of given type
    return T();
  }
}

template <typename T>
inline T Queue<T>::back() const {
  try {
    if (size) {
      return data[last];
    }
    else {
      throw std::runtime_error("Empty queue");
    }
  }
  catch (const std::runtime_error& err) {
    std::cerr << err.what() << '\n';
    // Returns default value of given type
    return T();
  }
  
}

template <typename T>
inline bool Queue<T>::is_empty() const {
  return not size;
}

template <typename T>
inline int Queue<T>::get_size() const {
  return size;
}

template <typename T>
inline int Queue<T>::get_cap() const {
  return capacity;
}

template <typename T>
void Queue<T>::print() const {
  std::cout << *this << '\n';
}

int main(int argc, char* argv[]) {
  Queue<int> q;
  std::cout << q.get_size() << ' ' << q.get_cap() << '\n';
  q.print();
  q.pop();
  std::cout << q.get_size() << ' ' << q.get_cap() << '\n';
  q.print();
  q.push(5);
  std::cout << q.get_size() << ' ' << q.get_cap() << '\n';
  q.print();
  q.push(10);
  std::cout << q.get_size() << ' ' << q.get_cap() << '\n';
  q.print();
  q.push(15);
  std::cout << q.get_size() << ' ' << q.get_cap() << '\n';
  q.print();
  q.push(20);
  std::cout << q.get_size() << ' ' << q.get_cap() << '\n';
  q.print();
  q.push(25);
  std::cout << q.get_size() << ' ' << q.get_cap() << '\n';
  q.print();
  q.pop();
  std::cout << q.get_size() << ' ' << q.get_cap() << '\n';
  q.print();
  q.pop();
  q.pop();
  q.pop();
  std::cout << q.get_size() << ' ' << q.get_cap() << '\n';
  q.print();
  q.push(1);
  q.push(2);
  q.push(3);
  q.push(4);
  q.push(5);
  q.push(6);
  std::cout << q.get_size() << ' ' << q.get_cap() << '\n';
  q.print();
  std::cout << q.front() << ' ' << q.back() << '\n';
  return 0;
}
