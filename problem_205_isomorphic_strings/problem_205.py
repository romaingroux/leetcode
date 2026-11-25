"""
Given two strings s and t, determine if they are isomorphic.

Two strings s and t are isomorphic if the characters in s can be replaced to get t.

All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character, but a character may map to itself.

 

Example 1:

Input: s = "egg", t = "add"

Output: true

Explanation:

The strings s and t can be made identical by:

Mapping 'e' to 'a'.
Mapping 'g' to 'd'.
Example 2:

Input: s = "f11", t = "b23"

Output: false

Explanation:

The strings s and t can not be made identical as '1' needs to be mapped to both '2' and '3'.

Example 3:

Input: s = "paper", t = "title"

Output: true
"""


class Solution:

    def isIsomorphic(self, string1: str, string2: str) -> bool:
        if len(string1) != len(string2):
            return False

        transitions: dict[str, str] = {}
        transitions_rev: dict[str, str] = {}

        for start, end in zip(string1, string2):

            if transitions.get(start) is None:
                transitions[start] = end
                if transitions_rev.get(end) is None:
                    transitions_rev[end] = start
                    continue
                else:
                    return False

            if transitions.get(start) == end:
                continue

            if transitions.get(start) != end:
                return False

            if transitions_rev.get(end) != start:
                return False
              
        return True


"""
b -> b
a -> a
d -> a
c -> d
"""

if __name__ == "__main__":
    assert Solution().isIsomorphic(string1 = "egg", string2 = "add") is True
    assert Solution().isIsomorphic(string1 = "f11", string2 = "b23") is False
    assert Solution().isIsomorphic(string1 = "paper", string2 = "title") is True
    assert Solution().isIsomorphic(string1 = "badc", string2 = "baba") is False