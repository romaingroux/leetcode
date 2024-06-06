/*
You are given a 0-indexed array of integers nums of length n. You are initially positioned at nums[0].

Each element nums[i] represents the maximum length of a forward jump from index i. In other words, if you are at nums[i], you can jump to any nums[i + j] where:

0 <= j <= nums[i] and
i + j < n
Return the minimum number of jumps to reach nums[n - 1]. The test cases are generated such that you can reach nums[n - 1].

 

Example 1:

Input: nums = [2,3,1,1,4]
Output: 2
Explanation: The minimum number of jumps to reach the last index is 2. Jump 1 step from index 0 to 1, then 3 steps to the last index.
Example 2:

Input: nums = [2,3,0,1,4]
Output: 2
 

Constraints:

1 <= nums.length <= 104
0 <= nums[i] <= 1000
It's guaranteed that you can reach nums[n - 1].
*/

#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>


std::ostream& operator << (std::ostream& stream,
                           const std::vector<int>& v)
{
    for(const auto& x : v)
    {   stream << x << " " ; }
    return stream ;
}


class Solution
{
    public:

    int jump0(std::vector<int>& nums) {

        int furthest_curr(-1) ;
        int nums_size = static_cast<int>(nums.size()) ;
        int n_jump = 0 ;

        if(nums.size() == 1) 
        {   return 0 ; }

        for(int i=0; i<nums_size; i++)
        {   
            // can jump further than before
            if((i + nums[i]) > furthest_curr)
            {   // std::cerr << "jump " << i << "->" << i+nums[i] << std::endl ;
                furthest_curr = i + nums[i] ; 
                n_jump++ ;
                // end is reachable
                if(furthest_curr >= (nums_size-1))
                {   // std::cerr << "return " << n_jump << std::endl << std::endl ;
                    return n_jump ; 
                }
            }
            // max range not yet reached
            else if(i < furthest_curr)
            {   continue ; }
            // too bad
            else
            {   break ; }
        }
        return -1 ;
    }

    int jump(std::vector<int>& nums) {

        int currEndJump(0) ;
        int maxEndJump(0) ;
        int nJump(0) ;

        int nums_n = static_cast<int>(nums.size()) ;

        for(int i=0; i<nums_n-1; i++)
        {
            maxEndJump = std::max(maxEndJump, i+nums[i]) ;

            if(maxEndJump >= nums_n-1)
            {   nJump++ ;
                break ;
            }

            if(i == currEndJump)
            {   nJump++ ;
                currEndJump = maxEndJump ;
            }
        }
        std::cerr << "return " << nJump << std::endl << std::endl ;
        return nJump ;
    }
} ;


int main()
{ 
    Solution s ;

    std::vector<int> v1 = {2,3,1,1,4} ;
    std::vector<int> v2 = {2,3,0,1,4} ;
    std::vector<int> v3 = {0} ;
    std::vector<int> v4 = {1} ;
    std::vector<int> v5 = {1,2,1,1,1} ;
    std::vector<int> v6 = {7,0,9,6,9,6,1,7,9,0,1,2,9,0,3} ;

    assert(s.jump(v1) == 2) ;
    assert(s.jump(v2) == 2) ;
    assert(s.jump(v3) == 0) ;
    assert(s.jump(v4) == 0) ;
    assert(s.jump(v5) == 3) ;
    assert(s.jump(v6) == 2) ;

    return 0 ;
}
