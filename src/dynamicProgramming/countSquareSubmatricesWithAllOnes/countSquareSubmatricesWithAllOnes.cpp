#include <vector>
#include <algorithm>
#include <iostream>
#include <utils/printHelper.h>

using namespace std;
using namespace utils;

class Solution {
public:

    #define PRINT 0

    int countSquares(vector<vector<int>>& matrix) {
        // I'm not quite seeing a simplistic way to represent this
        // after consulting with GPT4, the ideal way to go about this is:
        // construct an n*n matrix that keeps track of the largest subsquare of 1s that this square is part of

        // Base case: a cell containing a 1 is a 1x1 subsquare.
        int height = matrix.size();
        int width = matrix[0].size();

        vector<vector<int>> largestSubsquare(matrix.size());
        for(int i = 0; i < height; ++i){
            largestSubsquare[i] = matrix[i];
        }

        // Inductive step: a cell is capable of an nxn square matrix if it is surrounded by squares consisting of n-1 size squares
        // we can check the n-1 case recursively by starting at the top left of the grid, and evaluating if this square is the bottom right of a nxn submatrix.
        for (int i = 1; i < height; ++i)
        {
            for (int j = 1; j < width; ++j)
            {
                int cellResult = min(largestSubsquare[i-1][j], min(largestSubsquare[i][j-1], largestSubsquare[i-1][j-1])) + 1;
                cellResult *= matrix[i][j];

                #if PRINT
                //cout << "Setting " << i << " , " << j << " to: " << cellResult << endl;
                #endif
                largestSubsquare[i][j] = cellResult;
            }
        }

        int result = 0;
        for (auto row : largestSubsquare)
        {
            for (auto cell : row)
            {
                result += cell;
            }
        }

        #if PRINT
        cout << "[" << endl;
        for(auto row : largestSubsquare)
        {
            cout << " ";
            for (auto cell : row)
            {
                cout << cell << " ";
            }
            cout << endl;
        }
        cout << "]" << endl;
        #endif

        return result;
    }
};

int main()
{
    {
        Solution s;
        vector<vector<int>> input = {{0,1,1,1},{1,1,1,1},{0,1,1,1}};
        cout << "Input: " << endl;
        for(auto row : input)
        {
            cout << printVector(row) << endl;
        }
        int expected = 15;
        cout << "Output: " << s.countSquares(input) << " Expected: " <<  expected << endl;
    }
    {
        Solution s;
        vector<vector<int>> input = {{1,0,1},{1,1,0},{1,1,0}};
        cout << "Input: " << endl;
        for(auto row : input)
        {
            cout << printVector(row) << endl;
        }
        int expected = 7;
        cout << "Output: " << s.countSquares(input) << " Expected: " <<  expected << endl;
    }
}