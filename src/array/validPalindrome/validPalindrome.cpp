#include <utils/logHelper.h>
#include <utils/printHelper.h>

#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

/*
A phrase is a palindrome if, after converting all uppercase letters into
lowercase letters and removing all non-alphanumeric characters, it reads the
same forward and backward. Alphanumeric characters include letters and numbers.

Given a string s, return true if it is a palindrome, or false otherwise.



Example 1:

Input: s = "A man, a plan, a canal: Panama"
Output: true
Explanation: "amanaplanacanalpanama" is a palindrome.

Example 2:

Input: s = "race a car"
Output: false
Explanation: "raceacar" is not a palindrome.

Example 3:

Input: s = " "
Output: true
Explanation: s is an empty string "" after removing non-alphanumeric characters.
Since an empty string reads the same forward and backward, it is a palindrome.



Constraints:

    1 <= s.length <= 2 * 105
    s consists only of printable ASCII characters.


*/

/**
 * @brief Given an array of integers return if the array contains a duplicate.
 */
bool validPalindrome(std::string &input) {
  auto left = 0UL;
  auto right = input.length() - 1;

  while (left < right) {
    // iterate to next alphanumeric char:
    while (!std::isalnum(input[left])) {
      left++;
    }
    while (!std::isalnum(input[right])) {
      right--;
    }

    // std::cout << "Checking: input[" << left << "] (" << input[left]
    //           << ") == input[" << right << "] (" << input[right] << ")"
    //           << std::endl;

    // check equivalence
    if (!(std::tolower(input[left]) == std::tolower(input[right]))) {
      return false;
    }

    left++;
    right--;
  }
  return true;
}

int main() {
  // TODO: Add support for defining test cases in a more succinct wa.
  {
    std::string input = "A man, a plan, a canal: Panama";
    bool expected = true;
    cout << "Input: " << input << endl;
    cout << "Output: " << validPalindrome(input) << " Expected: " << expected
         << endl;
  }

  {
    std::string input = "race a car";
    bool expected = false;
    cout << "Input: " << input << endl;
    cout << "Output: " << validPalindrome(input) << " Expected: " << expected
         << endl;
  }

  {
    std::string input = " ";
    bool expected = true;
    cout << "Input: " << input << endl;
    cout << "Output: " << validPalindrome(input) << " Expected: " << expected
         << endl;
  }
}