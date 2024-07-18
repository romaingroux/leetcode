"""
Given an array of positive integers nums and a positive integer target, 
return the minimal length of a 
subarray whose sum is greater than or equal to target. If there is no such 
subarray, return 0 instead.

 

Example 1:
Input: target = 7, nums = [2,3,1,2,4,3]
Output: 2
Explanation: The subarray [4,3] has the minimal length under the problem 
constraint.

Example 2:
Input: target = 4, nums = [1,4,4]
Output: 1

Example 3:
Input: target = 11, nums = [1,1,1,1,1,1,1,1]
Output: 0
 

Constraints:

1 <= target <= 109
1 <= nums.length <= 105
1 <= nums[i] <= 104
 

Follow up: If you have figured out the O(n) solution, try coding another 
solution of which the time complexity is O(n log(n)).
"""

import typing as tp


class Solution:

    def minSubArrayLen(self, 
                       target: int, 
                       nums: tp.List[int]) \
                       -> int:
        """
        Finds the size of the smallest possible window within nums with a 
        sum >= target.
        Works in O(N) time.
        Args:
            target: the minimal window size.
            nums: the array to search in.
        Returns:
            The size of the smallest window with a sum >= target, 0 if none 
            is found.
        """

        l = len(nums)
        # window is [start,end)
        # start = 0
        end = 1
        sum_w = nums[0]  # sum in window
        len_w = 1        # length of window
        len_best = 9999999
        for start in range(0,l):
            # print(f"[{start},{end}) : score {sum_w}")
            # window score < target
            # extend towards right
            while (sum_w < target) and (end < l):
                sum_w += nums[end]
                end += 1
                len_w += 1
                # print(f"extend R  -- [{start},{end}) : score {sum_w}")
            # window score >= target
            if sum_w >= target:
                # remind this window
                len_best = min(len_best, len_w)
                # if len_w < len_best:
                #     print("new best")
                #     len_best = len_w
                # trim
                sum_w -= nums[start]
                start += 1
                len_w -= 1
                # print(f"trim L    -- [{start},{end}) : score {sum_w}")
        if len_best == 9999999:
            len_best = 0
        return len_best


if __name__ == "__main__":
    
    s = Solution()

    assert(s.minSubArrayLen(7, [2,3,1,2,4,3])     == 2)
    assert(s.minSubArrayLen(4, [1,4,4])           == 1)
    # print(s.minSubArrayLen(4, [1,4,4]))
    assert(s.minSubArrayLen(11, [1,1,1,1,1,1,1,1]) == 0)