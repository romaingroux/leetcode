"""
Given an integer array nums, return all the triplets 
[nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and 
nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set must not contain duplicate triplets.

 

Example 1:

Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Explanation: 
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
The distinct triplets are [-1,0,1] and [-1,-1,2].
Notice that the order of the output and the order of the triplets does not matter.
Example 2:

Input: nums = [0,1,1]
Output: []
Explanation: The only possible triplet does not sum up to 0.
Example 3:

Input: nums = [0,0,0]
Output: [[0,0,0]]
Explanation: The only possible triplet sums up to 0.
 

Constraints:

3 <= nums.length <= 3000
-105 <= nums[i] <= 105
"""

import typing as tp

class Solution:

    def twoSum(self, 
               numbers: tp.List[int], 
               start: int,
               target: int) \
        -> tp.List[tp.List[int]]:
        """
        Fast algorithm to find all pairs of elements, starting at start-th 
        element (0-based), in numbers summing up to target. 
        Works in O(N) time.
        Args:
            numbers: the list of int to search in.
            start: the 0-based index of the element where to start from in 
                numbers.
            target: the desired sum to obtain.
        Returns:
           A list of element pairs of numbers summing uo to target.
            None if nothing could be found.
        """

        res = set()
        l = len(numbers)
        i = start
        j = l-1
        # while (i<l) and (j>=start):
        while (i<j):
            n = numbers[i] + numbers[j]
            # match
            if n == target:
                res.add((numbers[i],numbers[j]))
                i += 1
                j -= 1
            # over shoot
            elif n > target:
                j -= 1
            # under shoot
            else:
                i += 1
        if len(res) != 0:
            return [[x,y] for x,y in res]
        return None
    
    def threeSum(self, 
                 nums: tp.List[int]) \
        -> tp.List[tp.List[int]]:
        """
        """

        nums = sorted(nums)
        l = len(nums)
        triplets = list()
        print("LOG: ", nums)
        for i in range(0,l):
            pivot = nums[i]
            # find a pair of 2 items equal to -pivot
            # such that pivot - (item1 + item2) = 0
            # pivot is 0, no need to search more, it is the same problem but in 
            # the other way
            if pivot > 0:
                break
            else:
                # previous pivot had this value, thus twoSum() will find 
                # another time the same result leading to a duplicated triplet
                if (i != 0) and (nums[i] == nums[i-1]):
                    continue 
                pairs = self.twoSum(nums, i+1, -pivot)
                if pairs is None:
                    continue
                else:
                    triplet = [[nums[i], pair[0], pair[1]] for pair in pairs]
                    # print(f"LOG: triplet {triplet}")
                    triplets.extend(triplet)
                # print(f"LOG: i={i} {triplets[-1]}")
        # print("LOG: ", triplets)
        return triplets

if __name__ == "__main__":

    s = Solution()
    # assert(sorted(s.threeSum([-1,0,1,2,-1,-4])) == 
    #        sorted([[-1, 0, 1], [-1, -1, 2]]))
    # assert(s.threeSum([0,1,1]) == list())
    # assert(s.threeSum([0,0,0]) == [[0,0,0]])
    # assert(s.threeSum([0,0,0,0]) == [[0,0,0]])
    # assert(sorted(s.threeSum([-1,0,1,2,-1,-4])) == sorted([[-1,-1,2],[-1,0,1]]))
    # assert(sorted(s.threeSum([-1,0,1,2,-1,-4,-2,-3,3,0,4])) == 
    #        sorted([[-4,0,4],[-4,1,3],[-3,-1,4],[-3,0,3],[-3,1,2],[-2,-1,3],[-2,0,2],[-1,-1,2],[-1,0,1]]))

    # assert(s.threeSum([-2,0,0,2,2]) == [[-2,0,2]])
    print(s.threeSum([-2,0,0,2,2]))

