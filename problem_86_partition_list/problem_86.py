"""
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
"""

import typing as tp


# Definition for singly-linked list.
class ListNode:

    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
    
    def __str__(self) \
        -> str:
        """
        Returns the string representation of a ListNode instance.
        Returns:
            The string representation of the instance.
        """
        next_val = self.next.val if self.next is not None else "None"
        return f"({self.val},{next_val})"

    def __repr__(self) \
        -> str:
        return str(self)
    
    def __hash__(self) \
        -> int:
        """
        Computes the hash of an instance on its string representation.
        Returns:
            The hash of the instance.
        """
        return hash(str(self))


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
    head = ListNode(values[0])
    cur = head

    for i in range(1,len(values)):
        cur.next = ListNode(values[i])
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
    while head:
        s.append(str(head))
        head = head.next
    print(",".join(s))


class Solution:
    def partition(self, 
                  head: tp.Optional[ListNode], 
                  x: int) \
        -> tp.Optional[ListNode]:
        """
        Partitions the given list.
        Args:
            head: the head of the list of interest.
            x: the value around which to partition the list.
        Returns:
            The head of the list.
        """

        # prehead
        node = ListNode(-1,head)
        is_smaller = []
        while node.next:
            is_smaller.append(node.next.val < x)
            node = node.next
        
        # reorganize
        # new list
        new_list_prehead = ListNode(-1,None)  # prehead
        new_list = new_list_prehead
        
        # add values smaller
        node = ListNode(-1,head)  # prehead
        i = 0
        while node.next:
            if is_smaller[i]:
                new_list.next = ListNode(node.next.val, None)
                new_list = new_list.next
            i += 1
            node = node.next
        
        # add values larger
        node = ListNode(-1,head)  # prehead
        i = 0
        while node.next:
            if not is_smaller[i]:
                new_list.next = ListNode(node.next.val, None)
                new_list = new_list.next
            i += 1
            node = node.next

        return new_list_prehead.next

if __name__ == "__main__":

    s = Solution()

    # [1,2,2,4,3,5]
    l = s.partition(make_list([1,4,3,2,5,2]), 3)
    print_list(l)

