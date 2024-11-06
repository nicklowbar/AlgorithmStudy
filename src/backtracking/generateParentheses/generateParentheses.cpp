/*
22. Generate Parentheses
Attempted
Medium
Topics
Companies

Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

 

Example 1:

Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]

Example 2:

Input: n = 1
Output: ["()"]

 

Constraints:

    1 <= n <= 8


*/

#include <vector>
#include <string>
#include <iostream>

#include <utils/printHelper.h>

using namespace std;
using namespace utils;

class Solution {
public:

    void generateParenthesisHelper(int n, int leftParenthesisCount, int rightParenthesisCount, vector<string>& result, vector<char>& stringBuilder)
    {
        // Base case: we have generated enough braces on either side. Append this to our result array.
        if (leftParenthesisCount >= n && rightParenthesisCount >= n) 
        {
            //cout << "adding " << string(&stringBuilder[0], stringBuilder.size()) << " to results." << endl;
            result.push_back(string(stringBuilder.begin(), stringBuilder.end()));
        }

        // inductive step: 
        // we need to add left and right parentheses  at different places in a n-1 parenthesis to create all the different permutations of a n parenthesis

        // Recursively add left parentheses, but remove them once we generate all of our permutations with a left parenthesis inserted at that location.
        if (leftParenthesisCount < n)
        {
            stringBuilder.push_back('(');
            generateParenthesisHelper(n, leftParenthesisCount + 1, rightParenthesisCount, result, stringBuilder);
            stringBuilder.pop_back();

        }

        // For right braces, only add an additional one if we need to match a left brace, and recursively add more braces after this brace.
        if (rightParenthesisCount < leftParenthesisCount)
        {
            stringBuilder.push_back(')');
            generateParenthesisHelper(n, leftParenthesisCount, rightParenthesisCount + 1, result, stringBuilder);
            stringBuilder.pop_back();
        }
    }

    vector<string> generateParenthesis(int n) {
        // we want to generate all possible combinations of n parentheses
        // ex: n = 1 -> ()
        //     n = 2 -> (()), ()()
        //     n = 3 -> ((())), (()()), (())(), ()(()), ()()()  
        //  at a given layer, we need to generate:
        //      all of the permutations of n-1 with each element parenthesized
        //      all of the permutations of n-1 with a parenthesis added to the left or right side.
        //      these elements need to be unique. 
        //  this lends itself to a recursive backtracking strategy where we generate n-1, then modify the result with our parentheses. At each leaf in our backtracking tree, we can return a completed string.



        vector<string> result;
        vector<char> stringBuilder;

        generateParenthesisHelper(n, 0, 0, result, stringBuilder);
        return result;
    }
};

int main()
{
    {
        Solution s;
        int input = 3;
        auto result = s.generateParenthesis(input);
        string expected = "[((())), (()()), (())(), ()(()), ()()()]";
        cout << "Input: " << input << endl;
        cout << "Result: " << printVector(result) << endl << "Expected: " << expected << endl;
    }

    {
        Solution s;
        int input = 1;
        auto result = s.generateParenthesis(input);
        string expected = "[()]";
        cout << "Input: " << input << endl;
        cout << "Result: " << printVector(result) << endl << "Expected: " << expected << endl;
    }

    {
        Solution s;
        int input = 4;
        auto result = s.generateParenthesis(input);
        string expected = "[(((()))), ((()())), ((())()), ((()))(), (()(())), (()()()), (()())(), (())(()), (())()(), ()((())), ()(()()), ()(())(), ()()(()), ()()()()]";
        cout << "Input: " << input << endl;
        cout << "Result: " << printVector(result) << endl << "Expected: " << expected << endl;
    }
    
}