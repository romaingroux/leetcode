/*
There are n children standing in a line. Each child is assigned a rating value given in the integer array ratings.

You are giving candies to these children subjected to the following requirements:

Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors.
Return the minimum number of candies you need to have to distribute the candies to the children.

 

Example 1:

Input: ratings = [1,0,2]
Output: 5
Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.
Example 2:

Input: ratings = [1,2,2]
Output: 4
Explanation: You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
The third child gets 1 candy because it satisfies the above two conditions.
 

Constraints:

n == ratings.length
1 <= n <= 2 * 104
0 <= ratings[i] <= 2 * 104
*/

#include <iostream>
#include <vector>
#include <numeric>
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
    int candyBruteForce(std::vector<int>& ratings)
    {   
        size_t n = ratings.size() ;
        std::vector<int> candies(n, 1) ;

        if(n == 1)
        {   return 1 ; }

        bool done(false) ;
        while(not done)
        {   
            done = true ;
            // std::cerr << done << "\ratings " << ratings << std::endl ;
            // std::cerr << done << "\tstart  " << candies << std::endl ;
            if((ratings[0] > ratings[1]) and (candies[0] <= candies[1]))
            {   candies[0] = candies[1] + 1 ; 
                done = false ;
            } 
            for(size_t i=1; i<n-1; i++)
            {
                if((ratings[i] > ratings[i-1]) and (candies[i] <= candies[i-1]))
                {
                    candies[i] = candies[i-1] + 1;
                    done = false ;
                }
                if((ratings[i] > ratings[i+1]) and (candies[i] <= candies[i+1]))
                {
                    candies[i] = candies[i+1] + 1 ;
                    done = false ;
                }
            }
            if((ratings[n-1] > ratings[n-2]) and (candies[n-1] <= candies[n-2]))
            {   candies[n-1] = candies[n-2] + 1 ;
                done = false ;
            }

            // std::cerr << done << "\tend    " << candies << std::endl << std::endl ;
        }

        return std::accumulate(candies.begin(), candies.end(), 0) ;
    }

    int candy(std::vector<int>& ratings)
    {   
        size_t n = ratings.size() ;
        if(n == 1)
        {   return 1 ; }
        std::vector<int> candies(n, 1) ;
        std::vector<int> left_scan(n, 1) ;
        std::vector<int> right_scan(n, 1) ;

        // left scan, compare only with left neighbor
        for(size_t i=1; i<n; i++)
        {   if(ratings[i] > ratings[i-1])
            {   left_scan[i] = left_scan[i-1] + 1 ; }
        }
        // right scan, compare only with right neighbor
        for(int i=n-2; i>=0; i--)
        {   if(ratings[i] > ratings[i+1])
            {   right_scan[i] = right_scan[i+1] + 1 ; }
        }

        for(size_t i=0; i<n; i++)
        {   candies[i] = std::max(left_scan[i], right_scan[i]) ; }

        return std::accumulate(candies.begin(), candies.end(), 0) ;

    }

} ;


int main()
{
    Solution s ;

    std::vector<int> ratings_1 = {1,0,2} ;
    std::vector<int> ratings_2 = {0} ;
    std::vector<int> ratings_3 = {1,2,87,87,87,2,1} ;

    assert(s.candy(ratings_1) == 5) ;
    assert(s.candy(ratings_2) == 1) ;
    assert(s.candy(ratings_3) == 13) ;

    return 0 ;
} ;
