/*
Insert description
*/

#include <iostream>
#include <vector>


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
    /* insert solution */
} ;


int main()
{
    Solution s ;
    /* insert tests */
    return 0 ;
} ;
