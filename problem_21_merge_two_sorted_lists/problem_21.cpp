/*
You are given the heads of two sorted linked lists list1 and list2.

Merge the two lists into one sorted list. The list should be made by splicing 
together the nodes of the first two lists.

Return the head of the merged linked list.

 

Example 1:


Input: list1 = [1,2,4], list2 = [1,3,4]
Output: [1,1,2,3,4,4]
Example 2:

Input: list1 = [], list2 = []
Output: []
Example 3:

Input: list1 = [], list2 = [0]
Output: [0]
 

Constraints:

The number of nodes in both lists is in the range [0, 50].
-100 <= Node.val <= 100
Both list1 and list2 are sorted in non-decreasing order.
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
     * Merges two sorted lists in ascending order.
     * @param list1 the head of the 1st list.
     * @param list2 the head of the 2nd list.
     * @returns the head of the merged list.
     * 
     */
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        
        if(list1 == nullptr and list2 ==nullptr)
        {   return nullptr ; }
        
        bool l1 = (list1 != nullptr) ? true : false ; 
        bool l2 = (list2 != nullptr) ? true : false ; 
        
        ListNode* head = new ListNode() ;
        ListNode* list3 = head ;

        while(l1 or l2)
        {
            if(l1 and l2)
            {   
                if(list1->val < list2->val)
                {   list3->val = list1->val ; 
                    list1 = list1->next ;
                }
                else
                {   list3->val = list2->val ; 
                    list2 = list2->next ;
                }
            }
            else if(l1)
            {
                list3->val = list1->val ;
                list1 = list1->next ;
            }
            else if(l2)
            {
                list3->val = list2->val ;
                list2 = list2->next ;
            }

            l1 = (list1 != nullptr) ? true : false ;
            l2 = (list2 != nullptr) ? true : false ;

            if(l1 or l2)
            {   list3->next = new ListNode() ;
                list3 = list3->next ;
            }
        }

        return head ;
    }
};


int main()
{
    Solution s ;
    /* insert tests */
    ListNode* l1 = construct_list({1,2,3}) ;
    ListNode* l2 = construct_list({4,5,6}) ;
    ListNode* l12 = s.mergeTwoLists(l1,l2) ;  // 1-2-3-4-5-6
    print_list(std::cout, l12) ;
    delete_list(l1) ;
    delete_list(l2) ;
    delete_list(l12) ;

    ListNode* l3 = construct_list({1,3,5}) ;
    ListNode* l4 = construct_list({2,4,6}) ;
    ListNode* l34 = s.mergeTwoLists(l3,l4) ;  // 1-2-3-4-5-6
    print_list(std::cout, l34) ;
    delete_list(l3) ;
    delete_list(l4) ;
    delete_list(l34) ;

    ListNode* l5 = construct_list({1,3}) ;
    ListNode* l6 = construct_list({2,4,5}) ;
    ListNode* l56 = s.mergeTwoLists(l5,l6) ;  // 1-2-3-4-5
    print_list(std::cout, l56) ;
    delete_list(l5) ;
    delete_list(l6) ;
    delete_list(l56) ;

    ListNode* l7 = construct_list({2,4,5}) ;
    ListNode* l8 = construct_list({1,3}) ;
    ListNode* l78 = s.mergeTwoLists(l7,l8) ;  // 1-2-3-4-5
    print_list(std::cout, l78) ;
    delete_list(l7) ;
    delete_list(l8) ;
    delete_list(l78) ;
    return 0 ;
} ;
