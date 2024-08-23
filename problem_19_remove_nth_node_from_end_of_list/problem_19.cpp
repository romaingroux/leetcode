/*
Given the head of a linked list, remove the nth node from the end of the 
list and return its head. 

Example 1:
Input: head = [1,2,3,4,5], n = 2
Output: [1,2,3,5]

Example 2:
Input: head = [1], n = 1
Output: []

Example 3:
Input: head = [1,2], n = 1
Output: [1]
 

Constraints:

The number of nodes in the list is sz.
1 <= sz <= 30
0 <= Node.val <= 100
1 <= n <= sz
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
    /**
     * Removes in place the N-th node from the end of a list.
     * Works in O(N) time.
     * @param head the head of the list of interest.
     * @param n the 1-based index of the node to remove, 1 means the last node, 
     * L in a list of lenght L means the 1st node.
     * @returns the head of the list.
     */
    ListNode* 
    removeNthFromEnd(ListNode* head, 
                     int n) {
        
        if(head == nullptr)
        {   return nullptr ; }

        // to map node index with node
        std::unordered_map<size_t,ListNode*> map ;
        
        // prehead
        ListNode* prehead = new ListNode(-1,head) ;
        map[0] = prehead ;
        
        size_t i = 1 ;
        ListNode* current = head ;
        while(current)
        {   map[i] = current ;
            current = current->next ;
            ++i ;
        }
        // size of list without the prehead
        size_t size = i-1 ;

        // remove node of interest
        size_t i_remove = size - n + 1 ;
        // rewire
        // node is either head or in middle
        if(i_remove != size)
        {   map[i_remove-1]->next = map[i_remove+1] ; }
        // node is one before tail and becomes new tail
        else
        {   map[i_remove-1]->next = nullptr ; }
        // free node
        delete map[i_remove] ;
        map[i_remove] = nullptr ;

        // return head
        return prehead->next ;
    }
} ;


int main()
{
    Solution s ;
    /* insert tests */
    ListNode* l = nullptr ;

    // remove head node
    l = construct_list({1,2,3,4,5,6}) ;
    l = s.removeNthFromEnd(l,6) ;
    print_list(std::cout, l) ;
    delete_list(l) ; l = nullptr ;
    
    // remove middle node
    l = construct_list({1,2,3,4,5,6}) ;
    l = s.removeNthFromEnd(l,3) ;
    print_list(std::cout, l) ;
    delete_list(l) ; l = nullptr ;

    // remove tail node
    l = construct_list({1,2,3,4,5,6}) ;
    l = s.removeNthFromEnd(l,1) ;
    print_list(std::cout, l) ;
    delete_list(l) ; l = nullptr ;

    // remove only node in list
    l = construct_list({1}) ;
    l = s.removeNthFromEnd(l,1) ;
    print_list(std::cout, l) ;
    delete_list(l) ; l = nullptr ;

    return 0 ;
} ;
