"""
Given the root of a binary tree, invert the tree, and return its root.

 

Example 1:


Input: root = [4,2,7,1,3,6,9]
Output: [4,7,2,9,6,3,1]
Example 2:


Input: root = [2,1,3]
Output: [2,3,1]
Example 3:

Input: root = []
Output: []
 

Constraints:

The number of nodes in the tree is in the range [0, 100].
-100 <= Node.val <= 100
"""

import typing as tp

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
    def invertTree(self, root: TreeNode | None) -> TreeNode | None:
        return Solution.traverse_depth_first(
            root, Solution.invert_node
        )

    @staticmethod
    def print_node(node: TreeNode) -> TreeNode:
        print(node)
        return node

    @staticmethod
    def invert_node(node: TreeNode) -> TreeNode:
        node.right, node.left = node.left, node.right
        return node
    
    @staticmethod
    def traverse_depth_first(
        root: TreeNode | None, 
        node_action: tp.Callable[[TreeNode], TreeNode] | None
    ) -> TreeNode | None:
        if not root:
            return root

        stack: list[TreeNode] = [root]
        visited: set[TreeNode] = set()

        while stack:
            node: TreeNode = stack.pop()
            if node not in visited:
                if node.right:
                    stack.append(node.right)
                if node.left:
                    stack.append(node.left)
                if node_action:
                    node_action(node)
        return root


if __name__ == "__main__":
    
    node_15 = TreeNode(15, None, None)
    node_7 = TreeNode(7, None, None)
    node_20 = TreeNode(20, node_15, node_7)
    node_14 = TreeNode(14, None, None)
    node_13 = TreeNode(13, node_14, None)
    node_12 = TreeNode(12, node_13, None)
    node_9 = TreeNode(9, None, node_12)
    root =  TreeNode(3, node_9, node_20)

    Solution.traverse_depth_first(
        Solution.traverse_depth_first(root, Solution.invert_node),
        Solution.print_node
    )