/*
Given an array nums of size n, return the majority element.

The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.

 

Example 1:

Input: nums = [3,2,3]
Output: 3

Example 2:

Input: nums = [2,2,1,1,1,2,2]
Output: 2
 

Constraints:

n == nums.length
1 <= n <= 5 * 104
-109 <= nums[i] <= 109
 

Follow-up: Could you solve the problem in linear time and in O(1) space?
*/

#include <iostream>
#include <vector>
#include <unordered_map>

std::ostream& operator << (std::ostream& stream, 
                           const std::vector<int>& v)
{
    for(const auto& x : v)
    {   stream << x << " " ; }
    return stream ;
}


class Solution {
public:
    int majorityElement(std::vector<int>& nums) 
    {
        size_t l = nums.size() ;
        size_t n_min = l / 2 ;
        std::cout << l << std::endl ;
        std::cout << n_min << std::endl ;

        std::unordered_map<int,size_t> freq ;


        for(const auto& num : nums)
        {   
            if(freq.find(num) != freq.end())
            {   freq[num]++ ; }
            else
            {   freq[num] = 1 ; }

            if(freq[num] > n_min)
            {   return num ; }
        }

        return -1 ;
    }

    /*
     * This is the Boyer-Moore algorithm. It is garantued to 
     * be correct only if the is a major element in the given 
     * vector. Otherwise a 2nd pass must be performed to 
     * check that the majority element is really one.
     */
    int majorityElementFast(std::vector<int>& nums) 
    {
        int major ;
        size_t count(0) ;

        for(const auto& num : nums)
        {
            if(count == 0)
            {   major = num ; 
                count = 1 ;
            }
            else if(num == major)
            {   count++ ; }
            else
            {   count-- ; }
        }
        return major ;
    }
} ;


int main()
{
    std::vector<int> nums({2,2,1,1,1,2,2}) ;
    
    Solution s ;
    int k = s.majorityElement(nums) ;
    
    std::cout << k << std::endl ;
    std::cout << nums << std::endl ;
    
    return 0 ;
}