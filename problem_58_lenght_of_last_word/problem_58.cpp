/*
Given a string s consisting of words and spaces, return the length of the last word in the string.

A word is a maximal 
substring
 consisting of non-space characters only.

 

Example 1:

Input: s = "Hello World"
Output: 5
Explanation: The last word is "World" with length 5.
Example 2:

Input: s = "   fly me   to   the moon  "
Output: 4
Explanation: The last word is "moon" with length 4.
Example 3:

Input: s = "luffy is still joyboy"
Output: 6
Explanation: The last word is "joyboy" with length 6.
 

Constraints:

1 <= s.length <= 104
s consists of only English letters and spaces ' '.
There will be at least one word in s.
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


class Solution {
    public:
    int lengthOfLastWord(std::string s) {
        
        int l = 0 ;
        int i = s.size() - 1 ;
        bool find_last_word(false) ;

        while(i >= 0)
        {   
            // beginning of last world
            if(not find_last_word)
            {   if(s[i] != ' ')
                {   find_last_word = true ; 
                    l++ ;
                }
            }
            // end of last word
            else if(find_last_word and s[i] == ' ')
            {   break ; }
            else
            {   l++ ; }
            i-- ;
        }
        return l ;
    }
};


int main()
{
    Solution s ;
    
    assert(s.lengthOfLastWord("") == 0) ;
    assert(s.lengthOfLastWord("Hello World") == 5) ;
    assert(s.lengthOfLastWord("HelloWorld") == 10) ;
    assert(s.lengthOfLastWord("Hello World ") == 5) ;
    assert(s.lengthOfLastWord("   fly me   to   the moon  ") == 4) ;
    assert(s.lengthOfLastWord("luffy is still joyboy") == 6) ;

    return 0 ;
} ;
