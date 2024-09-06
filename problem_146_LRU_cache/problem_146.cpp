/*
Design a data structure that follows the constraints of a Least Recently Used 
(LRU) cache.

Implement the LRUCache class:

LRUCache(int capacity) Initialize the LRU cache with positive size capacity.

int get(int key) Return the value of the key if the key exists, otherwise 
return -1.

void put(int key, int value) Update the value of the key if the key exists. 
Otherwise, add the key-value pair to the cache. If the number of keys exceeds 
the capacity from this operation, evict the least recently used key.

The functions get and put must each run in O(1) average time complexity.

 

Example 1:

Input
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, null, -1, 3, 4]

Explanation
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // cache is {1=1}
lRUCache.put(2, 2); // cache is {1=1, 2=2}
lRUCache.get(1);    // return 1
lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
lRUCache.get(2);    // returns -1 (not found)
lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
lRUCache.get(1);    // return -1 (not found)
lRUCache.get(3);    // return 3
lRUCache.get(4);    // return 4
 

Constraints:

1 <= capacity <= 3000
0 <= key <= 104
0 <= value <= 105
At most 2 * 105 calls will be made to get and put.
*/


#include <cassert>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <stdexcept>


template<class T,class S>
std::ostream& operator << (std::ostream& stream,
                           const std::pair<T,S>& p)
{   stream << "<" << p.first << "," << p.second << ">" ;
    return stream ;
}

template<class T>
std::ostream& operator << (std::ostream& stream,
                           const std::vector<T>& v)
{
    if(v.size() == 0)
    {   return stream ; }

    for(size_t i=0; i<v.size()-1; ++i)
    {   stream << v[i] << "," ; }

    stream << v.back() ;
        return stream ;
}



/**
 * Implements a doubly linked list node.
 */
struct ListNodeDouble {
    int key ;
    int val ;
    ListNodeDouble *prev ;
    ListNodeDouble *next ;
    
    ListNodeDouble() 
        : key(0), val(0), prev(nullptr), next(nullptr)
    {}
    
    ListNodeDouble(int key, int val)
        : key(key), val(val), prev(nullptr), next(nullptr)
    {}
    
    ListNodeDouble(int key, int val, ListNodeDouble* prev, ListNodeDouble *next)
        : key(key), val(val), prev(prev), next(next)
    {}
} ;


/**
 * Implements a LRU cache.
 * The key value pairs are stored in an unordered map and in a  linked list. 
 * The linked list node contains the values and the order of the values from 
 * most ancient (head) to most recent (tail). The linked list has a prehead. 
 * The key are stored as the key of the unordered map which values are the 
 * linked list nodes.
 * The key are 
 */
class LRUCache {
    public:
        /** 
         * Constructor.
         * @param capacity LRU cache capacity.
         */
        LRUCache(int capacity)
            : m_capacity(capacity),
              m_size(0),
              m_map(),
              m_list_prehead(nullptr),
              m_list_posttail(nullptr)
        {   if(capacity == 0)
            {   char msg[4096] ;
                sprintf(msg, "capacity (%d) must be > 0", capacity) ;
                throw std::invalid_argument(msg) ; 
            }

            // init list prehead and posttail
            // it does not hold any node (value) yet
            // dont store prehead and posttail in map, they don't hold values
            m_list_prehead = new ListNodeDouble( -1,-1,nullptr,nullptr) ; 
            m_list_posttail = new ListNodeDouble(-1,-1,nullptr,nullptr) ;
            m_list_prehead->next = m_list_posttail ;
            m_list_posttail->prev = m_list_prehead ;
        }

        ~LRUCache()
        {   this->delete_list() ; 
            m_list_prehead = nullptr ;
            m_list_posttail = nullptr ;
        }
        
