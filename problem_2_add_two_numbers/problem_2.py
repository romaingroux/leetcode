"""
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
"""


import typing as tp


# Definition for singly-linked list.

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
    while head:
        s.append(str(head))
        head = head.next
    print(",".join(s))

class Solution:

    def addTwoNumbers(self, 
        l1: tp.Optional[ListNode], 
        l2: tp.Optional[ListNode]) \
        -> tp.Optional[ListNode]:
        """
        Computes the sum of 2 numbers stored in two linked lists in reverse 
        order. For instance, 203 is stored as 3->0->2, 105 5->0->1 and the 
        result is 203+105=308 as 8->0->3.
        It works in O(|L1| + |L2|) time.
        Args:
            l1: the list storing the 1st number in reverse order.
            l2: the list storing the 2nd number in reverse order.
        Returns:
            The head of the list storing the results in reverse order.
        """

        # print_list(l1)
        # print_list(l2)

        n1 = 0
        n2 = 0

        # list of length 1
        if l1.next == None:
            n1 += l1.val
            l1 = l1.next
        if l2.next == None:
            n2 += l2.val
            l2 = l2.next

        # compute what is in list 1
        power = 0
        while l1:
            n1 += l1.val * (10**power)
            power += 1
            l1 = l1.next
        
        # compute what is in list 2
        power = 0
        while l2:
            n2 += l2.val * (10**power)
            power += 1
            l2 = l2.next
        
        n = n1 + n2
        if n == 0:
            return ListNode(0)
        
        # put this in a list
        prehead = ListNode(-1)
        l3 = prehead
        power = 1
        while n > 0:
            remain = n % (10**power)
            # print(f"{n} % 10**{power} = {remain}")
            n -= remain
            l3.next = ListNode(remain // (10**(power-1)))
            # print(f"{remain} // (10**{power-1}) = {val}")
            power += 1
            l3 = l3.next

        # print_list(prehead.next)
        return prehead.next


if __name__ == "__main__":

    s = Solution()

    s.addTwoNumbers(make_list([2,4,3]),
                    make_list([5,6,4]))

    s.addTwoNumbers(make_list([1]),
                    make_list([3]))


    s.addTwoNumbers(make_list([0]),
                    make_list([0]))
