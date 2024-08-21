/*
You are given two non-empty linked lists representing two non-negative 
integers. The digits are stored in reverse order, and each of their nodes 
contains a single digit. Add the two numbers and return the sum as a linked 
list.

You may assume the two numbers do not contain any leading zero, except the 
number 0 itself.

 
Example 1:
Input: l1 = [2,4,3], l2 = [5,6,4]
Output: [7,0,8]
Explanation: 342 + 465 = 807.

Example 2:
Input: l1 = [0], l2 = [0]
Output: [0]

Example 3:
Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
Output: [8,9,9,9,0,0,0,1]
 

Constraints:

The number of nodes in each linked list is in the range [1, 100].
0 <= Node.val <= 9
It is guaranteed that the list represents a number that does not have leading zeros.
*/

#include <iostream>
#include <vector>
#include <cmath>


/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


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


/**
 * Converts an int stored in a linked list node, one value per node, in reverse 
 * order, for instance 1-2-3 -> 321.
 * @param head the head of the list (containing the last digit).
 * @returns the int stored in the list.
 */
size_t 
listToInt(const ListNode* head)
{
    size_t sum = 0 ;
    size_t power = 0 ;

    const ListNode* current = head ;
    while(current)
    {   
        sum += current->val * (size_t)pow(10, power) ;
        power++ ;
        current = current->next ;
    }

    return sum ;
}


/**
 * Converts an int into a linked list with one digit per node in reverse order, 
 * for instance 321 -> 1-2-3.
 * @param n the int of interest.
 * @returns the head of the list containing the int.
 */
ListNode*
intToList(size_t n)
{
    ListNode* head = new ListNode() ;
    ListNode* current = head ;
    size_t power = 1 ;

    while(n != 0)
    {   
        size_t digit = n % (size_t)pow(10, power) ;
        current->val = digit / (size_t)pow(10, power-1) ;
        n -= digit ;
        power++ ;
        if(n)
        {   current->next = new ListNode() ; 
            current = current->next ;
        }
    }
    return head ;
}


class Solution {
public:
    /**
     * Sums two numbers stored in two linked lists in decreasing order and 
     * returns the result in the same format. For instance 1-2-3 + 4-5-6 is 
     * 321+654=975 which is returned as 5-7-9.
     * This implementation is upper bounded in precision by the precision of 
     * size_t.
     * @param l1 the list containing the 1st number
     * @param l2 the list containing the 2nd number
     * @returns the head of the list containing the result.
     */
    ListNode* addTwoNumbersLimited(ListNode* l1, ListNode* l2) {
        
        size_t n = listToInt(l1) + listToInt(l2) ;
        return intToList(n) ;
    }

    /**
     * Sums two numbers stored in two linked lists in decreasing order and 
     * returns the result in the same format. For instance 1-2-3 + 4-5-6 is 
     * 321+654=975 which is returned as 5-7-9.
     * @param l1 the list containing the 1st number
     * @param l2 the list containing the 2nd number
     * @returns the head of the list containing the result.
     */
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        
        ListNode* head = new ListNode(0) ;
        ListNode* l3 = head ;

        int extra = 0 ;

        bool l1_end = false ;
        bool l2_end = false ;

        while((not l1_end) or (not l2_end))
        {   // compute the digit
            int digit = 0 ;
            if(not l1_end)
            {   digit += l1->val ; }
            if(not l2_end)
            {   digit += l2->val ; }
            digit += extra ;

            // if digit >10, only add the last digit and carry over 10
            if(digit >= 10)
            {   extra = 1 ;
                digit = digit % 10 ;
            }
            else
            {   extra = 0 ; }

            l3->val = digit ;
            
            l1 = l1 != nullptr ? l1->next : l1 ;
            l2 = l2 != nullptr ? l2->next : l2 ;
            
            l1_end = l1 == nullptr ? true : false ;
            l2_end = l2 == nullptr ? true : false ;

            // need an extra l3 node if there still is a computation left
            if(l1 or l2 or extra)
            {   l3->next = new ListNode() ; 
                l3 = l3->next ;
            }
        }

        // if last l1 + l2 resulted in > 10
        if(extra)
        {   l3->val = extra ; 
            extra = 0 ;
        }

        return head ;
    }
} ;


int main()
{
    Solution s ;
    /* insert tests */
    
    ListNode* l1 = construct_list({1,2,3}) ;
    ListNode* l2 = construct_list({1,1,1}) ;
    ListNode* l12 = s.addTwoNumbers(l1,l2) ;  // 321+ 111 = 432 -> 2-3-4
    print_list(std::cout, l12) ;
    delete_list(l1) ;
    delete_list(l2) ;
    delete_list(l12) ;

    ListNode* l3 = construct_list({0}) ;
    ListNode* l4 = construct_list({0}) ;
    ListNode* l34 = s.addTwoNumbers(l3,l4) ;  // 0+ 0 = 0 -> 0
    print_list(std::cout, l34) ;
    delete_list(l3) ;
    delete_list(l4) ;
    delete_list(l34) ;

    ListNode* l5 = construct_list({1}) ;
    ListNode* l6 = construct_list({9}) ;
    ListNode* l56 = s.addTwoNumbers(l5,l6) ;  // 9+1 = 10 -> 0-1
    print_list(std::cout, l56) ;
    delete_list(l5) ;
    delete_list(l6) ;
    delete_list(l56) ;
    
    ListNode* l7 = construct_list({1,2,3}) ;
    ListNode* l8 = construct_list({0}) ;
    ListNode* l78 = s.addTwoNumbers(l7,l8) ;  // 321 + 0 = 321 -> 1-2-3
    print_list(std::cout, l78) ;
    delete_list(l7) ;
    delete_list(l8) ;
    delete_list(l78) ;
    
    return 0 ;
} ;
