#include <vector>
#include <algorithm>
#include <iostream>
#include <climits>

#include <utils/printHelper.h>

using namespace std;

/*
You are given an array prices where prices[i] is the price of a given stock on the ith day.

You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.

Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.

 

Example 1:

Input: prices = [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.

Example 2:

Input: prices = [7,6,4,3,1]
Output: 0
Explanation: In this case, no transactions are done and the max profit = 0.

 

Constraints:

    1 <= prices.length <= 105
    0 <= prices[i] <= 104


*/

int maxProfit(vector<int>& prices) {
    // This seems like a greedy sliding window problem at first glance, since we can only sell on a date later than our buy date
    // the naieve solution is to start on each day, and iterate to the end of the array to compute the maximum profit, requiring O(n^2) computations
    // However, we can reduce the amount of redundant traversals by keeping track of our current largest profit, and the lowest number we've seen so far, reducing this to O(n) as we no longer need to recompute previously encountered days.
    
    int minBuy = INT_MAX;
    auto sellPtr = prices.begin();
    int maxProfit = INT_MIN;
    while(sellPtr != prices.end())
    {
        int current = *sellPtr;
        minBuy = min(minBuy, current);
        maxProfit = max(maxProfit, current - minBuy);
        sellPtr++;
    }
    
    return maxProfit;
}

int main() {
    auto runTestCase([](vector<int> prices, int expected) {
        auto result = maxProfit(prices);
        cout << "Input: " << utils::printVector(prices) << endl;
        cout << "Output: " << result << " Expected: " << expected << endl;
    });

    runTestCase({7,1,5,3,6,4}, 5); // Output: 5 Expected: 5
    runTestCase({7,6,4,3,1}, 0); // Output: 0 Expected: 0

}