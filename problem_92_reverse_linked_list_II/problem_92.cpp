/*
Given the head of a singly linked list and two integers left and right 
where left <= right, reverse the nodes of the list from position left to 
position right, and return the reversed list.
 

Example 1:

Input: head = [1,2,3,4,5], left = 2, right = 4
Output: [1,4,3,2,5]


Example 2:

Input: head = [5], left = 1, right = 1
Output: [5]
 

Constraints:

The number of nodes in the list is n.
1 <= n <= 500
-500 <= Node.val <= 500
1 <= left <= right <= n
 

Follow up: Could you do it in one pass?
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
     * Reverses in place the order of the nodes located between indices 
     * [left,right]. Both index are 1-based, the nodes are numbered 
     * 1->2->3->..., starting from the head (1).
     * Works in O(N) time where N is the list length.
     * @param head the head of the list of interest.
     * @param left the 1-based index of the leftmost node to reverse
     * @param right the 1-based index of the rightmost node to reverse
     * @returns the head of the list.
     */
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        
        if(head == nullptr)
        {   return nullptr ; }

        std::unordered_map<size_t,ListNode*> map ;

        // associate each node with its index
        ListNode* current = head ;
        size_t i = 1 ;
        while(current)
        {   
            map[i] = current ;
            current = current->next ;
            ++i ;
        }
        size_t size = i ;

        // number of nodes to reverse
        size_t n = right - left + 1 ;
        // only go to half this number and swap
        // size_t n_half = (n + 2 - 1) / 2 ; // ceil of (n/2)
        size_t n_half = n / 2 ;
        for(size_t i=0; i<n_half; ++i)
        {   // swap
            // std::cerr << "swap L " << left+i << " <-> " << right-i << " R" << std::endl ; 
            ListNode* node_l = map[left+i] ;
            ListNode* node_r = map[right-i] ;
            map[left+i]  = node_r ;
            map[right-i] = node_l ;

            // udpdate next of left node
            // it is not the head so it has a previous node
            if(left+i != 1)
            {   // std::cerr << "rewire " << left+i-1 << "->" << left+i << std::endl ; 
                map[left+i-1]->next = map[left+i] ;
            }
            // it is not the last so it has a next node
            if(left+i != size)
            {   // std::cerr << "rewire " << left+i << "->" << left+i+1 << std::endl ; 
                map[left+i]->next = map[left+i+1] ;
            }
            // it is the tail
            else
            {   // std::cerr << "rewire " << left+i << "->NONE" << std::endl ;
                map[left+i]->next = nullptr ;
            }

            // udpdate next of right node
            // it is not the head so it has a previous node
            if(right-i != 1)
            {   // std::cerr << "rewire " << right-i-1 << "->" << right-i << std::endl ; 
                map[right-i-1]->next = map[right-i] ;
            }
            // it is not the last so it has a next node
            if(right-i != size)
            {   // std::cerr << "rewire " << right-i << "->" << right-i+1 << std::endl ;
                map[right-i]->next = map[right-i+1] ; 
            }
            // it is the tail
            else
            {   // std::cerr << "rewire " << right-i << "->NONE" << std::endl ;
                map[right-i]->next = nullptr ;
            }
           
        }

        return map[1] ;
    }
};


int main()
{
    Solution s ;
    ListNode* l = nullptr ;

    /* insert tests */
    // reverse in middle, odd number of items
    l = construct_list({1,2,3,4,5,6}) ;
    l = s.reverseBetween(l,2,4) ;
    print_list(std::cout, l) ;
    delete_list(l) ;
    l = nullptr ;

    // reverse in middle, even number of items
    l = construct_list({1,2,3,4,5,6}) ;
    l = s.reverseBetween(l,2,5) ;
    print_list(std::cout, l) ;
    delete_list(l) ;
    l = nullptr ;
    
    // reverse at head, odd number of items
    l = construct_list({1,2,3,4,5,6}) ;
    l = s.reverseBetween(l,1,3) ;
    print_list(std::cout, l) ;
    delete_list(l) ;
    l = nullptr ;

    // reverse at head, even number of items
    l = construct_list({1,2,3,4,5,6}) ;
    l = s.reverseBetween(l,1,4) ;
    print_list(std::cout, l) ;
    delete_list(l) ;
    l = nullptr ;

    // reverse at tail, odd number of items
    l = construct_list({1,2,3,4,5,6}) ;
    l = s.reverseBetween(l,4,6) ;
    print_list(std::cout, l) ;
    delete_list(l) ;
    l = nullptr ;

    // reverse at tail, even number of items
    l = construct_list({1,2,3,4,5,6}) ;
    l = s.reverseBetween(l,3,6) ;
    print_list(std::cout, l) ;
    delete_list(l) ;
    l = nullptr ;

    return 0 ;
} ;
