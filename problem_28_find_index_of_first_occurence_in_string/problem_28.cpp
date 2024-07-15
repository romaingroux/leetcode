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
#include <cmath>
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
    int strStrBruteForce(std::string word, std::string pattern)
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

    int strStrSTL(std::string word, std::string pattern)
    {   size_t i = word.find(pattern) ; 
        if(i == std::string::npos)
        {   return -1 ; }
        return i ;
    }


    int hash(const std::string& s, int radix, int mod)
    {
        int h = 0 ;
        int l = s.size() ;

        for(int i=0; i<l; i++)
        {   
            int h_part = (((s[i] - 'a') * (static_cast<int>(pow(radix, l-i-1)))) % mod)  ;
            std::cerr << "contribution s[" << i << "] " << s[i] << " = " << h_part << " : " << s[i] << "- 'a'* pow(" << radix << "," << l << "-" << i << "-1)" << std::endl ;
            h += h_part;
        }
        std::cerr << std::endl ;
        return h ;
    }

    int strStrHash(std::string word, std::string pattern)
    {   
        if(word.size() == 0)
        {   return -1 ; }

        if(word.size() < pattern.size())
        {   return -1 ; }

        // constants for hashing
        int radix = 26;
        int mod = 
        ;
        // long max_weight = 1;

        std::string word_0 = word.substr(0, 4) ;

        int h_word_0 = hash(word_0, radix, mod) ;

        std::cerr << word_0 << " " << h_word_0 << std::endl ;





        /*
        size_t l_pattern = pattern.size() ;
        size_t l_word    = word.size() ;
        std::string subword = word.substr(0, l_pattern) ;

        int h_pattern = hash(pattern, radix, mod) ;
        int h_subword = hash(subword, radix, mod) ;
        
        
        if(h_pattern == h_subword)
        {   return 0 ; }


        for(size_t i=1; i<l_word-l_pattern+1; i++)
        {   
            subword = word.substr(i, l_pattern) ;

            // update hash subword
            h_pattern -= (((word[i-1] - 'a') * 
                            (static_cast<int>(pow(radix, l_pattern-0-1)))) % mod) ;
            h_pattern += (((word[i+l_pattern] - 'a') * 
                            (static_cast<int>(pow(radix, l_pattern-(l_pattern-1)-1))))             % mod) ;

            std::cerr << "-" << word[i-1] << " " << subword << " +" << word[i+l_pattern] << " " << h_pattern << " " << hash(subword, radix, mod) << std::endl ;
        }

        int pattern_hash = hash(pattern, radix, mod) ;
        */
        return -1 ;
    }
} ;


int main()
{
    Solution s ;
    
    // assert(s.strStrSTL( "sadbutsad", "sad") == 0) ;
    // assert(s.strStrSTL( "leetcode", "leeto") == -1) ;
    // assert(s.strStrSTL( "a", "a") == 0) ;
    // assert(s.strStrSTL( "", "leeto") == -1) ;
    // assert(s.strStrSTL( "mississippi", "issip") == 4) ;

    s.strStrHash( "mississippi", "issip") ;

    return 0 ;
} ;
