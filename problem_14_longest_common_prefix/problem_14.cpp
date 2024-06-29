/*
Write a function to find the longest common prefix string amongst an array of strings.

If there is no common prefix, return an empty string "".

 

Example 1:

Input: strs = ["flower","flow","flight"]
Output: "fl"
Example 2:

Input: strs = ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.
 

Constraints:

1 <= strs.length <= 200
0 <= strs[i].length <= 200
strs[i] consists of only lowercase English letters.
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
    std::string longestCommonPrefix(std::vector<std::string>& strs) {
        
        std::string prefix ;

        // over character in strings
        for(size_t i=0; i<200; i++)
        {   
            char c ;
            // over words
            for(size_t j=0; j<strs.size(); j++)
            {   
                // current str is too short
                if(strs[j].size() < i+1)
                {   return prefix ; }

                // char to verify the presence in strings
                if(j == 0)
                {   c = strs[0][i] ; }
                                
                if(strs[j][i] != c)
                {   return prefix ; }
            }

            prefix.push_back(c) ;
        }

        return prefix ;
    }
} ;


int main()
{
    Solution s ;
    std::vector<std::string> strs1{"flower","flow","flight"} ;
    std::vector<std::string> strs2{"dog","racecar","car"} ;
    std::vector<std::string> strs3{""} ;
    assert(s.longestCommonPrefix(strs1) == "fl") ;
    assert(s.longestCommonPrefix(strs2) == "") ;
    assert(s.longestCommonPrefix(strs3) == "") ;
    return 0 ;
} ;
