/*
Given an input string s, reverse the order of the words.

A word is defined as a sequence of non-space characters. The words in s will be 
separated by at least one space.

Return a string of the words in reverse order concatenated by a single space.

Note that s may contain leading or trailing spaces or multiple spaces between 
two words. The returned string should only have a single space separating the 
words. Do not include any extra spaces.

 

Example 1:

Input: s = "the sky is blue"
Output: "blue is sky the"
Example 2:

Input: s = "  hello world  "
Output: "world hello"
Explanation: Your reversed string should not contain leading or trailing spaces.
Example 3:

Input: s = "a good   example"
Output: "example good a"
Explanation: You need to reduce multiple spaces between two words to a single 
space in the reversed string.
 

Constraints:

1 <= s.length <= 104
s contains English letters (upper-case and lower-case), digits, and spaces ' '.
There is at least one word in s.
 

Follow-up: If the string data type is mutable in your language, can you solve 
it in-place with O(1) extra space?
*/

#include <cassert>
#include <iostream>
#include <vector>
#include <list>
#include <string>

template<class T>
std::ostream& operator << (std::ostream& stream,
                           const std::vector<T>& v)
{
    for(const auto& x : v)
    {   stream << x << " " ; }
    return stream ;
}

template<class T>
std::ostream& operator << (std::ostream& stream,
                           const std::list<T>& l)
{
    for(const auto& x : l)
    {   stream << "<" << x << "> " ; }
    return stream ;
}


class Solution
{
    public:
    std::string reverseWords(std::string s) {
        
        std::list<std::string> words ;
        std::string word ;
        size_t from(0) ;
        size_t to(0) ;
        while(true)
        {   to = s.find(" ", from) ;
            if(to == std::string::npos)
            {   break ; }
            
            word = s.substr(from, to-from) ;
            if(word != "")
            {   words.push_back(word) ;
            }
            from = to + 1 ;
        }
        // last word 
        word = s.substr(from, to-from) ;
        if(word != "")
        {   words.push_back(word) ; }
        
        s.clear() ;
        for(auto i=words.rbegin(); i!=words.rend(); i++)
        {   s.append(*i) ;
            if(i != std::prev(words.rend()))
            { s.append(" ") ; }
        }
        
        return s ;
    }

    std::string reverseWordsSTL(std::string s)
    {
        s.erase(0, s.find_first_not_of(' ' , 0)) ; // leading spaces
        s.erase(s.find_last_not_of(' ')+1) ;       // trailing spaces

        std::cerr << "-" << s << "-" << std::endl ;

        return s ;
    }
} ;


int main()
{
    Solution s ;
    /* insert tests */
    std::string s1{"the sky is blue"} ;
    std::string s2{"  hello world  "} ;
    std::string s3{"a good   example"} ;
    assert(s.reverseWords(s1) == "blue is sky the") ;
    assert(s.reverseWords(s2) == "world hello") ;
    assert(s.reverseWords(s3) == "example good a") ;
    
    // s.reverseWordsSTL(s2) ;

    return 0 ;
} ;