        /**
         * Returns the value associated with the given key and updates the 
         * cache.
         * @param key the key of interest.
         * @returns The value associated with this key, -1 if no such key 
         * was found.
         */
        int get(int key) 
        {   
            const auto iter = m_map.find(key) ;
            
            // key found
            if(iter != m_map.end())
            {   // rewire and make value most recent (tail of list)
                ListNodeDouble* node = this->pop(key) ;
                this->push_back(node) ;
                return node->val ;
            }
            // key not found
            {return -1 ; }
        }
        
        /**
         * Wrapper around get(int,int) using a vector as argument.
         * Returns the value associated with the given key and updates the 
         * cache.
         * @param args The vector containing the key of interest.
         * @returns The value associated with this key, -1 if no such key 
         * was found.
         */
        int get(const std::vector<int>& args)
        {   return this->get(args[0]) ; }

        /**
         * Inserts the given key-value pair. This given pair becomes the most 
         * recently used. If the cache is at full capacity, evicts the least 
         * recently used key-value pair.
         * @param key the key of interest.
         * @param value the value of interest.
         */
        void put(int key, int value) 
        {   // is it a replacement ?
            // y -> replace
            // no 
            //  -> is there room ?
            //      y -> push_back
            //      n -> remove most ancient key and push_back

            auto iter = m_map.find(key) ;
            
            // replace value
            if(iter != m_map.end())
            {
                m_map[key]->val = value ;
                ListNodeDouble* node = this->pop(key) ;
                this->push_back(node) ;
            }
            // insert new key
            else
            {   // free room
                if(m_size < m_capacity)
                {   ListNodeDouble* node = new ListNodeDouble(key, value) ;
                    this->push_back(node) ;
                    m_size++ ;
                }
                // pop most ancient value and insert new one
                else
                {   
                    ListNodeDouble* head = m_list_prehead->next ;
                    this->pop(head->key) ;
                    delete head ; head = nullptr ;
                    ListNodeDouble* node = new ListNodeDouble(key,value) ;
                    this->push_back(node) ;
                }

            }
        }
        
        /**
         * Wrapper around put(int,int) using a vector as arguments.
         * Inserts the given key-value pair. This given pair becomes the most 
         * recently used. If the cache is at full capacity, evicts the least 
         * recently used key-value pair.
         * @param key the key of interest.
         * @param value the value of interest.
         */
        void put(const std::vector<int>& args)
        {   return this->put(args[0], args[1]) ; }


        /**
         * Returns the content of the cache as a list of pairs key,value 
         * from most ancient the most recent element.
         * @returns the list of key,value pairs.
         */
        std::vector<std::pair<int,int>>
        to_list() const
        {   
            std::vector<std::pair<int,int>> l(m_size) ;

            if(m_size == 0)
            {   return l ; }

            size_t i = 0 ;
            ListNodeDouble* current = m_list_prehead ;
            while(current->next)
            {
                l[i] = std::make_pair(current->next->key,
                                      current->next->val) ;
                current = current->next ;
                ++i ; 
            }
            return l ;
        }
    
    protected:
        /**
         * Removes the node associated with the given key from the list and 
         * map.
         * It does not update m_size !
         * @param key the key of interest.
         * @returns a pointer to the node popped. The node is still allocated !
         * If the key could no be found, nullptr is returned.
         */
        ListNodeDouble* pop(int key)
        {   ListNodeDouble* ptr ;

            const auto iter = m_map.find(key) ;
            if(iter == m_map.end())
            {   ptr = nullptr ; }
            else
            {   ptr = iter->second ;
                // remove from list
                ListNodeDouble* prev = ptr->prev ;
                ListNodeDouble* next = ptr->next ;
                prev->next = next ;
                next->prev = prev ;
                // remove from map 
                m_map.erase(key) ;
            }
            return ptr ;
        }

        /**
         * Pushes the given node at the back of the list (tail, most recent 
         * value) and stores associated with its key in the map.
         * If key is already inside map, replaces the corresponding value.
         * @param key the key to associate the node with.
         * @param node the node of interest.
         */
        void push_back(ListNodeDouble* node)
        {   
            // store in map, replace if already here
            m_map[node->key] = node ;
            // store in list
            // current tail
            ListNodeDouble* tail = m_list_posttail->prev ;
            // replaces tail
            tail->next = node ;
            node->prev = tail ;
            node->next = m_list_posttail ;
            m_list_posttail->prev = node ;
        }

