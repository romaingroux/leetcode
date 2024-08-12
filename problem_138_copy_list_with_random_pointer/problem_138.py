"""
A linked list of length n is given such that each node contains an additional 
random pointer, which could point to any node in the list, or null.

Construct a deep copy of the list. The deep copy should consist of exactly n 
brand new nodes, where each new node has its value set to the value of its 
corresponding original node. Both the next and random pointer of the new nodes 
should point to new nodes in the copied list such that the pointers in the 
original list and copied list represent the same list state. None of the 
pointers in the new list should point to nodes in the original list.

For example, if there are two nodes X and Y in the original list, 
where X.random --> Y, then for the corresponding two nodes x and y in the 
copied list, x.random --> y.

Return the head of the copied linked list.

The linked list is represented in the input/output as a list of n nodes. Each 
node is represented as a pair of [val, random_index] where:

val: an integer representing Node.val
random_index: the index of the node (range from 0 to n-1) that the random 
pointer points to, or null if it does not point to any node.
Your code will only be given the head of the original linked list.

 

Example 1:


Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]
Example 2:


Input: head = [[1,1],[2,1]]
Output: [[1,1],[2,1]]
Example 3:



Input: head = [[3,null],[3,0],[3,null]]
Output: [[3,null],[3,0],[3,null]]
 

Constraints:

0 <= n <= 1000
-104 <= Node.val <= 104
Node.random is null or is pointing to some node in the linked list.
"""

import typing as tp
import copy


# Definition for a Node.
class Node:
    def __init__(self, 
                 x: int, 
                 next: 'Node' = None, 
                 random: 'Node' = None):
        self.val = int(x)
        self.next = next
        self.random = random
    
    def __str__(self) \
        -> str:
        """
        Returns the string representation of a Node instance.
        Returns:
            The string representation of the instance.
        """
        self_p = hex(id(self))
        next_p = hex(id(self.next)) if self.next is not None else None
        rand_p = hex(id(self.random)) if self.random is not None else None
        return f"({self_p}, {self.val}, {rand_p}, {next_p})"
    
    def __hash__(self) \
        -> int:
        """
        Computes the hash of an instance on its string representation.
        Returns:
            The hash of the instance.
        """
        return hash(str(self))


def make_list(values: tp.List[int]) \
    -> tp.Optional[Node]:
    """
    Create a linked list with the given values and return the 
    head node.
    Args:
        values: the values of the nodes.
    Returns:
        The head of the list.
    """
    head = Node(val = values[0])
    cur = head

    for i in range(1,len(values)):
        cur.next = Node(val=values[i])
        cur = cur.next
    return head


def print_list(head: tp.Optional[Node]) \
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

    def copyRandomList(self, 
                       head: tp.Optional[Node]) \
        -> tp.Optional[Node]:
        """
        Makes a deep copy of the given list and returns its head.
        Args:
            head: the head of the list to copy.
        Returns:
            The head of the deep copied list.
        """

        if head is None:
            return None

        # will contain the original Node as keys and its copy as value
        copy = dict()

        # init the copy with only the values
        node = Node(-1, head)  # that's a prehead
        while node.next:
            copy[node.next] = Node(node.next.val, None, None)
            node = node.next
                
        # complete the copy by adding the next
        node = Node(-1, head)  # that's a prehead
        while node.next:
            # print(f"loop 2 {node.next}")
            if node.next.next:
                copy[node.next].next = copy[node.next.next]
            if node.next.random:
                copy[node.next].random = copy[node.next.random]
            node = node.next
        
        # return the head of the copy
        return copy[head]
          

if __name__ == "__main__":

    node0 = Node(0)
    node1 = Node(1)
    node2 = Node(2)
    node0.next = node1
    node0.random = node2
    node1.next = node2
    node1.random = node0
    node2.random = node1

    print_list(node0)

    s = Solution()
    node0_copy = s.copyRandomList(node0)

    print_list(node0_copy)


