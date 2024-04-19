/*
Given an integer array nums, rotate the array to the right by k steps, where k is non-negative.

 

Example 1:

Input: nums = [1,2,3,4,5,6,7], k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]
Example 2:

Input: nums = [-1,-100,3,99], k = 2
Output: [3,99,-1,-100]
Explanation: 
rotate 1 steps to the right: [99,-1,-100,3]
rotate 2 steps to the right: [3,99,-1,-100]
 

Constraints:

1 <= nums.length <= 105
-231 <= nums[i] <= 231 - 1
0 <= k <= 105
 

Follow up:

Try to come up with as many solutions as you can. There are at least three different ways to solve this problem.
Could you do it in-place with O(1) extra space?

*/

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
        
        static
        void rotate_by_1(std::vector<int>& nums)
        {   
            int last = nums.back() ;

            for(int i=nums.size()-2; i>=0; i--)
            {   nums[i+1] = nums[i] ; }
            nums[0] = last ;
        }
        void rotate(std::vector<int>& nums, int k)
        {
            for(size_t i=0; i<k; i++)
            {   Solution::rotate_by_1(nums) ; }
        }

        void rotate(std::vector<int>& nums, int k)
        {
            int n = nums.size() ;
            std::vector<int> temp(n);

            // ensure k is in range of n
            k %= n ;

            int j = 0;
            for (int i = n - k; i < n; ++i, ++j) {
                temp[j] = nums[i];
            }

            for (int i = 0; i < n - k; ++i, ++j) {
                temp[j] = nums[i];
            }
            nums = temp ;
        }

        // the fastest solution avaiable on leetcode
        void rotateFast(std::vector<int>& nums, int k) {
            int n = nums.size();
            k = k % n; // Ensure k is within the range [0, n)

            // Reverse the entire array
            std::reverse(nums.begin(), nums.end());
            
            // Reverse the first k elements
            std::reverse(nums.begin(), nums.begin() + k);
            
            // Reverse the rest of the elements after k
            std::reverse(nums.begin() + k, nums.end());
    }
};


int main()
{
    int k = 3 ;
    std::vector<int> nums({1,2,3,4,5,6,7}) ;
    std::cout << nums << std::endl ; 
    
    Solution s ;
    s.rotate(nums, k) ;
    
    std::cout << nums << std::endl ;
    
    return 0 ;
}