        /**
         * Frees the memory allocated for the list, including prehead and 
         * posttail and set m_list_prehead and m_list_postail to nullptr.
         */
        void delete_list()
        {   
            ListNodeDouble* current = m_list_prehead ;
            ListNodeDouble* next = nullptr ;
            while(current->next)
            {   next = current->next ;
                delete current ;
                current = nullptr ;
                current = next ;
            }
            // posttail
            delete current ;
            current = nullptr ;
            m_list_prehead = nullptr ;
            m_list_posttail = nullptr ;
        }

        // cache capacity
        size_t m_capacity ;
        // cache current size
        size_t m_size ;
        // maps key with corresponding node
        std::unordered_map<int,ListNodeDouble*> m_map ;
        // prehead node of value list, head is next if size > 0
        ListNodeDouble* m_list_prehead ;
        // posttail node of value list, tail is prev if size > 0
        ListNodeDouble* m_list_posttail ;

} ;


// pointer to a method on LRUCache
typedef void (LRUCache::*LRUFnPointer)(void);



int main()
{
    
    /* insert tests */
    std::vector<std::pair<int,int>> l ;

    
    // ["LRUCache", "put",   "put",  "get", "put",  "get", "put",  "get", "get", "get"]
    // [ [2],        [1, 1], [2, 2], [1],   [3, 3], [2],   [4, 4], [1],   [3],   [4]]
    // Output
    // [null,        null,   null,    1,    null,   -1,    null,   -1,    3,     4]
    LRUCache lru_cache(2) ;
    
    // cache is {}
    std::vector<std::pair<int,int>> l0 ; 
    assert(lru_cache.to_list()== l0) ;

    // cache is {1=1}
    lru_cache.put(1,1) ;
    l = {{1,1}} ; 
    assert(lru_cache.to_list()== l) ;

    // cache is {1=1, 2=2}
    lru_cache.put(2,2) ;
    l = {{1,1},{2,2}} ; 
    assert(lru_cache.to_list()== l) ;

    // cache is {2=2, 1=1}
    assert(lru_cache.get(1) ==  1);
    l = {{2,2},{1,1}} ; 
    assert(lru_cache.to_list()== l) ;

    // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
    lru_cache.put(3,3) ;
    l = {{1,1},{3,3}} ; 
    assert(lru_cache.to_list()== l) ;

    // return -1 (not found)
    assert(lru_cache.get(2) == -1) ;

    // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
    lru_cache.put(4,4) ;
    l = {{3,3},{4,4}} ; 
    assert(lru_cache.to_list()== l) ;

     // return -1 (not found)
    assert(lru_cache.get(1) == -1) ;

    assert(lru_cache.get(3) == 3) ;
    assert(lru_cache.get(4) == 4) ;
    
    

    // ["LRUCache","get","put","get","put","put","get","get"]
    // [[2],        [2] ,[2,6], [1], [1,5], [1,2],[1],  [2]]
    // [null,       -1,   null, -1,   null,  null, 2,    6]
    // LRUCache lru_cache2(2) ;
    // lru_cache2.get(2) ;
    // lru_cache2.put(2,6) ;
    // std::cout << lru_cache2.to_list() << std::endl ;
    // lru_cache2.get(1) ;
    // lru_cache2.put(1,5) ;
    // std::cout << lru_cache2.to_list() << std::endl ;
    // lru_cache2.put(1,2) ;
    // std::cout << lru_cache2.to_list() << std::endl ;
    // lru_cache2.get(1) ;
    // std::cout << lru_cache2.to_list() << std::endl ;
    // lru_cache2.get(2) ;
    // std::cout << lru_cache2.to_list() << std::endl ;


    return 0 ;
} ;
