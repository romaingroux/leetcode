/*
Given the head of a linked list, reverse the nodes of the list k at a time, 
and return the modified list.

k is a positive integer and is less than or equal to the length of the 
linked list. If the number of nodes is not a multiple of k then left-out 
nodes, in the end, should remain as it is.

You may not alter the values in the list's nodes, only nodes themselves may 
be changed.

Example 1:
Input: head = [1,2,3,4,5], k = 2
Output: [2,1,4,3,5]


Example 2:
Input: head = [1,2,3,4,5], k = 3
Output: [3,2,1,4,5]
 
Constraints:

The number of nodes in the list is n.
1 <= k <= n <= 5000
0 <= Node.val <= 1000
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


#include <unordered_map>

class Solution {
public:
    /** 
     * Reverse the order of the list by group of k nodes, starting from the 
     * 1st one. If k is not a multiple of the size of the list, the lasting 
     * nodes are left as they were.
     * Works in O(N) time where N is the size of the list.
     * It makes 2 passes over the list, one could be spared as in exercice 92
     * but I was too lazy... 
     */
    ListNode* reverseKGroup(ListNode* head, int k) {

        if(head == nullptr)
        {   return nullptr ; }
        if(head->next == nullptr)
        {   return head ; }

        if(k < 0)
        {   return nullptr ; }

        // maps the index of a node with the node
        std::unordered_map<size_t,ListNode*> map ;

        size_t i = 1 ;
        ListNode* current = head ;
        while(current)
        {   map[i] = current ;
            current = current->next ;
            ++i ;
        }

        // without the prehead nor the postail
        size_t size = i-1 ;

        // reverse each slide [from,to]
        for(size_t from=1,to=from+k-1; to<=size; from+=k,to+=k)
        {
            // swap
            size_t n = to - from + 1 ;
            size_t n_half = n / 2 ;
            for(size_t i=0; i<n_half; ++i)
            {   
                ListNode* ptr_l = map[from+i] ;
                ListNode* ptr_r = map[to-i] ;
                map[from+i] = ptr_r ;
                map[to-i]   = ptr_l ;
            }
        }

        // redo listing
        // this could be merged with the above swap step, as done in exercice 92
        // to gain speed
        for(size_t i=1; i<size; ++i)
        {   map[i]->next = map[i+1] ; 
        }
        map[size]->next = nullptr ;

        return map[1] ;
    }
};


int main()
{
    Solution s ;
    ListNode* l = nullptr ;

    /* insert tests */
    // revert by 1, size of list is multiple of 1
    l = construct_list({1,2,3,4,5,6}) ;
    l = s.reverseKGroup(l,1) ;
    print_list(std::cout, l) ;
    delete_list(l) ; l = nullptr ;

    // revert by 3, size of list is multiple of 3
    l = construct_list({1,2,3,4,5,6}) ;
    l = s.reverseKGroup(l,3) ;
    print_list(std::cout, l) ;
    delete_list(l) ; l = nullptr ;

    // revert by 4, size of list is not multiple of 4
    l = construct_list({1,2,3,4,5,6}) ;
    l = s.reverseKGroup(l,4) ;
    print_list(std::cout, l) ;
    delete_list(l) ; l = nullptr ;

    // revert by 6, this is the size of the list
    l = construct_list({1,2,3,4,5,6}) ;
    l = s.reverseKGroup(l,6) ;
    print_list(std::cout, l) ;
    delete_list(l) ; l = nullptr ;

    return 0 ;
} ;
