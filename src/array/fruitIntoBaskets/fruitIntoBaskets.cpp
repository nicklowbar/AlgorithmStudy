#include <utils/logHelper.h>
#include <utils/printHelper.h>

#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>

using namespace std;

/*
You are visiting a farm that has a single row of fruit trees arranged from left to right. The trees are represented by an integer array fruits where fruits[i] is the type of fruit the ith tree produces.

You want to collect as much fruit as possible. However, the owner has some strict rules that you must follow:

    You only have two baskets, and each basket can only hold a single type of fruit. There is no limit on the amount of fruit each basket can hold.
    Starting from any tree of your choice, you must pick exactly one fruit from every tree (including the start tree) while moving to the right. The picked fruits must fit in one of your baskets.
    Once you reach a tree with fruit that cannot fit in your baskets, you must stop.

Given the integer array fruits, return the maximum number of fruits you can pick.

 

Example 1:

Input: fruits = [1,2,1]
Output: 3
Explanation: We can pick from all 3 trees.

Example 2:

Input: fruits = [0,1,2,2]
Output: 3
Explanation: We can pick from trees [1,2,2].
If we had started at the first tree, we would only pick from trees [0,1].

Example 3:

Input: fruits = [1,2,3,2,2]
Output: 4
Explanation: We can pick from trees [2,3,2,2].
If we had started at the first tree, we would only pick from trees [1,2].

 

Constraints:

    1 <= fruits.length <= 105
    0 <= fruits[i] < fruits.length

*/


/**
 * @brief Given an array of integers representing trees, return the length of the longest subarray that contains at most two distinct values.
 */
int totalFruit(vector<int>& fruits) 
{
    // we want to be able to compute the longest sub-array consisting of up to two different values.
    // a naieve approach would be, for each element in the array, keep track of unique values, and iterate until you encounter a different one.
    
    // the Queue data structure _seems_ helpful here, as we can use the LIFO to keep track of previously encountered fruit, and dequeue old fruit when we want to process a new type of fruit moving forward, however we can intuitively "queue" our encountered trees using a pair of pointers indicating a sliding window, as our traveral order is fixed.
    
    // some interesting test cases would be where we see multiple instances of multiple fruit:
    // [1,2,1,2,3,1,2,1,2] where a naive queue would be difficult to keep track of these fruit independently.
    
    // I believe that keeping track of "first seen" and "last seen" for a given fruit may help here, however we can 
    
    // lets iterate over the input array, keeping track of unique "seen" values via a set, and keeping track of indices of new "seen" values
    
    // we can use a Dictionary to keep track of our baskets, using the type of fruit as the key, and the number we have in our baskets as the value. when we encounter one too many new types of tree, we can empty the baskets using a sliding window pointer keeping track of our starting position.

    const int numBaskets = 2;
    unordered_map<int, int> baskets;
    auto windowStartIdx = fruits.begin(); // initialize window to point at array start.
    auto windowEndIdx = fruits.begin();
    
    int maxFruit = 0;
    
    while(windowEndIdx != fruits.end())
    {
        int currentFruit = *windowEndIdx;
        
        // add this fruit into our basket, clearing space if necessary.
        if (baskets.contains(currentFruit))
        {
            //cout << "Added a fruit to basket: " << currentFruit << endl;
            baskets[currentFruit]++;
            //cout << "Number of fruit in basket: " << currentFruit << " : " << baskets[currentFruit] << endl;
        }
        else
        {
            while(baskets.size() > numBaskets - 1)
            {
                int currentRemovedFruit = *windowStartIdx;
                int& numCurrentRemovedFruit = baskets[currentRemovedFruit];
                numCurrentRemovedFruit--;
                //cout << "Removed a fruit from basket: " << currentRemovedFruit << " " << numCurrentRemovedFruit << " Remaining." << endl;
                if(numCurrentRemovedFruit <= 0)
                {
                    //cout << "Removed basket: " << currentRemovedFruit << endl;
                    baskets.erase(currentRemovedFruit);
                }
                
                windowStartIdx++;
            }
            //cout << "Added new basket: " << currentFruit << endl;
            
            baskets[currentFruit] = 1;
            //cout << "Number of fruit in basket: " << currentFruit << " : " << baskets[currentFruit] << endl;
        }
        
        windowEndIdx++;
        maxFruit = max<int>(maxFruit, windowEndIdx - windowStartIdx);
        //cout << "maximum fruit: " << maxFruit << endl;
    }
    
    return maxFruit;
}

int main()
{
    // TODO: Add support for defining test cases in a more succinct way.
    {
        vector<int> fruits = {1,2,1};
        int expected = 3;
        cout << "Input: " << utils::printVector(fruits) << endl;
        cout << "Output: " << totalFruit(fruits) << " Expected: " << expected << endl;
    }
    
    {
        vector<int> fruits = {0,1,2,2};
        int expected = 3;
        cout << "Input: " << utils::printVector(fruits) << endl;
        cout << "Output: " << totalFruit(fruits) << " Expected: " << expected << endl;
    
    }
    
    {
        vector<int> fruits = {1,2,3,2,2};
        int expected = 4;
        cout << "Input: " << utils::printVector(fruits) << endl;
        cout << "Output: " << totalFruit(fruits) << " Expected: " << expected << endl;
    }
    
    {
        vector<int> fruits = {1,2,1,2,3,1,2,1,2};
        int expected = 4;
        cout << "Input: " << utils::printVector(fruits) << endl; 
        cout << "Output: " << totalFruit(fruits) << " Expected: " << expected << endl;
    }

}