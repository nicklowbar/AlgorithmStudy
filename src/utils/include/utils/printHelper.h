#pragma once

#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

namespace utils {

template <typename T> std::string printVector(std::vector<T> &vec) {
  std::ostringstream oss;
  oss << "[";
  for (int i = 0; i < vec.size(); i++) {
    oss << vec[i];
    if (i < vec.size() - 1) {
      oss << ", ";
    }
  }
  oss << "]";
  return oss.str();
}

template <typename... Args> std::string printStack(std::stack<Args...> &stk) {
  std::string result = "[";
  std::stack<Args...> temp = stk;
  while (!temp.empty()) {
    result += std::to_string(temp.top());
    temp.pop();
    if (!temp.empty()) {
      result += ", ";
    }
  }
  result += "]";
  return result;
}
} // namespace utils
