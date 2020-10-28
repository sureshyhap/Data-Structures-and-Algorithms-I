#include <iostream>
#include <stack>
#include <string>

bool is_balanced(const std::string& expression);

int main(int argc, char* argv[]) {
  std::cout << "Enter an expression: ";
  std::string exp;
  std::cin >> exp;
  bool is_bal = is_balanced(exp);
  std::cout << (is_bal ? "It is balanced\n" : "It is not balanced\n");
  return 0;
}

///////// Balances strings with only (), {}, and [] /////////////
bool is_balanced(const std::string& expression) {
  std::stack<char> check_balanced;
  for (std::string::const_iterator cit {expression.cbegin()};
       cit != expression.end(); ++cit) {
    // Is left marker
    if (*cit == '(' or *cit == '[' or *cit == '{') {
      check_balanced.push(*cit);
    }
    // Is right marker
    else if (*cit == ')' or *cit == ']' or *cit == '}') {
      if (*cit == ')') {
	// If matching left marker, then pop and continue
	if (check_balanced.top() == '(') {
	  check_balanced.pop();
	}
	// Otherwise not balanced
	else {
	  return false;
	}
      }
      else if (*cit == ']') {
	// If matching left marker, then pop and continue
	if (check_balanced.top() == '[') {
	  check_balanced.pop();
	}
	// Otherwise not balanced
	else {
	  return false;
	}
      }
      else if (*cit == '}') {
	// If matching left marker, then pop and continue
	if (check_balanced.top() == '{') {
	  check_balanced.pop();
	}
	// Otherwise not balanced
	else {
	  return false;
	}
      }
    }
  }
  // If all matched up and thus empty stack, is balanced
  if (check_balanced.empty()) {
    return true;
  }
  // If non-empty stack, then there was a marker that
  // was not paired with another so not balanced
  else {
    return false;
  }
}
