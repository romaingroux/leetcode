"""
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
    def rotateRight(self, 
                    head: tp.Optional[ListNode], 
                    k: int) \
        -> tp.Optional[ListNode]:
        """
        Rotates the given linked list by the given offset.
        Args:
            head: the head node of the list of interest.
            k: the offset.
        Returns:
            The head of the list.
        """

        if head is None:
            return None
        elif (k == 0) or (head.next is None):
            return head
        
        # prehead
        node = ListNode(-9999,head)
        d = dict()
        i = 0
        while node.next:
            d[i] = node.next
            node = node.next
            i += 1
        length = i
        
        # if case k > length of list, it's like cycling the entire list again 
        k = k % length

        # it's back on the head, no computation
        if k == 0:
            return d[0]

        # new head
        head_index = length - k
        d[length-1].next = d[0]
        # new tail
        d[head_index-1].next = None
        
        return d[head_index]

if __name__ == "__main__":

    s = Solution()

    # [4,5,1,2,3]
    # l = s.rotateRight(make_list([1,2,3,4,5]), 2)
    # print_list(l)

    # [2,0,1]
    # l = s.rotateRight(make_list([0,1,2]), 4)
    # print_list(l)

    l = s.rotateRight(make_list([1,2]), 2)
    print_list(l)

