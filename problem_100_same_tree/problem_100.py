"""
Given the roots of two binary trees p and q, write a function to check if they are the same or not.

Two binary trees are considered the same if they are structurally identical, and the nodes have the same value.

 

Example 1:


Input: p = [1,2,3], q = [1,2,3]
Output: true
Example 2:


Input: p = [1,2], q = [1,null,2]
Output: false
Example 3:


Input: p = [1,2,1], q = [1,1,2]
Output: false
 

Constraints:

The number of nodes in both trees is in the range [0, 100].
-104 <= Node.val <= 104
"""

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

    def __str__(self) -> str:
        return f"<value:{self.val}, left:{id(self.left)}, right:{id(self.right)}>"

    def __repr__(self) -> str:
        return str(self)
    
    def __hash__(self) -> int:
        return hash(str(self))

class Solution:
    def isSameTree(self, tree1: TreeNode | None, tree2: TreeNode | None) -> bool:
        if tree1 is None and tree2 is None:
            return True
        if not tree1 or not tree2:
            return False
        
        stack: list[TreeNode] = [(tree1, tree2)]

        while stack:
            node_1, node_2 = stack.pop()
            print(f"{node_1=}")
            print(f"{node_2=}")
            if not Solution.compare_nodes(node_1, node_2):
                return False
            if node_1:
                stack.append((node_1.left, node_2.left))
                stack.append((node_1.right, node_2.right))

            
        return True

    @staticmethod
    def compare_nodes(node1: TreeNode | None, node2: TreeNode | None) -> bool:
        # both None
        if node1 is None and node2 is None:
            return True
        # one None
        if node1 is None or node2 is None:
            return False
        return node1.val == node2.val
    
if __name__ == "__main__":
    
    node_3 = TreeNode(3, None, None)
    node_2 = TreeNode(2, None, None)
    tree_1 = TreeNode(1, node_2, node_3)
    tree_2 = TreeNode(1, node_2, node_3)

    

    print(Solution().isSameTree(tree_1, tree_2))        