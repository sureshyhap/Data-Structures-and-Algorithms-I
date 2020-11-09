#include <iostream>
#include <string>
#include <stack>
#include <sstream>

double eval_postfix(std::string expression);

int main(int argc, char* argv[]) {
  std::cout << "Enter an expression: ";
  std::string exp;
  std::getline(std::cin, exp);
  std::cout << eval_postfix(exp) << '\n';
  return 0;
}

double eval_postfix(std::string expression) {
  std::stack<double> values;
  std::istringstream iss(expression);
  std::string oper;
  while (iss >> oper) {
    try {
      if (oper == "+" or oper == "-" or oper == "*" or oper == "/") {
	if (values.size() < 2) {
	  throw std::runtime_error("Unbalanced expression.");
	}
	double second_operand = {values.top()};
	values.pop();
	double first_operand = {values.top()};
	values.pop();
	double result = {};
	switch (oper.at(0)) {
	case '+':
	  result = {first_operand + second_operand};
	  break;
	case '-':
	  result = {first_operand - second_operand};
	  break;
	case '*':
	  result = {first_operand * second_operand};
	  break;
	case '/':
	  result = {first_operand / second_operand};
	  break;
	}
	values.push(result);
      }
      else {
	std::istringstream num(oper);
	double value = {};
	num >> value;
	values.push(value);
      }
    }
    catch (const std::runtime_error& re) {
      std::cerr << re.what() << '\n';
      return 0;
    }
  }
  try {
    if (values.size() == 1) {
      return values.top();
    }
    else {
      throw std::runtime_error("Unbalanced expression.");
    }
  }
  catch (const std::runtime_error& re) {
    std::cerr << re.what() << '\n';
    return 0;
  }
}
