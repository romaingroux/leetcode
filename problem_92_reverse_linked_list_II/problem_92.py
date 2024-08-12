"""
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
"""

import typing as tp


# Definition for a Node.
class ListNode:
    def __init__(self, 
                 val=0, 
                 next=None):
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
    def reverseBetween(self, 
                       head: tp.Optional[ListNode], 
                       left: int,
                       right: int) \
        -> tp.Optional[ListNode]:
        """
        Reverses the given list items located at index [left,right], expressed 
        as 1-based index.
        Args:
            head: the head of the list to reverse.
            left: the 1-based index of the lefmost item in the list to be 
                reverted.
            right: the 1-based index of the rightmost item in the list to be 
                reverted.
        Returns:
            The head of the list.
        """

        if head is None:
            return None

        # will contain the index of the Node in the list as key and the Node 
        # as value
        d = dict()

        i = 1
        node = ListNode(-1, head)  # that's a prehead
        # include prehead in dict
        d[0] = node
        while node.next:
            d[i] = node.next
            i += 1
            node = node.next

        length = i-1
        if length == 1:
            return head
        # if right > length:
        #     return None

        # revert the given range  
        for i in range(right, left, -1):
            print(f"{i}-->{i-1}")
            d[i].next = d[i-1]

        d[left-1].next = d[right]
        if right+1 <= length:
            d[left].next = d[right+1]
        else:
            d[left].next = None
        return d[0].next


if __name__ == "__main__":

    s = Solution()

    # l_rev = s.reverseBetween(make_list([1,2,3,4,5]), 2 ,4)
    # print_list(l_rev)

    # l_rev = s.reverseBetween(make_list([1,2,3,4,5]), 1 ,3)
    # print_list(l_rev)

    l_rev = s.reverseBetween(make_list([1,2,3,4,5]), 3 ,5)
    print_list(l_rev)