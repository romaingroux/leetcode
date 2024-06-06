/*
Given an array of integers citations where citations[i] is the number of citations a researcher received for their ith paper and citations is sorted in ascending order, return the researcher's h-index.

According to the definition of h-index on Wikipedia: The h-index is defined as the maximum value of h such that the given researcher has published at least h papers that have each been cited at least h times.

You must write an algorithm that runs in logarithmic time.

 

Example 1:

Input: citations = [0,1,3,5,6]
Output: 3
Explanation: [0,1,3,5,6] means the researcher has 5 papers in total and each of them had received 0, 1, 3, 5, 6 citations respectively.
Since the researcher has 3 papers with at least 3 citations each and the remaining two with no more than 3 citations each, their h-index is 3.
Example 2:

Input: citations = [1,2,100]
Output: 2
 

Constraints:

n == citations.length
1 <= n <= 105
0 <= citations[i] <= 1000
citations is sorted in ascending order.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>


std::ostream& operator << (std::ostream& stream,
                           const std::vector<int>& v)
{
    for(const auto& x : v)
    {   stream << x << " " ; }
    return stream ;
}


// [3,0,6,1,5]
// 0 1 3 5 6
//      


class Solution
{
    public:
    
    /*
    int hIndex(std::vector<int>& citations) 
    {
        int n = citations.size();
        int h = 0;
        for(int i=1; i<=n; i++){
            if(citations[n-i] >= i)
                h = i;
        }
        return h;
    }
    */
    int hIndex(std::vector<int>& citations)
    {
        int n = citations.size() ;
        for(int i=0; i<n; i++)
        {   if(citations[i] >= n-i)
            {   return n-i ; }
        }
        return 0 ;
    }
} ;


int main()
{
    
    std::vector<int> citations_1({3,0,6,1,5}) ;
    std::vector<int> citations_2({100}) ;
    std::vector<int> citations_3({11,15}) ;

    Solution s ;
    assert(s.hIndex(citations_1) == 3) ;
    assert(s.hIndex(citations_2) == 1) ;
    assert(s.hIndex(citations_3) == 2) ;

    return 0 ;
} ;
