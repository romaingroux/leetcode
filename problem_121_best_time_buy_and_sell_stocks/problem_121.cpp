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

#include <iostream>
#include <vector>
#include <limits>
#include <cassert>


std::ostream& operator << (std::ostream& stream, 
                           const std::vector<int>& v)
{
    for(const auto& x : v)
    {   stream << x << " " ; }
    return stream ;
}


class Solution {
public:
    
    int maxProfit(std::vector<int>& prices)
    {
        if(prices.size() == 1)
        {   return 0 ; }

        int min = std::min(prices[0], prices[1]) ; // buy
        int max = std::max(prices[0], prices[1]) ; // sell
        int spread = -1 ;

        if(prices[1] >= prices[0])
        {   spread = max - min ; }

       
        for(size_t i=2; i<prices.size(); i++)
        {
            // a new max means a new sell price, can update spread
            if(prices[i] >= max)
            {   max = prices[i] ;
                spread = max - min ;
            }
            // new price may not exceed current max
            // but if it increases spread, take it!
            if(prices[i] - min > spread)
            {   max = prices[i] ;
                spread = prices[i] - min ;
            }
            // a new possible best buy price
            // will only update spread if we can find best sell price after this (if case atop)
            if(prices[i] < min)
            {   min = prices[i] ; }
        }

        return std::max(0, spread) ;
    }
};

int main()
{
    std::vector<int> prices_1({7,1,5,3,6,4}) ;
    std::vector<int> prices_2({7,6,4,3,1}) ;
    std::vector<int> prices_3({2,1,2,1,0,1,2}) ;
    std::vector<int> prices_4({3,3,5,0,0,3,1,4}) ;

    Solution s ;
    
    assert(s.maxProfit(prices_1) == 5) ;
    assert(s.maxProfit(prices_2) == 0) ;
    assert(s.maxProfit(prices_3) == 2) ;
    assert(s.maxProfit(prices_4) == 4) ;
    
    return 0 ;
}