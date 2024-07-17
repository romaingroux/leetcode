"""
You are given an integer array height of length n. There are n vertical lines drawn such that the two endpoints of the ith line are (i, 0) and (i, height[i]).

Find two lines that together with the x-axis form a container, such that the container contains the most water.

Return the maximum amount of water a container can store.

Notice that you may not slant the container.

 

Example 1:


Input: height = [1,8,6,2,5,4,8,3,7]
Output: 49
Explanation: The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the container can contain is 49.
Example 2:

Input: height = [1,1]
Output: 1
 

Constraints:

n == height.length
2 <= n <= 105
0 <= height[i] <= 104
"""

import typing as tp


class Solution:
    def maxAreaNaive(self, heights: tp.List[int]) \
        -> int:
        """
        Finds the max area on O(N^2) time.
        Args:
            heights: a list of value representing the heights of the bars.
        Returns:
            The max possible area between two bars.
        """

        area_max = 0

        n = len(heights)
        for i in range(0, n):
            area = 0
            for j in range(0, n):
                h1 = heights[i]
                h2 = heights[j]
                width = abs(i-j)
                height = min(h1,h2)
                area = width * height
                # print(f"{h1} {h2} : W {width} x H {height} = {area}")
                if area > area_max:
                    # print("max area")
                    area_max = area
        return area_max
    
    def maxArea(self, heights: tp.List[int]) \
        -> int:
        """
        Finds the max area. 
        Args:
            heights: a list of value representing the heights of the bars.
        Returns:
            The max possible area between two bars.
        """
        # pointers
        n = len(heights)
        i = 0
        j = n-1
        area_max = 0

        while (i<j):
            h1 = heights[i]
            h2 = heights[j]
            width = abs(i-j)
            height = min(h1,h2)
            area = width * height
            print(f"{h1} {h2} : W {width} x H {height} = {area}")
            # update area
            if area > area_max:
                print("max area")
                area_max = area
            # move shortest edge
            if h1 < h2:
                print("move L edge")
                i += 1
            else:
                print("move R edge")
                j -=1
        return area_max

if __name__ == "__main__":
    
    s = Solution()

    assert(s.maxArea([1,8,6,2,5,4,8,3,7]) == 49)
    assert(s.maxArea([1,1])               == 1)