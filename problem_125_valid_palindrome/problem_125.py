"""
A phrase is a palindrome if, after converting all uppercase letters into 
lowercase letters and removing all non-alphanumeric characters, it reads the 
same forward and backward. Alphanumeric characters include letters and numbers.

Given a string s, return true if it is a palindrome, or false otherwise.


Example 1:

Input: s = "A man, a plan, a canal: Panama"
Output: true
Explanation: "amanaplanacanalpanama" is a palindrome.
Example 2:

Input: s = "race a car"
Output: false
Explanation: "raceacar" is not a palindrome.
Example 3:

Input: s = " "
Output: true
Explanation: s is an empty string "" after removing non-alphanumeric characters.
Since an empty string reads the same forward and backward, it is a palindrome.

 

Constraints:

1 <= s.length <= 2 * 105
s consists only of printable ASCII characters.
"""

import re


class Solution:
    def isPalindrome(self, s: str) \
        -> bool:
        """
        Checks if s is a palindrome. Rules are that only ASCII char are 
        considered. The method is case insensitive.
        Args:
            s: the string of interest.
        Returns:
            Whether s is a palindrome
        """
        
        # only leave alphanumeric
        print("1 ", s)
        s = s.lower()
        s = re.sub(r'[^0-9a-z]+', '', s)

        print("2 ", s)

        l = len(s)
        # check one half versus the other
        # if odd length, the pivot does not need to be checked
        l_half = l // 2

        i_rev = l - 1
        for i in range(0, l_half):
            if s[i] != s[i_rev]:
                return False
            i_rev -= 1
        
        return True

        


if __name__ == "__main__":

    sol = Solution()

    s1 = "A man, a plan, a canal: Panama"
    s2 = "race a car"
    s3 = " "
    s4 = "ab_a"

    assert(sol.isPalindrome(s1) == True)
    assert(sol.isPalindrome(s2) == False)
    assert(sol.isPalindrome(s3) == True)
    assert(sol.isPalindrome(s4) == True)
