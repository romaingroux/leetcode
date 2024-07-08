/*
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
    int strStrOld(std::string word, std::string pattern)
    {   
        if(word.size() == 0)
        {   return -1 ; }

        if(word.size() < pattern.size())
        {   return -1 ; }

        for(size_t i=0; i<word.size() - pattern.size() + 1; )
        {   
            bool found = true ;
            for(size_t j=0; j<pattern.size(); j++)
            {   
                std::cerr << "i: " << i << " " << " j: " << j << std::endl ;
                std::cerr << "word:    " << word[i+j] << std::endl ;
                std::cerr << "pattern: " << pattern[j] << std::endl ;
                std::cerr << std::endl ;

                if(word[i+j] != pattern[j])
                {   i++ ;
                    found = false ;
                    break ;
                }
            }

            if(found)
            {   return i ; }
        }

        return -1 ;
    }

    int strStr(std::string word, std::string pattern)
    {   int i = word.find(pattern) ; 
        if(i == std::string::npos)
        {   return -1 ; }
        return i ;
    
    }
} ;


int main()
{
    Solution s ;
    
    // assert(s.strStr( "sadbutsad", "sad") == 0) ;
    // assert(s.strStr( "leetcode", "leeto") == -1) ;
    // assert(s.strStr( "a", "a") == 0) ;
    // assert(s.strStr( "", "leeto") == -1) ;
    assert(s.strStr( "mississippi", "issip") == 4) ;

    return 0 ;
} ;
