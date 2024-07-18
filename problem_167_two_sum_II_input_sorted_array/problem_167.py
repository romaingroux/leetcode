"""
Given a 1-indexed array of integers numbers that is already sorted in n
on-decreasing order, find two numbers such that they add up to a specific 
target number. Let these two numbers be numbers[index1] and numbers[index2] 
where 1 <= index1 < index2 <= numbers.length.

Return the indices of the two numbers, index1 and index2, added by one as an 
integer array [index1, index2] of length 2.

The tests are generated such that there is exactly one solution. You may not 
use the same element twice.

Your solution must use only constant extra space.

 

Example 1:

Input: numbers = [2,7,11,15], target = 9
Output: [1,2]
Explanation: The sum of 2 and 7 is 9. Therefore, index1 = 1, index2 = 2. 
We return [1, 2].
Example 2:

Input: numbers = [2,3,4], target = 6
Output: [1,3]
Explanation: The sum of 2 and 4 is 6. Therefore index1 = 1, index2 = 3. 
We return [1, 3].
Example 3:

Input: numbers = [-1,0], target = -1
Output: [1,2]
Explanation: The sum of -1 and 0 is -1. Therefore index1 = 1, index2 = 2. 
We return [1, 2].
 

Constraints:

2 <= numbers.length <= 3 * 104
-1000 <= numbers[i] <= 1000
numbers is sorted in non-decreasing order.
-1000 <= target <= 1000
The tests are generated such that there is exactly one solution.
"""

import typing as tp


class Solution:
    def twoSumNaive(self, 
               numbers: tp.List[int], 
               target: int) \
        -> tp.List[int]:
        """
        Naive algorithm to find the index of both elements in numbers 
        summing up to target. Wotrks in O(n^2) time.
        Args:
            numbers: the list of int to search in.
            target: the desired sum to obtain.
        Returns:
            A pair of index (1-based) of the elements to sum.
        """
        
        l = len(numbers)
        for i in range(0, l):
            for j in range(0, l):
                if i == j:
                    continue
                elif numbers[i] + numbers[j] == target:
                    return [i+1,j+1]
                
        return [-1,-1]

    def twoSum(self, 
               numbers: tp.List[int], 
               target: int) \
        -> tp.List[int]:
        """
        Fast algorithm to find the index of both elements in numbers 
        summing up to target. Works in O(n) time.
        Args:
            numbers: the list of int to search in.
            target: the desired sum to obtain.
        Returns:
            A pair of index (1-based) of the elements to sum.
        """
        
        l = len(numbers)
        i = 0
        j = l-1

        while (i<l) and (j>=0):
            n = numbers[i] + numbers[j]
            # match
            if n == target:
                return [i+1,j+1]
            # over shoot
            elif n > target:
                j -= 1
            # under shoot
            else:
                i += 1

        return [-1,-1]

if __name__ == "__main__":

    s = Solution()
    assert(s.twoSum([2,7,11,15], 9) == [1,2])
    assert(s.twoSum([2,3,4],     6) == [1,3])
    assert(s.twoSum([-1,0],     -1) == [1,2])