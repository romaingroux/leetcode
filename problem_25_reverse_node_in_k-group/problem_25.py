"""
Given the head of a linked list, reverse the nodes of the list k at a time, 
and return the modified list.

k is a positive integer and is less than or equal to the length of the 
linked list. If the number of nodes is not a multiple of k then left-out 
nodes, in the end, should remain as it is.

You may not alter the values in the list's nodes, only nodes themselves may 
be changed.

Example 1:
Input: head = [1,2,3,4,5], k = 2
Output: [2,1,4,3,5]


Example 2:
Input: head = [1,2,3,4,5], k = 3
Output: [3,2,1,4,5]
 
Constraints:

The number of nodes in the list is n.
1 <= k <= n <= 5000
0 <= Node.val <= 1000
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

    def reverseKGroup(self, 
                      head: tp.Optional[ListNode], 
                      k: int) \
        -> tp.Optional[ListNode]:
        """
        Takes a linked list and reverses the node order by groups of k 
        nodes. For instance if k=2 and list=[0,1,2,3,4], the new order will 
        be [1,0,3,2,4].
        Args:
            head: the head of the list of interest.
            k: the size of the groups.
        Returns:
            The head of the list.
        """
        if head == None:
            return None
        
        # will contain the index of each node in the list as key and the
        # node as value
        d = dict()
        node = head
        d[0] = node 
        i = 1
        while node.next:
            d[i] = node.next
            i += 1
            node = node.next
        length = i
        # print(f"length: {length}")
        
        # nothing can be done
        if k > length:
            return head

        # this will contain the new index of a node in the list as key and 
        # the node as value
        d_new = dict()
        # go over each group of K nodes from head, range [from,to]
        i_ori = 0
        from_p = 0
        to_p   = from_p + k - 1
        while to_p < length:
            print(f"slice [{from_p}->{to_p}]")
            # this is the new inded
            for i_new in range(to_p, from_p-1, -1):
                print(f"{i_ori} -> {i_new}")
                d_new[i_new] = d[i_ori]
                i_ori += 1
            from_p = to_p + 1
            to_p = from_p + k - 1
        
        # last slice may have been ignored because incomplete
        # in here the indices stay the same
        print(f"last slice [{from_p}->{to_p}]")
        while from_p < length:
            print(f"{from_p} -> {from_p}")
            d_new[from_p] = d[from_p]
            from_p += 1
        
        # rewire
        for i in range(0,length-1,1):
            print(f"rewire {i}->{i+1}")
            d_new[i].next = d_new[i+1]
        d_new[length-1].next = None
        return d_new[0]


if __name__ == "__main__":

    s = Solution()

    l_reorder= s.reverseKGroup(make_list([0,1,2,3,4]), 6)
    print_list(l_reorder)
