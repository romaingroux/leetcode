/*
Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.

Example 1:
Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.

Example 2:

Input: height = [4,2,0,3,2,5]
Output: 9
 

Constraints:

n == height.length
1 <= n <= 2 * 104
0 <= height[i] <= 105
*/

#include <iostream>
#include <utility>
#include <vector>
#include <cassert>


template<class S, class T>
std::ostream& operator << (std::ostream& stream,
                           const std::pair<S,T>& p)
{
    stream << "(" << p.first << " " << p.second << ")" ;
    return stream ;
}

template<class T>
std::ostream& operator << (std::ostream& stream,
                           const std::vector<T>& v)
{
    for(const auto& x : v)
    {   stream << x << " " ; }
    return stream ;
}


class Solution
{
    public:

    // this solution does not work because it finds local holes (i know...)
    // 2 consecutive holes may be merged together in some cases
    // |     |
    // |  |  |
    //  -- -- holes detected
    // 2  1  2 -> this is actual one single hole
    int trapOld(std::vector<int>& heights)
    {
        
        size_t n = heights.size() ;
        
        // derivative
        std::vector<int> dh(n-1, 0) ;
        std::vector<int> dh_sign(n-1, 0) ;

        for(size_t i=0; i<n-1; i++)
        {   dh[i] = heights[i+1] - heights[i] ; 
            if(dh[i] > 0)
            {   dh_sign[i] = 1 ; }
            else if(dh[i] < 0)
            {   dh_sign[i] = -1 ; }
        }

        // find holes
        bool in_hole(false) ;
        size_t start_i(0) ;
        size_t end_i(0) ;
        // holes [start,end) in heights index
        std::vector<std::pair<size_t,size_t>> holes ;
        for(size_t i=0; i<dh_sign.size()-1; i++)
        {   // decrease -> potential hole start
            if(dh_sign[i] < 0)
            {   if(not in_hole)
                {   // std::cerr << "start hole " << i << std::endl ;
                    start_i = i ; 
                    in_hole = true ;
                }
            }

            // increase -> potential hole end
            if(dh_sign[i] > 0)
            {   if(in_hole)
                {   // std::cerr << "end hole " << i << std::endl ;
                    end_i = i+2 ; 
                    in_hole = false ;
                    holes.push_back(std::make_pair(start_i,end_i)) ;
                }
            }
        }
        // potential last hole end
        if(in_hole)
        {   if(dh_sign[dh_sign.size()-1] > 0)
            {   // std::cerr << "last end hole " << dh_sign.size()-2 << std::endl ;
                in_hole = false ;
                holes.push_back(std::make_pair(start_i,n)) ;
            }
        }

        // hole level, up to this level in heights units
        std::vector<int> holes_levels(holes.size(), 0) ;
        for(size_t i=0; i<holes.size(); i++)
        {   int level = std::min(heights[holes[i].first], 
                                 heights[holes[i].second-1]) ;
            holes_levels[i] = level ;
        }

        int volume(0) ;
        for(size_t i=0; i<holes.size(); i++)
        {
            size_t hole_start = holes[i].first ;
            size_t hole_end   = holes[i].second ;
            int hole_level    = holes_levels[i] ; 
            int hole_volume   = 0 ;
            std::cerr << "hole volume computation" << std::endl ;
            std::cerr << "hole       : " << hole_start << " " << hole_end << std::endl ;
            std::cerr << "hole level : " << hole_level << std::endl ;
            for(size_t j=hole_start+1; j<hole_end-1; j++)
            {   hole_volume += (hole_level - heights[j]) ;
                std::cerr << j << " " << hole_level - heights[j] << std::endl ;
            }

            volume += hole_volume ;
            std::cerr << "hole volume " << hole_volume << std::endl ;
        }

        std::cerr << dh           << std::endl ;
        std::cerr << dh_sign      << std::endl ;
        std::cerr << holes        << std::endl ;
        std::cerr << holes_levels << std::endl ;
        std::cerr << volume << std::endl ;

        return 0 ;
    }

    
    int trap(std::vector<int>& heights)
    {   
        // simpler solution
        // a hole can only contain the minimum volume allowed by its 
        // left and right boundaries
        // 1) let's find each possible left boundary and their allowed level
        // 2) let's find each possible right boundary and their allowed level
        // 3) let's take the minimum for each

        size_t n = heights.size() ;
        
        // scans toward the R (this will be left boundaries)
        int max(0) ;
        std::vector<int> maxs_2_R(n, 0) ;
        for(size_t i=0; i<n; i++)
        {   maxs_2_R[i] = max ;
            if(heights[i] > max)
            {   max = heights[i] ;
                maxs_2_R[i] = -1 ; // this indicates a boundary
            }
        }

        // scans toward the L (this will be right boundaries)
        max = 0 ;
        std::vector<int> maxs_2_L(n, 0) ;
        for(int i=n-1; i>=0; i--)
        {   maxs_2_L[i] = max ;
            if(heights[i] > max)
            {   max = heights[i] ;
                maxs_2_L[i] = -1 ; // this indicates a boundary
            }
        }

        // get the minimal water height allowed by the boundaries
        int volume(0) ;
        for(size_t i=0; i<n; i++)
        {   if(maxs_2_R[i] != -1 and maxs_2_L[i] != -1)
            {   volume += std::min(maxs_2_R[i], maxs_2_L[i]) - heights[i] ; }
        }
        return volume ;
    }
} ;


int main()
{
    Solution s ;
    
    std::vector<int> heights_1 = {4,2,0,3,2,5} ;

    s.trap(heights_1) ;

    return 0 ;
} ;
