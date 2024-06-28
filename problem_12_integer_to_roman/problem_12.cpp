/*
Seven different symbols represent Roman numerals with the following values:

Symbol	Value
I	1
V	5
X	10
L	50
C	100
D	500
M	1000
Roman numerals are formed by appending the conversions of decimal place values from highest to lowest. Converting a decimal place value into a Roman numeral has the following rules:

If the value does not start with 4 or 9, select the symbol of the maximal value that can be subtracted from the input, append that symbol to the result, subtract its value, and convert the remainder to a Roman numeral.
If the value starts with 4 or 9 use the subtractive form representing one symbol subtracted from the following symbol, for example, 4 is 1 (I) less than 5 (V): IV and 9 is 1 (I) less than 10 (X): IX. Only the following subtractive forms are used: 4 (IV), 9 (IX), 40 (XL), 90 (XC), 400 (CD) and 900 (CM).
Only powers of 10 (I, X, C, M) can be appended consecutively at most 3 times to represent multiples of 10. You cannot append 5 (V), 50 (L), or 500 (D) multiple times. If you need to append a symbol 4 times use the subtractive form.
Given an integer, convert it to a Roman numeral.

 

Example 1:

Input: num = 3749

Output: "MMMDCCXLIX"

Explanation:

3000 = MMM as 1000 (M) + 1000 (M) + 1000 (M)
 700 = DCC as 500 (D) + 100 (C) + 100 (C)
  40 = XL as 10 (X) less of 50 (L)
   9 = IX as 1 (I) less of 10 (X)
Note: 49 is not 1 (I) less of 50 (L) because the conversion is based on decimal places
Example 2:

Input: num = 58

Output: "LVIII"

Explanation:

50 = L
 8 = VIII
Example 3:

Input: num = 1994

Output: "MCMXCIV"

Explanation:

1000 = M
 900 = CM
  90 = XC
   4 = IV
 

Constraints:

1 <= num <= 3999
*/

#include <iostream>
#include <vector>
#include <string>
#include <cassert>



std::ostream& operator << (std::ostream& stream,
                           const std::vector<int>& v)
{
    for(const auto& x : v)
    {   stream << x << " " ; }
    return stream ;
}


class Solution
{
    public:
    std::string intToRoman(int num) {
        
        std::vector<std::pair<std::string,int>> map = {
            {"I",   1},
            {"IV",  4},
            {"V",   5},
            {"IX",  9},
            {"X",  10},
            {"XL", 40},
            {"L" , 50},
            {"XC", 90},
            {"C", 100},
            {"CD",400},
            {"D", 500},
            {"CM",900},
            {"M",1000}} ;

        std::string roman ;
        
        size_t i = map.size() - 1 ;
        while(num != 0)
        {   

            int base      = map[i].second ;
            std::string c = map[i].first ;
            if(num >= base)
            {   int n = num / base ;
                
                // only these can have multiple 
                // I -> up to III
                // X -> up to XXX
                // C -> up to CCC
                // M -> up to ...
                if((base == 1 or base == 10 or base == 100 or base == 1000) and
                   (n > 1))
                {   roman.append(std::string(n, c[0])) ; }
                else
                {   roman.append(c) ; }

                num -= (n*base) ;
            }    
            i-- ;
        }
        return roman ;
    }
} ;


int main()
{
    Solution s ;
    
    assert(s.intToRoman(1)    == std::string("I")) ;
    assert(s.intToRoman(2)    == std::string("II")) ;
    assert(s.intToRoman(3)    == std::string("III")) ;
    assert(s.intToRoman(4)    == std::string("IV")) ;
    assert(s.intToRoman(5)    == std::string("V")) ;
    assert(s.intToRoman(6)    == std::string("VI")) ;
    assert(s.intToRoman(9)    == std::string("IX")) ;
    assert(s.intToRoman(10)   == std::string("X")) ;
    assert(s.intToRoman(11)   == std::string("XI")) ;
    assert(s.intToRoman(19)   == std::string("XIX")) ;
    assert(s.intToRoman(20)   == std::string("XX")) ;
    assert(s.intToRoman(40)   == std::string("XL")) ;
    assert(s.intToRoman(49)   == std::string("XLIX")) ;
    assert(s.intToRoman(50)   == std::string("L")) ;
    assert(s.intToRoman(51)   == std::string("LI")) ;
    assert(s.intToRoman(90)   == std::string("XC")) ;
    assert(s.intToRoman(99)   == std::string("XCIX")) ;
    assert(s.intToRoman(4000) == std::string("MMMM")) ;


    return 0 ;
} ;
