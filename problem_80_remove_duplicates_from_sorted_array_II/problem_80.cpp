/*
Given an integer array nums sorted in non-decreasing order, remove some duplicates in-place such that each unique element appears at most twice. The relative order of the elements should be kept the same.

Since it is impossible to change the length of the array in some languages, you must instead have the result be placed in the first part of the array nums. More formally, if there are k elements after removing the duplicates, then the first k elements of nums should hold the final result. It does not matter what you leave beyond the first k elements.

Return k after placing the final result in the first k slots of nums.

Do not allocate extra space for another array. You must do this by modifying the input array in-place with O(1) extra memory.

Custom Judge:

The judge will test your solution with the following code:

int[] nums = [...]; // Input array
int[] expectedNums = [...]; // The expected answer with correct length

int k = removeDuplicates(nums); // Calls your implementation

assert k == expectedNums.length;
for (int i = 0; i < k; i++) {
    assert nums[i] == expectedNums[i];
}
If all assertions pass, then your solution will be accepted.

 

Example 1:

Input: nums = [1,1,1,2,2,3]
Output: 5, nums = [1,1,2,2,3,_]
Explanation: Your function should return k = 5, with the first five elements of nums being 1, 1, 2, 2 and 3 respectively.
It does not matter what you leave beyond the returned k (hence they are underscores).
Example 2:

Input: nums = [0,0,1,1,1,1,2,3,3]
Output: 7, nums = [0,0,1,1,2,3,3,_,_]
Explanation: Your function should return k = 7, with the first seven elements of nums being 0, 0, 1, 1, 2, 3 and 3 respectively.
It does not matter what you leave beyond the returned k (hence they are underscores).
 

Constraints:

1 <= nums.length <= 3 * 104
-104 <= nums[i] <= 104
nums is sorted in non-decreasing order.
*/

#include <iostream>
#include <vector>

std::ostream& operator << (std::ostream& stream, 
                           const std::vector<int>& v)
{
    for(const auto& x : v)
    {   stream << x << " " ; }
    return stream ;
}



class Solution {
public:
    int countRepetitions(std::vector<int>& nums)
    {
        
        for(size_t i=0; i<nums.size(); )
        {
            // loop forward and count how many times this item is repeated
            size_t rep_n = 1 ;
            for(size_t j=i+1; j<nums.size();j++)
            {   if(nums[i] != nums[j])
                {   break ; }
                else
                {   rep_n++ ; }
            }
            std::cout << nums[i] << " is repeated " << rep_n << "X" << std::endl ; 
            i = i+rep_n ;
        }
        return 0 ;
    }

    int removeDuplicates(std::vector<int>& nums)
    {   
        size_t n_unique(0) ;
        size_t copy_at(0) ;

        for(size_t i=0; i<nums.size(); )
        {
            // loop forward and count how many times this item is repeated
            size_t rep_n = 1 ;
            for(size_t j=i+1; j<nums.size();j++)
            {   if(nums[i] != nums[j])
                {   break ; }
                else
                {   rep_n++ ; }
            }
            std::cout << nums[i] << " is repeated " << rep_n << "X" << std::endl ; 

            // in place edition
            size_t number_insert = (rep_n > 2) ? 2 : rep_n;
            for(size_t j=0; j<number_insert; j++)
            {   nums[copy_at] = nums[i] ; 
                std::cout << "writing " << nums[i] << " at index " << copy_at << std::endl ;
                copy_at++ ;
                n_unique++ ;
            }

            i = i+rep_n ;
        }
        return n_unique ;
    }
};


int main()
{
    std::vector<int> nums({0,0,1,1,1,1,2,3,3}) ;
    
    Solution s ;
    int k = s.removeDuplicates(nums) ;
    
    std::cout << k << std::endl ;
    std::cout << nums << std::endl ;
    
    return 0 ;
}