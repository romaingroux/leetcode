/*
Given the head of a linked list, rotate the list to the right by k places.

Example 1:
Input: head = [1,2,3,4,5], k = 2
Output: [4,5,1,2,3]

Example 2:
Input: head = [0,1,2], k = 4
Output: [2,0,1]
 
Constraints:
The number of nodes in the list is in the range [0, 500].
-100 <= Node.val <= 100
0 <= k <= 2 * 109
*/

#include <iostream>
#include <vector>


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
     * Rotates the list in place by K steps to the right.
     * @param head the head of the list.
     * @param k the number of steps.
     * @returns the new list head.
     */
    ListNode* 
    rotateRight(ListNode* head, int k)
    {
        if(head == nullptr)
        {   return nullptr ; }

        if(k == 0)
        {   return head ; }

        // circularize and measure size
        int size = 1 ;
        ListNode* current = head ;
        while(current)
        {   // tail
            if(current->next == nullptr)
            {   current->next = head ; 
                break ;
            }
            current = current->next ;
            size++ ;
        }

        // in case K is bigger than size
        k = k % size ;

        // predecessor of new head and cut the next to make it the new tail
        current = head ;
        for(int i=0; i<size-k-1; ++i)
        {   current = current->next ; }
        head = current->next ;
        current->next = nullptr ;

        return head ;
    }
};


int main()
{
    Solution s ;
    ListNode* l = nullptr ;
    
    /* insert tests */
    // [1,2]
    l = construct_list({1,2}) ;
    l = s.rotateRight(l, 0) ;
    print_list(std::cout, l) ;
    delete_list(l) ; l = nullptr ;

    // [2,1]
    l = construct_list({1,2}) ;
    l = s.rotateRight(l, 1) ;
    print_list(std::cout, l) ;
    delete_list(l) ; l = nullptr ;

    // [4,5,1,2,3]
    l = construct_list({1,2,3,4,5}) ;
    l = s.rotateRight(l, 2) ;
    print_list(std::cout, l) ;
    delete_list(l) ; l = nullptr ;

    // [2,0,1]
    l = construct_list({0,1,2}) ;
    l = s.rotateRight(l, 4) ;
    print_list(std::cout, l) ;
    delete_list(l) ; l = nullptr ;



    return 0 ;
} ;
