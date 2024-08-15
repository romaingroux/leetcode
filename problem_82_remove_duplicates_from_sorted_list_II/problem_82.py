"""
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
"""

import typing as tp
import collections


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

    @staticmethod
    def isDuplicated(node: ListNode) \
        -> bool:
        """
        Checks if the given node is duplicated (that if it is followed by a 
        node with the same value). The given node must have a next node !
        Args:
            node: the node of interest
        Returns:
            If the node is duplicated
        """
        # a middle node can be duplicated, check
        if node.next:
            if node.next.val == node.val:
                return True
            else:
                return False
        # the last node in the list cannot be duplicated
        else:
            return False
    
    @staticmethod
    def jumpAfter(head: ListNode):
        """
        From the given node, finds the 1st next node with a different value 
        and returns it. Returns None if no such node could be found before the 
        end of the list.
        Args:
            head: the node of interest
        Returns:
            The next node with a different value or None if no such node could 
            be found by the end of the list.
        """
        node = head
        while node.next:
            # node with different value
            if node.next.val != head.val:
                return node.next
            else:
                node = node.next
        # hit the end of the list without finding node with different
        # value, there is no such node!
        return None
    
    def deleteDuplicatesFast(self, 
                             head: tp.Optional[ListNode]) \
        -> tp.Optional[ListNode]:
        """
        Removes the duplicates in a sorted list and returns the head of 
        the new list.
        IT IS NOT WORKING WITH INPUTS CONTAINING 2 DUPLICATED STRETCHES 
        FOLLOWING EACH OTHER LIKE [1,2,2,3,3,4], OTHERWISE GOOD
        Args:
            head: the head of the list of interest.
        Returns:
            The head of the list without duplicates.
        """

        # list of lenght 1, no duplicate
        if head.next is None:
            return head
        # list of length 2, check duplicate
        elif head.next.next is None:
            # both nodes are duplicated
            if head.val == head.next.val:
                return None
            # no duplicate
            else:
                return head

        # list of length >= 3
        # prehead
        prehead = ListNode(-999999, head)
        node = prehead
        while node.next:
            print(f"{node=}")
            print(f"{node.next=}")
            # is next node duplicated (followed by node with same value)
            is_duplicated = self.isDuplicated(node.next)
            # find first node after next that is not duplicated
            if is_duplicated:
                print(f"next node {node.next} is duplicated")
                next_node = self.jumpAfter(node.next)
                # could find a node
                if next_node:
                    print(f"new next {next_node=}")
                    node.next = next_node
                    node = node.next
                # hit end of list without finding node
                # create new end
                else:
                    node.next = None
                    break
            else:
                print(f"next node is not duplicated")
                node = node.next
        return prehead.next

    def deleteDuplicates(self, 
                         head: tp.Optional[ListNode]) \
        -> tp.Optional[ListNode]:
        """
        Removes the duplicates in a sorted list and returns the head of 
        the new list.
        Slower than above solution but exact !
        Args:
            head: the head of the list of interest.
        Returns:
            The head of the list without duplicates.
        """

        counts = collections.Counter()

        # list unique / duplicate values
        node = head
        while node:
            print(f"{node=}")
            counts[node.val] += 1
            node = node.next
        
        prehead = ListNode(-99999,head)
        node = prehead
        while node.next:
            # next node is duplicated, remove it
            if counts[node.next.val] > 1:
                # not the end
                if node.next.next:
                    node.next = node.next.next
                # the end
                else:
                    node.next = None
            else:
                node = node.next
        
        return prehead.next
    

if __name__ == "__main__":

    s = Solution()

    # 1 node list
    l = s.deleteDuplicates(make_list([1]))
    print_list(l)
    # 2 nodes list w/o duplicates
    l = s.deleteDuplicates(make_list([1,2]))
    print_list(l)
    # 2 nodes list with duplicates
    l = s.deleteDuplicates(make_list([1,1]))
    print_list(l)
    
    # no duplicate
    l = s.deleteDuplicates(make_list([0,1,2,3,4]))
    print_list(l)
    # duplicate in middle
    l = s.deleteDuplicates(make_list([0,1,1,2]))
    print_list(l)
    # duplicate at end
    l = s.deleteDuplicates(make_list([0,1,2,2]))
    print_list(l)
    # duplicate at beginning
    l = s.deleteDuplicates(make_list([0,0,1,2]))
    print_list(l)
    # 2 duplications follow each other
    l = s.deleteDuplicates(make_list([0,1,2,2,3,3,4]))
    print_list(l)

    l = s.deleteDuplicates(make_list([1,1,1,2,3]))
    print_list(l)