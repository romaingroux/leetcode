/*
Given head, the head of a linked list, determine if the linked list has a 
cycle in it.

There is a cycle in a linked list if there is some node in the list that can 
be reached again by continuously following the next pointer. Internally, pos is 
used to denote the index of the node that tail's next pointer is connected to. 
Note that pos is not passed as a parameter.

Return true if there is a cycle in the linked list. Otherwise, return false.

 

Example 1:
Input: head = [3,2,0,-4], pos = 1
Output: true
Explanation: There is a cycle in the linked list, where the tail connects to 
the 1st node (0-indexed).

Example 2:
Input: head = [1,2], pos = 0
Output: true
Explanation: There is a cycle in the linked list, where the tail connects to 
the 0th node.

Example 3:
Input: head = [1], pos = -1
Output: false
Explanation: There is no cycle in the linked list. 

Constraints:

The number of the nodes in the list is in the range [0, 104].
-105 <= Node.val <= 105
pos is -1 or a valid index in the linked-list.
 

Follow up: Can you solve it using O(1) (i.e. constant) memory?
*/

#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <functional>     // std::hash
#include <unordered_set>  // unordered_set

/**
 * Definition for singly-linked list.
 */
 struct ListNodeDouble {
     int val;
     ListNodeDouble *next;
     ListNodeDouble(int x) : val(x), next(NULL) {}
 } ;
 

// /**
//  * Definition for singly-linked list.
//  */ 
// struct ListNode {
//     /** The node value.*/
//     int val;
//     /** The next node in the list, nullptr if no follower.*/
//     ListNode* next ;
//     
//     /**
//      * Constructs a node without next node.
//      * @param x The value of the node.
//      */
//     ListNode(int x) 
//         : val(x), next(nullptr) 
//     { ; }
// 
//     /**
//      * Constructs a node that has a next node.
//      * @param x The value of the node.
//      * @param next The next node in the list.
//      */
//     ListNode(int x, ListNode* next) 
//         : val(x), next(next) 
//     { ; }
// 
//     /**
//      * Comparison operator.
//      * @param rhs the other instance to compare with.
//      * @returns true if the fields of both instances are the same, false 
//      * otherwise.
//      */
//     bool 
//     operator == (const ListNode& rhs) const
//     {
//         if(&rhs == this)
//         {   return true ; }
//         
//         if(this->val == rhs.val and this->next == rhs.next)
//         {   return true ; }
//         
//         return false ;
//     }
// 
//     /**
//      * Returns a string representation of the instance.
//      * @returns The string representation of the instance.
//      */
//     std::string 
//     to_string() const
//     {   
//         std::string next_str = (this->next == nullptr) ? 
//                                 "NULL" : 
//                                 std::to_string(
//                                     (unsigned long long)(void**)this->next) ;
//         return "(" + std::to_string(this->val) + "," + next_str + ")" ;
//     }
// } ;


// /**
//  * Implement hash functions for custom struct and classes.
//  */
// class HashFunction
// {
//     public:
//         /**
//          * Computes the hash of a ListNode from its string representation.
//          * @param node the node of interest.
//          * @returns the instance hash.
//          */
//         size_t operator() (const ListNode& node) const
//         {   return std::hash<std::string>()(node.to_string()) ; }
// } ;


std::ostream& 
operator << (std::ostream& stream, 
             const ListNodeDouble& node)
{
    std::string next_str = node.next == nullptr ? 
                            "NONE" :
                            std::to_string(
                                (unsigned long long)(void**)node.next) ;
    stream << "(" << node.val << "," << next_str << ")" << std::endl ;
    return stream ;
}


/**
 * Construct a linked list from the array of values.
 * All nodes are dynamically allocated and need to be deleted afterward!
 * @param values the values of the nodes.
 * @returns A pointer to the head of the list.
 */
ListNodeDouble*
construct_list(const std::vector<int>& values)
{   
    if(values.size() == 0)
    {   return nullptr ; }

    ListNodeDouble* head = new ListNodeDouble(values[0]) ;
    ListNodeDouble* current = head ;
    for(size_t i=1; i<values.size(); i++)
    {   current->next = new ListNodeDouble(values[i]) ;
        current = current->next ;
    }
    return head ;
}

/**
 * Deletes all nodes within a list.
 * @param head the head of the list of interest.
 */
void
delete_list(ListNodeDouble* head)
{
    ListNodeDouble* current = head ;
    while(current)
    {   ListNodeDouble* next = current->next ;
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
print_list(std::ostream& stream, ListNodeDouble* head)
{
    ListNodeDouble* current = head ;
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
    bool hasCycle(ListNodeDouble *head) {
        // no list
        if(head == nullptr)
        {   return false ; }
        // one item list with no cycle
        else if(head->next == nullptr)
        {   return false ; }

        ListNodeDouble* current(head) ;
        std::unordered_set<ListNodeDouble*> set ;
        while(current != nullptr)
        {   // node has already been seen
            if(set.find(current) != set.end())
            {   return true ; }
            
            set.insert(current) ; 
            current = current->next ; 
        }

        return false ;
    }
} ;


int main()
{
    Solution s ;
    /* insert tests */
    // std::vector<int> values_1 = {0,1,2,3,4} ;
    // ListNode* list_1 = construct_list(values_1) ;
    // print_list(std::cout, list_1) ;
    // delete_list(list_1) ;

    // no list
    assert(s.hasCycle(nullptr) == false) ;

    // no cycle
    ListNodeDouble node_0(0) ;
    ListNodeDouble node_1(1) ;
    ListNodeDouble node_2(2) ;
    node_0.next = &node_1 ;
    node_1.next = &node_2 ;
    assert(s.hasCycle(&node_0) == false) ;

    // cycle
    node_2.next = &node_0 ;
    assert(s.hasCycle(&node_0) == true) ;

    return 0 ;
} ;
