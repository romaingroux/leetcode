/*
Given the head of a linked list and a value x, partition it such that all nodes 
less than x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two 
partitions.


Example 1:
Input: head = [1,4,3,2,5,2], x = 3
Output: [1,2,2,4,3,5]

Example 2:
Input: head = [2,1], x = 2
Output: [1,2]
 

Constraints:
The number of nodes in the list is in the range [0, 200].
-100 <= Node.val <= 100
-200 <= x <= 200
*/

#include <iostream>
#include <vector>
#include <unordered_map>


/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
} ;


std::ostream& 
operator << (std::ostream& stream, 
             const ListNode& node)
{
    std::string next_str = node.next == nullptr ? 
                            "NONE" :
                            std::to_string(
                                (unsigned long long)(void**)node.next) ;
    stream << "(" << node.val << "," << next_str << ")" ;
    return stream ;
}

/**
 * Construct a linked list from the array of values.
 * All nodes are dynamically allocated and need to be deleted afterward!
 * @param values the values of the nodes.
 * @returns A pointer to the head of the list.
 */
ListNode*
construct_list(const std::vector<int>& values)
{   
    if(values.size() == 0)
    {   return nullptr ; }

    ListNode* head = new ListNode(values[0]) ;
    ListNode* current = head ;
    for(size_t i=1; i<values.size(); i++)
    {   current->next = new ListNode(values[i]) ;
        current = current->next ;
    }
    return head ;
}

/**
 * Deletes all nodes within a list.
 * @param head the head of the list of interest.
 */
void
delete_list(ListNode* head)
{
    ListNode* current = head ;
    while(current)
    {   ListNode* next = current->next ;
        if(current != nullptr)
        {   delete current ; }
        current = next ;
    }
}


/**
 * Prints a linked list on the given stream.
 * @param stream the stream to print to.
 * @param head the head of the list.
 * @return the stream.
 */
std::ostream&
print_list(std::ostream& stream, ListNode* head)
{
    ListNode* current = head ;
    while(current != nullptr)
    {   stream << *current ;
        if(current->next != nullptr)
        {   stream << "," ; }
        current = current->next ;
    }
    stream << std::endl ;
    return stream ;
}


class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        if(head == nullptr)
        {   return nullptr ; }
        
        // prehead
        ListNode* prehead = new ListNode(-1,head) ;

        // map node index in list with node
        std::unordered_map<size_t,ListNode*> map_index ;
        map_index[0] = prehead ;  // prehead
        // contains the index (in order) of nodes < x
        std::vector<size_t> is_smaller ;
        // contains the index (in order) of nodes >= x
        std::vector<size_t> is_bigger ;

        // parse list from head to tail, fill map and vector and remember size
        ListNode* current = head ;
        size_t size = 1 ;
        while(current)
        {   map_index[size] = current ;
            
            if(current->val < x)
            {   is_smaller.push_back(size) ; }
            else
            {   is_bigger.push_back(size) ; }

            current = current->next ;
            ++size ;
        }

        // rewire < x
        bool has_smaller = is_smaller.size() ;
        if(has_smaller)
        {   for(size_t i=0; i<is_smaller.size()-1; i++)
            {   
                size_t i_curr = is_smaller[i] ;
                size_t i_next = is_smaller[i+1] ;
                map_index[i_curr]->next = map_index[i_next] ;
            }
        }
        // rewire >= x
        bool has_bigger = is_bigger.size() ;
        if(has_bigger)
        {   for(size_t i=0; i<is_bigger.size()-1; i++)
            {   
                size_t i_curr = is_bigger[i] ;
                size_t i_next = is_bigger[i+1] ;
                map_index[i_curr]->next = map_index[i_next] ;
            }
        }

        // rewire both parts
        // nodes < x and nodes >= x
        if(has_smaller and has_bigger)
        {   
            size_t i_smaller = is_smaller.back() ;
            size_t i_bigger  = is_bigger.front() ;
            size_t i_head = is_smaller.front() ;
            size_t i_tail = is_bigger.back() ;
            map_index[0]->next = map_index[i_head] ;
            map_index[i_smaller]->next = map_index[i_bigger] ;
            map_index[i_tail]->next = nullptr ;
        }
        // only nodes < x
        else if(has_smaller)
        {   size_t i_head = is_smaller.front() ;
            size_t i_tail = is_smaller.back() ;
            map_index[0]->next = map_index[i_head] ;
            map_index[i_tail]->next = nullptr ;
        }
        // only nodes >= x
        else if(has_smaller)
        {   size_t i_head = is_bigger.front() ;
            size_t i_tail = is_bigger.back() ;
            map_index[0]->next = map_index[i_head] ;
            map_index[i_tail]->next = nullptr ;
        }

        ListNode* new_head = map_index[0]->next ;

        delete prehead ;
        prehead = nullptr ;
        map_index[0] = nullptr ;

        return new_head ;
    }
} ;


int main()
{
    Solution s ;
    ListNode* l = nullptr ;

    /* insert tests */
    // [1,2,2,4,3,5]
    l = construct_list({1,4,3,2,5,2}) ; 
    l = s.partition(l, 3)  ;
    print_list(std::cout, l) ;
    delete_list(l) ; l = nullptr ;

    // [1,2]
    l = construct_list({2,1}) ;
    l = s.partition(l, 2) ;
    print_list(std::cout, l) ;
    delete_list(l) ; l = nullptr ;

    return 0 ;
} ;
