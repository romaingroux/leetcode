/*
Given the head of a sorted linked list, delete all nodes that have duplicate 
numbers, leaving only distinct numbers from the original list. Return the 
linked list sorted as well.

 

Example 1:
Input: head = [1,2,3,3,4,4,5]
Output: [1,2,5]

Example 2:
Input: head = [1,1,1,2,3]
Output: [2,3]
 
Constraints:

The number of nodes in the list is in the range [0, 300].
-100 <= Node.val <= 100
The list is guaranteed to be sorted in ascending order.
*/


#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>


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
     * Deletes duplicated nodes from a list.
     * Works in O(N) time in a two passes with O(N) extra memory.
     * @param head the head of the list of interest.
     * @returns the head of the resulting list.
     */
    ListNode*
    deleteDuplicatesSlow(ListNode* head) {
        
        if(head == nullptr)
        {   return nullptr ; }
        
        std::vector<int> values ;
        std::unordered_map<int,int> map ;
        

        ListNode* current = head ;
        while(current)
        {   
           if(map.find(current->val) == map.end())
           {    map[current->val] = 1 ;}
           else
           {    map[current->val] += 1 ; }
           current = current->next ;
        }

        // result list with prehead
        ListNode* results_prehead = new ListNode(-1,nullptr) ;
        ListNode* results = results_prehead ;

        current = head ;
        while(current)
        {   // unique
            if(map[current->val] == 1)
            {   results->next = new ListNode(current->val) ;
                results = results->next ; 
            }
            // not unique
            else
            {   ; }
            // std::cerr << *current << " " << map[current->val] << std::endl ;
            current = current->next ;
        }
       

        // delete prehead
        results = results_prehead->next ;
        delete results_prehead ; results_prehead = nullptr ;

        return results ;
    }

    /**
     * Deletes duplicated nodes from a list in place.
     * Works in O(N) time in a single pass with O(1) extra memory.
     * @param head the head of the list of interest.
     * @returns the head of the list.
     */
    ListNode*
    deleteDuplicates(ListNode* head) {
        // prehead
        ListNode* prehead = new ListNode(0, head);
        
        // previous = the last node
        // before the sublist of duplicates
        ListNode* previous = prehead;
        ListNode* current = head ;
        while (current) 
        {
            // start of duplicated stretch of nodes
            if (current->next and current->val == current->next->val) 
            {
                // move current until after duplicated stretch
                while (current->next and current->val == current->next->val)
                {   // free memory
                    ListNode* current_next = current->next ;
                    delete current ;
                    current = current_next ;
                }
                // move previous to 1st node after duplicated stretch
                previous->next = current->next ;
            // move previous
            } 
            else 
            {   previous = previous->next ; }
            // move forward
            current = current->next;
        }

        current = prehead->next ;
        delete prehead ;
        return current ;
    }

} ;



int main()
{
    Solution s ;
    /* insert tests */


    ListNode* l = nullptr ;
    
    // repeatition at beginning
    l = construct_list({1,1,1,2,3,4,5}) ;
    l = s.deleteDuplicates(l) ;
    print_list(std::cout, l) ;
    delete_list(l) ; l = nullptr ;

    // 2 repeatitions at beginning
    l = construct_list({1,1,1,2,2,2,3,4,5}) ;
    l = s.deleteDuplicates(l) ;
    print_list(std::cout, l) ;
    delete_list(l) ; l = nullptr ;
    
    // repeatition in middle
    l = construct_list({1,2,3,3,3,4,5}) ;
    l = s.deleteDuplicates(l) ;
    print_list(std::cout, l) ;
    delete_list(l) ; l = nullptr ;
    
    // 2 repeatitions in middle
    l = construct_list({1,2,2,3,3,3,4,5}) ;
    l = s.deleteDuplicates(l) ;
    print_list(std::cout, l) ;
    delete_list(l) ; l = nullptr ;
    
    // repeatition at the end
    l = construct_list({1,2,3,4,5,5,5}) ;
    l = s.deleteDuplicates(l) ;
    print_list(std::cout, l) ;
    delete_list(l) ; l = nullptr ;
    
    // 2 repeatitions at the end
    l = construct_list({1,2,3,4,4,4,5,5,5}) ;
    l = s.deleteDuplicates(l) ;
    print_list(std::cout, l) ;
    delete_list(l) ; l = nullptr ;

    return 0 ;
} ;
