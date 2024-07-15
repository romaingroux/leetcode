"""
Roman numerals are represented by seven different symbols: I, V, X, L, C, D and
 M.

Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
For example, 2 is written as II in Roman numeral, just two ones added together. 
12 is written as XII, which is simply X + II. The number 27 is written as XXVII, 
which is XX + V + II.

Roman numerals are usually written largest to smallest from left to right. 
However, the numeral for four is not IIII. Instead, the number four is written 
as IV. Because the one is before the five we subtract it making four. The same 
principle applies to the number nine, which is written as IX. There are six 
instances where subtraction is used:

I can be placed before V (5) and X (10) to make 4 and 9. 
X can be placed before L (50) and C (100) to make 40 and 90. 
C can be placed before D (500) and M (1000) to make 400 and 900.
Given a roman numeral, convert it to an integer.
 

Example 1:

Input: s = "III"
Output: 3
Explanation: III = 3.
Example 2:

Input: s = "LVIII"
Output: 58
Explanation: L = 50, V= 5, III = 3.
Example 3:

Input: s = "MCMXCIV"
Output: 1994
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
 

Constraints:

1 <= s.length <= 15
s contains only the characters ('I', 'V', 'X', 'L', 'C', 'D', 'M').
It is guaranteed that s is a valid roman numeral in the range [1, 3999].
"""

class Solution:
    
    map = {
        "I": 1,
        "V": 5,
        "X": 10,
        "L": 50,
        "C": 100,
        "D": 500,
        "M": 1000}

    def romanToInt(self, s: str) -> int:
        
        n = 0
        i = 0

        while i < len(s):
            # print(f"i {i}  s[i] {s[i]}")
            # last
            if i == len(s)-1:
                # print("case 1")
                n += Solution.map[s[i]]
                i += 1
            # inside, regular single char, eg V or X
            elif Solution.map[s[i]] >= Solution.map[s[i+1]]:
                # print("case 2")
                n += Solution.map[s[i]]
                i += 1
            # inside, two char, eg IV
            else:
                # print("case 3")
                n += Solution.map[s[i+1]] - Solution.map[s[i]]
                i += 2
            # print(f"n {n}")
        return n

if __name__ == "__main__":
    
    s = Solution()
    assert(s.romanToInt("I")     == 1)
    assert(s.romanToInt("II")    == 2)
    assert(s.romanToInt("III")   == 3)
    assert(s.romanToInt("IV")    ==  4)
    assert(s.romanToInt("V")     ==  5)
    assert(s.romanToInt("VI")    ==  6)
    assert(s.romanToInt("VII")   ==  7)
    assert(s.romanToInt("VIII")  ==  8)
    assert(s.romanToInt("IX")    ==  9)
    assert(s.romanToInt("X")     ==  10)
    assert(s.romanToInt("XI")    ==  11)
    assert(s.romanToInt("XIV")   ==  14)
    assert(s.romanToInt("LVIII") ==  58)
    print(s.romanToInt("LVIII"))

