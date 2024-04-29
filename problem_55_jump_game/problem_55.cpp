/*
You are given an integer array nums. You are initially positioned at the array's first index, and each element in the array represents your maximum jump length at that position.

Return true if you can reach the last index, or false otherwise.

 

Example 1:

Input: nums = [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
Example 2:

Input: nums = [3,2,1,0,4]
Output: false
Explanation: You will always arrive at index 3 no matter what. Its maximum jump length is 0, which makes it impossible to reach the last index.
 

Constraints:

1 <= nums.length <= 104
0 <= nums[i] <= 105
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
    
    bool canJump(std::vector<int>& nums)
    {
        int furthest_curr(-1) ;
        int nums_size = static_cast<int>(nums.size()) ;

        // if we can jump 0, the vector need to terminate here
        // otherwise it is a failure
        if((nums[0] == 0) and (nums_size > 1))
        {   return false ; }

        // at every step, check that we can either jump 
        // 1 further than before
        // 2 if we can't, we have not yet reach max range
        for(int i=0; i<nums_size; i++)
        {   // can jump further than before
            if((i + nums[i]) > furthest_curr)
            {   furthest_curr = i + nums[i] ; 
                // end is reachable
                if(furthest_curr >= (nums_size-1))
                {   return true ; }
            }
            // max range not yet reached
            else if(i < furthest_curr)
            {   continue ; }
            // too bad
            else
            {   break ; }
        }
        return false ;
    }
} ;


int main()
{
    std::vector<int> prices_1({2,3,1,1,4}) ;
    std::vector<int> prices_2({3,2,1,0,4}) ;
    std::vector<int> prices_3({0}) ;
    std::vector<int> prices_4({3,0,8,2,0,0,1}) ;
    std::vector<int> prices_5({0,1}) ;

    Solution s ;

    assert(s.canJump(prices_1) == true) ;
    assert(s.canJump(prices_2) == false) ;
    assert(s.canJump(prices_3) == true) ;
    assert(s.canJump(prices_4) == true) ;
    assert(s.canJump(prices_5) == false) ;
    
    return 0 ;
}