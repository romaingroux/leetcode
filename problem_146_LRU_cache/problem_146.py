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


def make_list(values: tp.List[tp.Tuple[int,int]]) \
    -> tp.Optional[ListNode]:
    """
    Create a linked list with the given values and return the 
    head node.
    Args:
        values: the values of the nodes.
    Returns:
        The head of the list.
    """
    # prehead
    prehead = ListNode(-999,-999)
    cur = prehead

    for i in range(0,len(values)):
        cur.next = ListNode(values[i][0],
                            values[i][1],
                            cur)
        cur = cur.next
    
    head = prehead.next
    head.prev = None
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


class LRUCache:

    def __init__(self, 
                 capacity: int):
        """
        Constructs a LRUCache with the given capacity.
        Args:
            capacity: the LRUCache capacity.
        """

        """Pointer to most ancient LRUCache item (list head)"""
        self.head = None
        """Pointer to most recent LRUCache item (list tail)"""
        self.tail = None
        """LRUCache dictionary"""
        self.dict = dict()
        """Capacity"""
        self.capacity = capacity
        """Current number of pairs"""
        self.size = 0
    
    def __str__(self) \
        -> str:
        """
        Returns a string representation of the instance.
        Returns:
            A string representation of the instance.
        """
        l = []
        l.append(f"{self.size}/{self.capacity}")
        node = self.head
        while node:
            l.append(str(node))
            node = node.next
        return ",".join(l)

    def get(self, 
            key: int) \
        -> int:
        """
        Returns the item with the value corresponding to this key.
        Args:
            key: the key of interest.
        Returns:
            The corresponding value, -1 if the key could not be found.
        """
        node = self.dict.get(key,None)
        return node.value if node else -1

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
                node = ListNode(key,value,self.tail,None)
                if self.head is None:
                    self.head = node
                    self.tail = node
                else:
                    self.tail.next = node
                    self.tail = self.tail.next
                # add in dict
                self.dict[key] = self.tail
                # increase size
                self.size += 1
            # update value
            else:
                node = self.dict[key]
                node.value = value
        # delete most ancient item
        else:
            node = ListNode(key,value,self.tail,None)
            # remove from dir
            del self.dict[self.head.key]
            # new head in list
            self.head = self.head.next
            # new tail
            self.tail.next = node
            self.tail = self.tail.next
    
    def to_array(self) \
        -> tp.List[tp.Tuple[int,int]]:
        """
        Returns the LRUCache as a list of tuple key-value, from the most 
        ancient to the most recent element.
        Returns:
            An array containing the key-value pairs of the instance.
        """
        l = []
        node = self.head
        while node:
            l.append((node.key,node.value))
            node = node.next
        return l

if __name__ == "__main__":

    # Your LRUCache object will be instantiated and called as such:
    # obj = LRUCache(capacity)
    # param_1 = obj.get(key)
    # obj.put(key,value)

    # cache = LRUCache(4)
    # cache.put(1,2)
    # print(cache)
    # cache.put(3,4)
    # print(cache)
    # cache.put(5,6)
    # print(cache)
    # cache.put(7,8)
    # print(cache)
    # cache.put(9,10)
    # print(cache)
    # cache.put(11,12)
    # print(cache)
    
    lRUCache = LRUCache(2);
    lRUCache.put(1, 1)          #  cache is {1=1}
    assert(lRUCache.to_array() == [(1,1)])
    lRUCache.put(2, 2)          # cache is {1=1, 2=2}
    assert(lRUCache.to_array() == [(1,1),(2,2)])
    assert(lRUCache.get(1)== 1) #  return 1
    lRUCache.put(3, 3)          #  LRU key was 2, evicts key 2, cache is {1=1, 3=3}
    assert(lRUCache.to_array() == [(1,1),(3,3)])
    # assert(lRUCache.get(2) == -1)        #  returns -1 (not found)
    # lRUCache.put(4, 4) ; print(lRUCache) #  LRU key was 1, evicts key 1, cache is {4=4, 3=3}
    # lRUCache.get(1)                      #  return -1 (not found)
    # lRUCache.get(3)                      #  return 3
    # lRUCache.get(4)                      #  return 4

