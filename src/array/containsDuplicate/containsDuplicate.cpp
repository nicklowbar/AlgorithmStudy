#include <utils/logHelper.h>
#include <utils/printHelper.h>

#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

/*
Given an array of integers, determine if there are any duplicates in the array.

Example 1:

Input: nums = [1,2,3,2]
Output: true
Explanation: The value 2 occurs twice in the array.

Example 2:

Input: nums = [1,2,3,4]
Output: false
Explanation: There are no duplicates in the array.


Constraints:

    1 <= nums.length <= 100,000
    INT_MIN <= nums[i] < INT_MAX

*/

/**
 * @brief Given an array of integers return if the array contains a duplicate.
 */
bool containsDuplicate(vector<int> &nums) {
  std::unordered_set<int> seen;

  for (auto begin = std::begin(nums), end = std::end(nums); begin != end;) {
    int value = *begin++;
    if (seen.contains(value)) {
      return true;
    }
    seen.insert(value);
  }
  return false;
}

int main() {
  // TODO: Add support for defining test cases in a more succinct wa.
  {
    vector<int> nums = {1, 2, 3, 2};
    bool expected = true;
    cout << "Input: " << utils::printVector(nums) << endl;
    cout << "Output: " << containsDuplicate(nums) << " Expected: " << expected
         << endl;
  }

  {
    vector<int> nums = {1, 2, 3, 4};
    bool expected = false;
    cout << "Input: " << utils::printVector(nums) << endl;
    cout << "Output: " << containsDuplicate(nums) << " Expected: " << expected
         << endl;
  }

  {
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1};
    bool expected = true;
    cout << "Input: " << utils::printVector(nums) << endl;
    cout << "Output: " << containsDuplicate(nums) << " Expected: " << expected
         << endl;
  }
}