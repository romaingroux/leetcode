"""
Given the root of a binary tree, return its maximum depth.

A binary tree's maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

Input: root = [3,9,20,null,null,15,7]
Output: 3
Example 2:

Input: root = [1,null,2]
Output: 2

"""

import collections

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
    def maxDepth(self, root: TreeNode | None) -> int:
        if root is None:
            return 0
        
        height = 1
        stack: list[TreeNode] = [(root, 1)]
        visited: set[TreeNode] = set()
    
        while len(stack):
            node, level = stack.pop()
            if level > height:
                height = level
            if node not in visited:
                if node.left is not None:
                    stack.append((node.left, level+1))
                if node.right is not None:
                    stack.append((node.right, level+1))
        return height


def traverse_depth_first(tree_root: TreeNode):

    stack: list[TreeNode] = [tree_root]
    visited: set[TreeNode] = set()
    while len(stack):
        node: TreeNode = stack.pop()
        if node not in visited:
            print(node)
            if node.left is not None:
                stack.append(node.left)
            if node.right is not None:
                stack.append(node.right)

def traverse_width_first(tree_root: TreeNode):

    queue: collections.deque[TreeNode] = collections.deque([tree_root])
    visited: set[TreeNode] = set()
    while len(queue):
        node: TreeNode = queue.popleft()
        if node not in visited:
            print(node)
            if node.left is not None:
                queue.append(node.left)
            if node.right is not None:
                queue.append(node.right)

def traverse_depth_first_len(tree_root: TreeNode | None):

    height = 1
    stack: list[TreeNode] = [(tree_root, 1)]
    visited: set[TreeNode] = set()

    while len(stack):
        node, level = stack.pop()
        if level > height:
            height = level
        if node not in visited:
            if node.left is not None:
                stack.append((node.left, level+1))
            if node.right is not None:
                stack.append((node.right, level+1))
    return height


if __name__ == "__main__":
    
    node_15 = TreeNode(15, None, None)
    node_7 = TreeNode(7, None, None)
    node_20 = TreeNode(20, node_15, node_7)
    node_14 = TreeNode(14, None, None)
    node_13 = TreeNode(13, node_14, None)
    node_12 = TreeNode(12, node_13, None)
    node_9 = TreeNode(9, None, node_12)
    root =  TreeNode(3, node_9, node_20)

    print(traverse_width_first(root))