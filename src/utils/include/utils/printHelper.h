#pragma once

#include <string>
#include <vector>
#include <stack>
#include <queue>

namespace utils
{
    template <typename...Args>
    std::string printVector(std::vector<Args...>& vec)
    {
        std::string result = "[";
        for (int i = 0; i < vec.size(); i++) {
            result += std::to_string(vec[i]);
            if (i < vec.size() - 1) {
                result += ", ";
            }
        }
        result += "]";
        return result;
    }

    template <typename...Args>
    std::string printStack(std::stack<Args...>& stk)
    {
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
}
