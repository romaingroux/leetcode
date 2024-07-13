"""
Given two strings needle and haystack, return the index of the first occurrence 
of needle in haystack, or -1 if needle is not part of haystack.


Example 1:

Input: haystack = "sadbutsad", needle = "sad"
Output: 0
Explanation: "sad" occurs at index 0 and 6.
The first occurrence is at index 0, so we return 0.
Example 2:

Input: haystack = "leetcode", needle = "leeto"
Output: -1
Explanation: "leeto" did not occur in "leetcode", so we return -1.
 

Constraints:

1 <= haystack.length, needle.length <= 104
haystack and needle consist of only lowercase English characters.
"""

import re


class Solution:

    def strStrNaive(self, word: str, pattern: str) \
        -> int:
        """
        Naive algorithm to search the 1st of occurence of pattern of length M 
        in word of length N, time complexity O(NxM).
        Args:
            word: the word to search in.
            pattern: the pattern to find.
        Returns: the index of the 1st occurence of pattern in word, -1 if not 
            found.
        """
        if len(word) == 0:
            return -1
        elif len(word) < len(pattern):
            return -1

        for i in range(0, len(word)-len(pattern)+1):
            found = True
            for j in range(0,len(pattern)):
                if word[i+j] != pattern[j]:
                    found = False
                    break
            if found:
                return i
        return -1
    
    def strStr(self, word: str, pattern: str) \
        -> int:
        """
        Uses regex to search the 1st of occurence of pattern of length M 
        in word of length N.
        Args:
            word: the word to search in.
            pattern: the pattern to find.
        Returns: the index of the 1st occurence of pattern in word, -1 if not 
            found.
        """
        if len(word) == 0:
            return -1
        elif len(word) < len(pattern):
            return -1

        match = re.search(pattern, word)
        if match is None:
            return -1
        else:
            return match.start()


if __name__ == "__main__":
    s = Solution()
    assert(s.strStr("sadbutsad", "sad") == 0)
    assert(s.strStr("leetcode", "leeto") == -1)
    assert(s.strStr("", "pattern") == -1)
    assert(s.strStr("a", "a") == 0)