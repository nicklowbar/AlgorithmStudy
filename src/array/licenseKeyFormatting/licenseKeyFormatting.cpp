#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

/*
You are given a license key represented as a string s that consists of only alphanumeric characters and dashes. The string is separated into n + 1 groups by n dashes. You are also given an integer k.

We want to reformat the string s such that each group contains exactly k characters, except for the first group, which could be shorter than k but still must contain at least one character. Furthermore, there must be a dash inserted between two groups, and you should convert all lowercase letters to uppercase.

Return the reformatted license key.

 

Example 1:

Input: s = "5F3Z-2e-9-w", k = 4
Output: "5F3Z-2E9W"
Explanation: The string s has been split into two parts, each part has 4 characters.
Note that the two extra dashes are not needed and can be removed.

Example 2:

Input: s = "2-5g-3-J", k = 2
Output: "2-5G-3J"
Explanation: The string s has been split into three parts, each part has 2 characters except the first part as it could be shorter as mentioned above.

 

Constraints:

    1 <= s.length <= 105
    s consists of English letters, digits, and dashes '-'.
    1 <= k <= 104

*/

/**
 * @brief Given a string s and an integer k, reformat the string such that each group contains exactly k characters, except for the first group, which could be shorter than k but still must contain at least one character. Furthermore, there must be a dash inserted between two groups, and all lowercase letters should be converted to uppercase.
 */
string licenseKeyFormatting(string s, int k) {       
    string result = "";
    int numAlChars = 0;
    
    // First, count the number of alphanumeric characters in the input string
    for_each(s.begin(), s.end(), [&](char ch)
    {
        if(isalnum(ch))
        {
            numAlChars++;
        }
    });
    
    // Calculate the remainder of the number of alphanumeric characters divided by k
    
    int remainder = numAlChars % k; // remainder of the number of alphanumeric characters divided by k
    int counter = 0; // how many characters to process before inserting a '-'
    bool firstEncountered = false; // flag to indicate if the first alphanumeric character has been encountered
    
    for(int i = 0; i < s.size(); ++i){ // iterate through input string by character
        char ch = s[i];
        if (!isalnum(ch)) // skip non-alphanumeric characters
        {
            continue;
        }
        
        // if the first segment end has been encountered, append a hyphen
        if (!firstEncountered && remainder != 0 && counter == remainder ) 
        {
            result += '-';
            counter = 0;
            firstEncountered = true;
        }
        // otherwise every k characters, append a hyphen.
        else if( counter == k )
        {
            result += '-';
            counter = 0;
        }

        // convert to upper case.
        result += toupper(ch);
        counter++;
    }
    
    return result;
}

int main()
{
    string s = "5F3Z-2e-9-w";
    string expected_result = "5F3Z-2E9W";
    int k = 4;
    string result = licenseKeyFormatting(s, k);

    cout << "Result: " << result << ", Expected Result:" << expected_result << endl;

    return 0;
}