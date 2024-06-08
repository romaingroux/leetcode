/*
There are n gas stations along a circular route, where the amount of gas at the ith station is gas[i].

You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from the ith station to its next (i + 1)th station. You begin the journey with an empty tank at one of the gas stations.

Given two integer arrays gas and cost, return the starting gas station's index if you can travel around the circuit once in the clockwise direction, otherwise return -1. If there exists a solution, it is guaranteed to be unique

 

Example 1:

Input: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
Output: 3
Explanation:
Start at station 3 (index 3) and fill up with 4 unit of gas. Your tank = 0 + 4 = 4
Travel to station 4. Your tank = 4 - 1 + 5 = 8
Travel to station 0. Your tank = 8 - 2 + 1 = 7
Travel to station 1. Your tank = 7 - 3 + 2 = 6
Travel to station 2. Your tank = 6 - 4 + 3 = 5
Travel to station 3. The cost is 5. Your gas is just enough to travel back to station 3.
Therefore, return 3 as the starting index.
Example 2:

Input: gas = [2,3,4], cost = [3,4,3]
Output: -1
Explanation:
You can't start at station 0 or 1, as there is not enough gas to travel to the next station.
Let's start at station 2 and fill up with 4 unit of gas. Your tank = 0 + 4 = 4
Travel to station 0. Your tank = 4 - 3 + 2 = 3
Travel to station 1. Your tank = 3 - 3 + 3 = 3
You cannot travel back to station 2, as it requires 4 unit of gas but you only have 3.
Therefore, you can't travel around the circuit once no matter where you start.
 

Constraints:

n == gas.length == cost.length
1 <= n <= 105
0 <= gas[i], cost[i] <= 104*/

#include <iostream>
#include <vector>
#include <limits>


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
    int canCompleteCircuit(std::vector<int>& gas, 
                           std::vector<int>& cost)
    {   size_t n = gas.size() ;
        
        int gain_total = 0 ;
        std::vector<int> gains(n) ;
        for(size_t i=0; i<n; i++)
        {   gains[i] = gas[i] - cost[i] ; 
            gain_total += gains[i] ;
        }
        
        // no path through all
        if(gain_total < 0)
        {   return -1 ; }

        // find segments
        // segments are [start, end)
        int gain_current = 0 ;
        std::vector<int> segments_starts ;
        std::vector<int> segments_ends   ;
        std::vector<int> segments_gains ;

        segments_starts.push_back(0) ;
        for(size_t i=0; i<n; i++)
        {   gain_current += gains[i] ; 
            if(gain_current < 0)
            {   segments_ends.push_back(i+1) ;
                segments_gains.push_back(gain_current) ;
                gain_current = 0 ;
                segments_starts.push_back(i+1) ;
            }
        }
        segments_ends.push_back(n) ;
        segments_gains.push_back(gain_current) ;

        // find max segment gain to start from
        int max_index(-1) ;
        int max_value(std::numeric_limits<int>::min()) ;
        for(size_t i=0; i<segments_gains.size(); i++)
        {   if(segments_gains[i] > max_value)
            {   max_value = segments_gains[i] ;
                max_index = i ;
            }
        }

        return segments_starts[max_index] ;
    }
} ;


int main()
{
    Solution s ;
    
    std::vector<int> gas_1  = {1,2,3,4,5} ;
    std::vector<int> cost_1 = {3,4,5,1,2} ;

    s.canCompleteCircuit(gas_1, cost_1) ;

    return 0 ;
} ;
