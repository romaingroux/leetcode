"""
Implement the RandomizedSet class:

RandomizedSet() Initializes the RandomizedSet object.
bool insert(int val) Inserts an item val into the set if not present. 
    Returns true if the item was not present, false otherwise.
bool remove(int val) Removes an item val from the set if present. 
    Returns true if the item was present, false otherwise.
int getRandom() Returns a random element from the current set of elements 
    (it's guaranteed that at least one element exists when this method is 
    called). Each element must have the same probability of being returned.
You must implement the functions of the class such that each function works in 
    average O(1) time complexity.

 

Example 1:

Input
["RandomizedSet", "insert", "remove", "insert", "getRandom", "remove", "insert", "getRandom"]
[[], [1], [2], [2], [], [1], [2], []]
Output
[null, true, false, true, 2, true, false, 2]

Explanation
RandomizedSet randomizedSet = new RandomizedSet();
randomizedSet.insert(1); // Inserts 1 to the set. Returns true as 1 was inserted successfully.
randomizedSet.remove(2); // Returns false as 2 does not exist in the set.
randomizedSet.insert(2); // Inserts 2 to the set, returns true. Set now contains [1,2].
randomizedSet.getRandom(); // getRandom() should return either 1 or 2 randomly.
randomizedSet.remove(1); // Removes 1 from the set, returns true. Set now contains [2].
randomizedSet.insert(2); // 2 was already in the set, so return false.
randomizedSet.getRandom(); // Since 2 is the only number in the set, getRandom() will always return 2.
 

Constraints:

-231 <= val <= 231 - 1
At most 2 * 105 calls will be made to insert, remove, and getRandom.
There will be at least one element in the data structure when getRandom is called.
"""

import random


class RandomizedSet:

    def __init__(self):
        """
        Constructor.
        Constructs an empty set.
        """

        # the actual set of elements
        self._set = list()
        # a map with the elements (key) and there index in the set (value)
        self._map = dict()
    
    def __repr__(self) \
        -> str:

        return f"RandomizedSet\n" \
               f"<{self._set}>\n" \
               f"<{self._map}>"


    def insert(self, val: int) \
        -> bool:
        """
        Inserts val in the set in O(1) time.
        Args:
            val: the item to insert.
        Returns:
            True if item was not present, False otherwise.
        """

        if self._map.get(val, None) is None:
            self._set.append(val)
            self._map[val] = len(self._set) - 1
            return True
        else:
            return False

    def remove(self, val: int) \
        -> bool:
        """
        Removes val from the set in O(1) time.
        Args:
            val: the item to remove.
        Returns:
            True if the item was present, False otherwise.
        """

        idx = self._map.get(val, None)
        # to remove, swap val to last position to allow O(1) pop
        if idx is not None:
            # swap
            # val_idx = self._set[idx]
            val_last = self._set[-1]
            self._set[idx] = val_last
            self._set[-1] = val
            # update map
            self._map[val_last] = idx
            # pop 
            self._set.pop()
            self._map.pop(val)
            return True
        else:
            return False

    def getRandom(self) \
        -> int:
        """
        Gets an item in the set at random, with a uniform 
        probability in O(1) time.
        Returns:
            An item in the set.
        """
        idx = random.randint(0, len(self._set)-1)
        return self._set[idx]
    

if __name__ == "__main__":
    # Your RandomizedSet object will be instantiated and called as such:
    obj = RandomizedSet()
    print(f"insert 10 {obj.insert(10)}")
    print(f"insert 10 {obj.insert(10)}")
    print(obj)
    print(f"insert 20 {obj.insert(20)}")
    print(obj)
    print(f"remove 10 {obj.remove(10)}")
    print(obj)
    # param_2 = obj.remove(20)
    # param_3 = obj.getRandom()