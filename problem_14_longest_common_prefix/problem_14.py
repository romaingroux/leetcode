"""
Write a function to find the longest common prefix string amongst an array of 
strings.

If there is no common prefix, return an empty string "".

 

Example 1:

Input: strs = ["flower","flow","flight"]
Output: "fl"
Example 2:

Input: strs = ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.
 

Constraints:

1 <= strs.length <= 200
0 <= strs[i].length <= 200
strs[i] consists of only lowercase English letters.
"""

import typing as tp


class Solution:
    def longestCommonPrefix(self, strs: tp.List[str]) \
        -> str:

        prefix_l = 0
        l_min = min([len(s) for s in strs])
        for i in range(0,l_min):
            c = strs[0][i]
            
            test = [s[i] == c for s in strs[1:]]
            if sum(test) == len(strs)-1:
                prefix_l += 1
            else:
                break
        
        return strs[0][0:prefix_l]


if __name__ == "__main__":

    s = Solution()
    assert(s.longestCommonPrefix(["flower","flow","flight"]) == "fl")
    assert(s.longestCommonPrefix(["cir","car"]) == "c")
