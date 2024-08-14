"""
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
1 <= n <= sz"""

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
        return f"({self.val})"
    
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
    def removeNthFromEnd(self, 
                         head: tp.Optional[ListNode], 
                         n: int) \
        -> tp.Optional[ListNode]:
        """
        Removes the N-th node from the end of the list and returns 
        the list.
        Args:
            head: the head of the list of interest.
            n: the 1-based index of the node to remove, from the end of 
                the list.
        """

        if head == None:
            return None
        
        
        d = dict()
        node = ListNode(-1, head)  # prehead
        d[0] = node
        i = 1
        while node.next:
            d[i] = node.next
            i += 1
            node = node.next
        # length without prehead
        length = i - 1 

        # remove
        n = n -1  # make it 0-based
        d[length-n].next = None
        # we are removing a middle element
        if n != 0:
            d[length-n-1].next = d[length-n+1] 
        # we are removing the tail, make new tail
        else:
            d[length-1].next = None

        # we have removed the head, return new head
        if n == length-1:
            # special case, we have removed the head of a 1 element
            # list, nothing remains
            if length-1 == 0:
                return None
            else:
                return d[2]
        
        return d[1]


if __name__ == "__main__":

    s = Solution()
    
    # remove middle element
    l = s.removeNthFromEnd(make_list([1,2,3,4,5]), 2)
    print_list(l)
    # remove tail
    l = s.removeNthFromEnd(make_list([1,2,3,4,5]), 1)
    print_list(l)
    # remove head
    l = s.removeNthFromEnd(make_list([1,2,3,4,5]), 5)
    print_list(l)
    # remove only item in 1 element list
    l = s.removeNthFromEnd(make_list([1]), 1)
    print_list(l)