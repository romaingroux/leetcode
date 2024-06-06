/*
Implement the RandomizedSet class:

RandomizedSet() Initializes the RandomizedSet object.
bool insert(int val) Inserts an item val into the set if not present. Returns true if the item was not present, false otherwise.
bool remove(int val) Removes an item val from the set if present. Returns true if the item was present, false otherwise.
int getRandom() Returns a random element from the current set of elements (it's guaranteed that at least one element exists when this method is called). Each element must have the same probability of being returned.
You must implement the functions of the class such that each function works in average O(1) time complexity.

 

Example 1:

Input
["RandomizedSet", "insert", "remove", "insert", "getRandom", "remove", "insert", "getRandom"]
[[], [1], [2], [2], [], [1], [2], []]
Output
[null, true, false, true, 2, true, false, 2]

Explanation
RandomizedSet randomizedSet = new RandomizedSet();
randomizedSet.insert(1); // Inserts 1 to the set. Returns true as 1 was inserted successfully.
randomizedSet.remove(2); // Returns false as 2 does not exist in the set.
randomizedSet.insert(2); // Inserts 2 to the set, returns true. Set now contains [1,2].
randomizedSet.getRandom(); // getRandom() should return either 1 or 2 randomly.
randomizedSet.remove(1); // Removes 1 from the set, returns true. Set now contains [2].
randomizedSet.insert(2); // 2 was already in the set, so return false.
randomizedSet.getRandom(); // Since 2 is the only number in the set, getRandom() will always return 2.
 

Constraints:

-231 <= val <= 231 - 1
At most 2 * 105 calls will be made to insert, remove, and getRandom.
There will be at least one element in the data structure when getRandom is called.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <random>
#include <cassert>


std::ostream& operator << (std::ostream& stream,
                           const std::vector<int>& v)
{
    for(const auto& x : v)
    {   stream << x << " " ; }
    return stream ;
}

std::ostream& operator << (std::ostream& stream,
                           const std::unordered_map<int, size_t>& m)
{
    for(const auto& p : m)
    {   stream << " (" 
               << p.first << "," 
               << p.second << ") " 
               << std::endl ;
    }
    return stream ;
}




class RandomizedSet {
    public:
        RandomizedSet() 
            : m_values(),
              m_map(),
              m_rand_dev(),
              m_rand_gen(m_rand_dev()),
              m_distr_unif(0,1)
        { ; }
        
        virtual 
        ~RandomizedSet()
        { ; }
        
        bool insert(int val) {
            if(m_map.contains(val))
            {   return false ; }  
            else
            {   m_values.push_back(val) ;
                size_t index = m_values.size() - 1 ;
                m_map[val] = index ;
                return true ;
            }
        }
        
        bool remove(int val) {
            if(m_map.contains(val))
            {   size_t index_val = m_map.at(val) ;
                size_t index_last = m_values.size() - 1 ;

                // swap for O(1) pop_back
                int val_last = m_values[index_last] ;
                m_values[index_last] = val ;
                m_values[index_val] = val_last ;
                m_map.at(val_last) = index_val ;
                // pop
                m_values.pop_back() ;
                m_map.erase(val) ;

                return true ;
            }
            else
            {   return false ; }
        }
        
        int getRandom() {
            // random index
            const int from  = 0;
            const int to    = m_values.size() -1 ;
            // std::random_device                  rand_dev ;
            // std::mt19937                        rand_gen(rand_dev()) ;
            // std::uniform_int_distribution<int>  distr(from, to) ;
            // size_t idx = distr(m_rand_gen) ;
            m_distr_unif.param(
                std::uniform_int_distribution<size_t>::param_type(from, to)) ;

            return m_values[m_distr_unif(m_rand_gen)] ; 
        }

        void print() const
        {   std::cerr << "values : " << m_values << std::endl ;
            std::cerr << "map    : " << m_map << std::endl ;
        }
    
    protected:
        /* The values in the set */
        std::vector<int> m_values ;

        /* A map mapping value with corresponding index in values*/
        std::unordered_map<int, size_t> m_map ;

        /* Number random generator */
        std::random_device m_rand_dev ;
        std::mt19937 m_rand_gen ; 
        std::uniform_int_distribution<size_t> m_distr_unif ;
} ;

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */


int main()
{
    RandomizedSet s ;
    std::cout << s.insert(0) << std::endl ;
    std::cout << s.insert(1) << std::endl ;
    std::cout << s.insert(2) << std::endl ;
    std::cout << s.insert(3) << std::endl ;
    std::cout << s.insert(3) << std::endl ;
    s.print() ;
    std::cout << s.remove(0) << std::endl ;
    s.print() ;
    std::cout << s.remove(1) << std::endl ;
    s.print() ;
    std::cout << s.remove(2) << std::endl ;
    s.print() ;
    std::cout << s.remove(3) << std::endl ;
    s.print() ;
    std::cout << s.remove(3) << std::endl ;
    s.print() ;
    // s.remove(0) ;
    // s.remove(0) ;
    // s.remove(0) ;
    return 0 ;
}