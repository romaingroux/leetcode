"""
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
"""


import typing as tp

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
    
    def __str__(self):
        return f"<{self.val} {self.next != None}>"


def make_list(values: tp.List[int]) \
    -> tp.Optional[ListNode]:
    """
    Create a linked list with the given values and return the 
    head node.
    Args:
        values: the values of the nodes.
    Returns:
        The head of the list.
    """
    head = ListNode(val = values[0])
    cur = head

    for i in range(1,len(values)):
        cur.next = ListNode(val=values[i])
        cur = cur.next
    return head

def print_list(head: tp.Optional[ListNode]) \
    -> None:
    """
    Prints a linked list on stdout.
    Args:
        head: the head node of the list.
    Returns:
        None
    """
    s = []
    while head.next != None:
        s.append(str(head))
        head = head.next
    s.append(str(head))
    print(",".join(s))



class Solution:

    def mergeTwoLists(self,
                      list1: tp.Optional[ListNode], 
                      list2: tp.Optional[ListNode]) \
        -> tp.Optional[ListNode]:
        """
        Merges two linked lists sorted in ascending order.
        Works in O(L1+L2) time.
        Args:
            list1: the head of the 1st list.
            list2: the head of the 2nd list.
        Returns:
            The head of the merged list. 
        """
        prehead = ListNode(-1)
        list3 = prehead
        # merge
        while list1 and list2:
            if list1.val < list2.val:
                list3.next = list1
                list1 = list1.next
            else:
                list3.next = list2
                list2 = list2.next
            list3 = list3.next

        # terminate
        if list1.next is not None:
            list3.next = list1
        else:
            list3.next = list2

        return prehead.next



if __name__ == "__main__":

    s = Solution()
    l1 = make_list([1,2,4])
    l2 = make_list([1,3,4])
   
    l3 = s.mergeTwoLists(l1, l2)
    print_list(l3)
    # l1 = make_list([1,2,3,4,5])
    # print(l1)
    # print_list(l1)