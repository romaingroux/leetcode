/*
Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].

The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

You must write an algorithm that runs in O(n) time and without using the division operation.

 

Example 1:

Input: nums = [1,2,3,4]
Output: [24,12,8,6]
Example 2:

Input: nums = [-1,1,0,-3,3]
Output: [0,0,9,0,0]
 

Constraints:

2 <= nums.length <= 105
-30 <= nums[i] <= 30
The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
 

Follow up: Can you solve the problem in O(1) extra space complexity? (The output array does not count as extra space for space complexity analysis.)
*/

#include <iostream>
#include <vector>
#include <cmath>

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
    std::vector<int> productExceptSelf(std::vector<int>& nums) {
        
        size_t n(nums.size()) ;

        // prod_l[i] contains the prod of all ements on LEFT of nums[i]
        // prod_l[i] = nums[0] * ... * nums[i-1]
        std::vector<int> prod_l(n, 1) ;
        // prod_r[i] contains the prod of all ements on RIGHT of nums[i]
        // prod_r[i] = nums[i+1] * ... * nums[n-1]
        std::vector<int> prod_r(n, 1) ;

        // init L
        int prod(1) ;
        for(size_t i=1; i<n; i++)
        {   prod *= nums[i-1] ; 
            prod_l[i] = prod ;
        }

        // init R
        prod = 1 ;
        for(int i=n-2; i>=0; i--)
        {   prod *= nums[i+1] ;
            prod_r[i] = prod ;
        }

        // product without self
        std::vector<int> prods(n) ;
        for(size_t i=0; i<n; i++)
        {   prods[i] = prod_l[i] * prod_r[i] ; }

        return prods ;
    }

    std::vector<int> productExceptSelf2(std::vector<int>& nums) {
        
        size_t n(nums.size()) ;
        std::vector<double> nums_log(n, 0) ;
        
        double sum_log = 0. ;
        for(size_t i=0; i<n; i++)
        {   nums_log[i] = log(nums[i]) ;
            sum_log += nums_log[i] ;
        }

        std::vector<int> nums_prod(n) ;
        for(size_t i=0; i<n; i++)
        {   nums_prod[i] = static_cast<int>(ceil(exp(sum_log - nums_log[i]))) ;

        }
        return nums_prod ;
    }
    
} ;


int main()
{
    Solution s ;
    /* insert tests */
    std::vector<int> v1 = {1,2,3,4} ;

    std::cout << s.productExceptSelf(v1) << std::endl ;
    std::cout << s.productExceptSelf2(v1) << std::endl ;
    return 0 ;
} ;
