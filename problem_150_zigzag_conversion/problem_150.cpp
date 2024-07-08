/*
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of 
rows like this: (you may want to display this pattern in a fixed font for better 
legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number 
of rows:

string convert(string s, int numRows);
 

Example 1:

Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"
Example 2:

Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:
P     I    N
A   L S  I G
Y A   H R
P     I
Example 3:

Input: s = "A", numRows = 1
Output: "A"
 

Constraints:

1 <= s.length <= 1000
s consists of English letters (lower-case and upper-case), ',' and '.'.
1 <= numRows <= 1000
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

template<class T>
std::ostream& operator << (std::ostream& stream,
                           const std::vector<std::vector<T>>& m)
{
    for(const auto& row : m)
    {   for(const auto& x : row)
        {   stream << ">" << x << "<\t" ; }
        stream << std::endl ; 
    }
    return stream ;
}


class Solution
{
    public:
    std::string convert(std::string s, int numRows)
    {   if(numRows == 1)
        {   return s ; }
        
        size_t nrows(numRows) ;
        size_t ncols_u(nrows - 1) ;
        // 1. not 1 to force everyhing to floating point div and ceil !
        size_t n_units = ceil(s.size() / (nrows + ncols_u - 1.)) ;
        size_t ncols = ncols_u * n_units ;

        std::vector<std::vector<char>> matrix(nrows, std::vector<char>(ncols, '0')) ;

        // fill matrix
        size_t s_i = 0 ;
        for(size_t n_unit=0; n_unit<n_units; n_unit++)
        {   
            for(size_t ncol_u=0; ncol_u<ncols_u; ncol_u++)
            {   
                size_t j = (n_unit*ncols_u) + ncol_u ;
                for(size_t i=0; i<nrows; i++)
                {   if(s_i >= s.size())
                    {   break ; }

                    if(ncol_u != 0)
                    {   if(i != nrows - ncol_u - 1)
                        {   continue ; }
                    }
                    matrix[i][j] = s[s_i] ;
                    s_i++ ;
                }
            }
        }

        // recontruct string
        std::string s_converted ;
        size_t s_conv_i = 0 ;
        for(size_t i=0; i<nrows; i++)
        {   for(size_t j=0; j<ncols; j++)
            {   
                if(matrix[i][j] != '0')
                {   s_converted.push_back(matrix[i][j]) ;
                    s_conv_i++ ;
                }

            }
        }

        return s_converted ;
    }
} ;


int main()
{
    Solution s ;
    
    std::string s1{"PAYPALISHIRING"} ;
    std::string s2{"A"} ;

    assert(s.convert(s1, 3) == "PAHNAPLSIIGYIR") ;
    assert(s.convert(s1, 4) == "PINALSIGYAHRPI") ;
    assert(s.convert(s2, 1) == "A") ;

    return 0 ;
} ;
