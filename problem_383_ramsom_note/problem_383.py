"""
Given two strings ransomNote and magazine, return true if ransomNote can be constructed by using the letters from magazine and false otherwise.

Each letter in magazine can only be used once in ransomNote.

 

Example 1:

Input: ransomNote = "a", magazine = "b"
Output: false
Example 2:

Input: ransomNote = "aa", magazine = "ab"
Output: false
Example 3:

Input: ransomNote = "aa", magazine = "aab"
Output: true
 

Constraints:

1 <= ransomNote.length, magazine.length <= 105
ransomNote and magazine consist of lowercase English letters.
"""


class Solution:
    def canConstruct(self, ransomNote: str, magazine: str) -> bool:
        
        magazine_dict: dict[str,int] = Solution.construct_magazine_dict(magazine)
        for l in ransomNote:
            n_left = magazine_dict.get(l)
            if n_left is None or n_left == 0:
                return False
            if n_left:
                magazine_dict[l] -= 1
        return True

    @staticmethod
    def construct_magazine_dict(magazine: str) -> dict[str,int]:
        magazine_dict: dict[str,int] = {d:0 for d in magazine}
        for l in magazine:
            magazine_dict[l] += 1
        return magazine_dict

if __name__ == "__main__":

    assert Solution().canConstruct(ransomNote = "a", magazine = "b") is False
    assert Solution().canConstruct(ransomNote = "aa", magazine = "ab") is False
    assert Solution().canConstruct(ransomNote = "aa", magazine = "aab") is True

