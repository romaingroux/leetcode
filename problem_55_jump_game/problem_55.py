"""
You are given an integer array nums. You are initially positioned at the 
array's first index, and each element in the array represents your maximum 
jump length at that position.

Return true if you can reach the last index, or false otherwise.

 

Example 1:
Input: nums = [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.

Example 2:
Input: nums = [3,2,1,0,4]
Output: false
Explanation: You will always arrive at index 3 no matter what. Its maximum jump 
length is 0, which makes it impossible to reach the last index.
 

Constraints:

1 <= nums.length <= 104
0 <= nums[i] <= 105
"""

import typing as tp

class Solution:
    def canJump(self, 
                nums: tp.List[int]) \
        -> bool:
        """
        """

        l = len(nums)

        if l > 1 and nums[0] == 0:
            return False
        
        # index of the furthest element we can reach from 
        # where we are
        furthest_possible = 0

        for i in range(0,l):
            # print(f" -> {i} {furthest_possible}")

            # this place cannot be accessed
            if furthest_possible < i:
                return False

            # the furthest we can go from here
            furthest_from_here = i + nums[i]
            # we have reached the end
            if furthest_from_here >= l-1:
                return True
            
            # check if we now can jump further than before
            if furthest_from_here > furthest_possible:
                furthest_possible = furthest_from_here
        
        return False

        

if __name__ == "__main__":
    
    s = Solution()

    assert(s.canJump([2,3,1,1,4]) == True)
    assert(s.canJump([3,2,1,0,4]) == False)
