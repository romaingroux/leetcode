"""
Given a string s, find the length of the longest 
substring without repeating characters.


Example 1:
Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.

Example 2:
Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.

Example 3:
Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a 
substring.
 

Constraints:

0 <= s.length <= 5 * 104
s consists of English letters, digits, symbols and spaces.
"""

import typing as tp


class Solution:
    def lengthOfLongestSubstring(self, s: str) \
        -> int:
        """
        Finds the length of longtest substring in s that contains 
        not character repeatition.
        Works in O(N) time.
        Args:
            s: the string of interest.
        Returns:
            The size of the largest substring in s without repeatition.
        """

        l = len(s)
        if l == 0:
            return 0
        
        # window is [start,end)
        # start = 0
        end = 1
        # char found in window, O(1) access time
        char_w = set()
        char_w.add(s[0])
        len_w = 1
        len_best = 1

        for start in range(0,l):
            # no repeat
            # extend L
            while (end < l) and (s[end] not in char_w):
                char_w.add(s[end])
                end += 1
                len_w += 1
                len_best = max(len_best, len_w)

            # repeat 
            # trim R
            if (end < l) and (s[end] in char_w):
                char_w.remove(s[start])
                start += 1
                len_w -= 1

            # cannot extend, no repeat, we already have found the longest
            # window at some point
            else:
                break

        return len_best

if __name__ == "__main__":

    s = Solution()
    assert(s.lengthOfLongestSubstring("abcabcbb") == 3)
    assert(s.lengthOfLongestSubstring("bbbbb")    == 1)
    assert(s.lengthOfLongestSubstring("pwwkew")   == 3)
    assert(s.lengthOfLongestSubstring("abcdefgh") == 8)
    assert(s.lengthOfLongestSubstring("")         == 0)

