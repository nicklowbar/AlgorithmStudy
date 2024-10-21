#include "utils/printHelper.h"

std::string printVector(std::vector<int>& vec)
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