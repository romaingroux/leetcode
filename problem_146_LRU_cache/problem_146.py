"""
Design a data structure that follows the constraints of a Least Recently Used 
(LRU) cache.

Implement the LRUCache class:

LRUCache(int capacity) Initialize the LRU cache with positive size capacity.

int get(int key) Return the value of the key if the key exists, otherwise 
return -1.

void put(int key, int value) Update the value of the key if the key exists. 
Otherwise, add the key-value pair to the cache. If the number of keys exceeds 
the capacity from this operation, evict the least recently used key.

The functions get and put must each run in O(1) average time complexity.

 

Example 1:

Input
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, null, -1, 3, 4]

Explanation
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // cache is {1=1}
lRUCache.put(2, 2); // cache is {1=1, 2=2}
lRUCache.get(1);    // return 1
lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
lRUCache.get(2);    // returns -1 (not found)
lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
lRUCache.get(1);    // return -1 (not found)
lRUCache.get(3);    // return 3
lRUCache.get(4);    // return 4
 

Constraints:

1 <= capacity <= 3000
0 <= key <= 104
0 <= value <= 105
At most 2 * 105 calls will be made to get and put.
"""

import typing as tp


class ListNode:
    """
    Implements a double linked list node.
    """

    def __init__(self,
                 key: int,
                 value: int,
                 previous: tp.Optional["ListNode"]=None,
                 next: tp.Optional["ListNode"]=None):
        """
        Constructs a double linked list node holding a key and a value.
        Args:
            key: the node key.
            value: the node value.
            previous: the previous node in the list.
            next: the next node in the list.
        """
        self.key = key
        self.value = value
        self.prev = previous
        self.next = next
    
    def __str__(self) \
        -> str:
        """
        Returns the string representation of a ListNode instance.
        Returns:
            The string representation of the instance.
        """
        prev_val = hex(id(self.prev)) if self.prev is not None else "None"
        next_val = hex(id(self.next)) if self.next is not None else "None"
        return f"({prev_val} <- {self.key}:{self.value} -> {next_val})"

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

class LRUCache:
    """
    Implements a LRU cache.
    """

    def __init__(self, 
                 capacity: int):
        """
        Constructs a LRUCache with the given capacity.
        Args:
            capacity: the LRUCache capacity.
        """

        """Prehead to LRUCache item list (next item is most ancient)"""
        self.prehead = ListNode(-1,-1,None,None)
        """Posttail to LRUCache item list (prev item is most recent)"""
        self.posttail = self.prehead.next
        """LRUCache dictionary"""
        self.dict = dict()
        """Capacity"""
        self.capacity = capacity
        """Current number of items in LRUCache"""
        self.size = 0
    
    def __str__(self) \
        -> str:
        """
        Returns a string representation of the instance.
        Returns:
            A string representation of the instance.
        """
        l = []
        l.append(f"{self.size}/{self.capacity},PREHEAD")
        if self.size > 0:
            node = self.prehead.next
            for i in range(0,self.size):
                l.append(str(node))
                node = node.next
        l.append(f"POSTTAIL")
        return ",".join(l)

    def _pop(self, 
             key:int) \
        -> tp.Optional[ListNode]:
        """
        Pops the pair with the given key from the list and dict and 
        returns it. Does nothing and returns None if no such key is present.
        Args:
            key: the key of interest.
        Returns:
            The popped node, None if no pair with this key was found.
        """
        node = self.dict.get(key,None)
        if node:
            node_prev = node.prev
            node_next = node.next
            node_prev.next = node_next
            node_next.prev = node_prev
            del self.dict[key]
            return node
        else:
            return None
    
    def _append(self, 
                node: ListNode) \
        -> None:
        """
        Appends the given node after the current tail updates the list and dict.
        Args:
            node: the node of interest.
        Returns:
            None.
        """
        node_prev = self.posttail.prev
        node_prev.next = node
        node.prev = node_prev
        node.next = self.posttail
        self.posttail.prev = node
        self.dict[node.key] = node

    def get(self, 
            key: int) \
        -> int:
        """
        Returns the item with the value corresponding to this key and updates 
        the LRUCache.
        Args:
            key: the key of interest.
        Returns:
            The corresponding value, -1 if the key could not be found.
        """
        if self.dict.get(key,None):
            # pop node
            node = self._pop(key)
            # append node as new tail
            self._append(node)
            return self.posttail.prev.value
        else:
            return -1

    def put(self, 
            key: int, 
            value: int) \
            -> None:
        """
        Inserts the key-value pair in the LRUCache. If the key already exists, 
        its value is updated. If the LRUCache is already filled, the least 
        recent entry is deleted.
        Args:
            key: the key of interest.
            value: the value of interest.
        Returns:
            None
        """
        # insert
        if self.size < self.capacity:
            # this key is not present yet
            if self.dict.get(key,None) is None:
                # add in list
                node = ListNode(key,value,None,None)
                # LRUCache is empty
                if self.size == 0:
                    # new posttail
                    self.posttail = ListNode(-1,-1,None,None)
                    # new head
                    node.prev = self.prehead
                    node.next = self.posttail
                    self.prehead.next = node
                    self.posttail.prev = node
                    # add in dict
                    self.dict[key] = node
                else:
                    # append node as new tail
                    self._append(node)
                # increase size
                self.size += 1
            # update value
            else:
                # pop node and update value
                node = self._pop(key)
                node.value = value
                # append node as new tail
                self._append(node)
        # full
        else:
            # this key is not present yet, replace most ancient item
            if self.dict.get(key,None) is None:
                # pop head
                self._pop(self.prehead.next.key)
                node = ListNode(key,value,None,None)
                # append node as new tail
                self._append(node)
            # update value
            else:
                # pop node and update value
                node = self._pop(key)
                node.value = value
                # append node as new tail
                self._append(node)

    
    def to_array(self) \
        -> tp.List[tp.Tuple[int,int]]:
        """
        Returns the LRUCache as a list of tuple key-value, from the most 
        ancient to the most recent element.
        Returns:
            An array containing the key-value pairs of the instance.
        """
        l = []
        if self.size > 0:
            node = self.prehead.next
            for i in range(0,self.size):
                l.append((node.key,node.value))
                node = node.next
        return l

if __name__ == "__main__":
    

    #           ["LRUCache","get","put","get","put","put","get","get"]
    # parameter [[2],        [2], [2,6], [1],  [1,5],[1,2],[1],  [2]]
    # expected  [null,       -1,   null, -1,   null,  null, 2,    6]
    lRUCache = LRUCache(2)
    assert(lRUCache.get(2) == -1)
    lRUCache.put(2,6)
    assert(lRUCache.to_array() == [(2,6)])
    assert(lRUCache.get(1) == -1)
    lRUCache.put(1,5)
    assert(lRUCache.to_array() == [(2,6),(1,5)])
    lRUCache.put(1,2)
    assert(lRUCache.to_array() == [(2,6),(1,2)])
    assert(lRUCache.get(1) == 2)
    assert(lRUCache.to_array() == [(2,6),(1,2)])
    assert(lRUCache.get(2) == 6)
    assert(lRUCache.to_array() == [(1,2),(2,6)])
