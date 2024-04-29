/*
You are given an integer array prices where prices[i] is the price of a given stock on the ith day.

On each day, you may decide to buy and/or sell the stock. You can only hold at most one share of the stock at any time. However, you can buy it then immediately sell it on the same day.

Find and return the maximum profit you can achieve.

 

Example 1:

Input: prices = [7,1,5,3,6,4]
Output: 7
Explanation: Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit = 5-1 = 4.
Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit = 6-3 = 3.
Total profit is 4 + 3 = 7.
Example 2:

Input: prices = [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
Total profit is 4.
Example 3:

Input: prices = [7,6,4,3,1]
Output: 0
Explanation: There is no way to make a positive profit, so we never buy the stock to achieve the maximum profit of 0.
 

Constraints:

1 <= prices.length <= 3 * 104
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
    {   // compute 1st derivative
        // get all stretches > 0
        // these stretches are when to buy and sell

        int profit(0) ;
        int diff_best(0) ;

        for(size_t i=1; i<prices.size(); i++)
        {   int diff_curr = prices[i] - prices[i-1] ;
            
            // std::cerr << "diff " << diff_curr << std::endl ;

            // price is still increasing
            if(diff_curr > 0)
            {   diff_best += diff_curr ; }
            // price decreased
            else
            {   profit += diff_best ;
                diff_best = 0 ;
            }
        }
        if(diff_best > 0)
        {   profit += diff_best ; }
        // std::cerr << "profit " << profit << std::endl ; 
        // std::cerr << std::endl ;

        return std::max(0, profit) ;
    }
};


int main()
{
    std::vector<int> prices_1({7,1,5,3,6,4}) ;
    std::vector<int> prices_2({1,2,3,4,5}) ;
    std::vector<int> prices_3({7,6,4,3,1}) ;

    Solution s ;

    assert(s.maxProfit(prices_1) == 7) ;
    assert(s.maxProfit(prices_2) == 4) ;
    assert(s.maxProfit(prices_3) == 0) ;
    
    return 0 ;
}