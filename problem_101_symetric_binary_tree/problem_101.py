"""
Given the root of a binary tree, check whether it is a mirror of itself (i.e., symmetric around its center).


Example 1:


Input: root = [1,2,2,3,4,4,3]
Output: true
Example 2:


Input: root = [1,2,2,null,3,null,3]
Output: false
 

Constraints:

The number of nodes in the tree is in the range [1, 1000].
-100 <= Node.val <= 100
 

Follow up: Could you solve it both recursively and iteratively?
"""
import typing as tp


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

    def __str__(self) -> str:
        return f"<value:{self.val}, " \
            f"left:{id(self.left) if self.left else None}, " \
            f"right:{id(self.right) if self.right else None}>"

    def __repr__(self) -> str:
        return str(self)
    
    def __hash__(self) -> int:
        return hash(str(self))


class Solution:
    
    def isSymmetric(self, root: TreeNode | None) -> bool:
        """Tells if the tree is symetric, i.e. that both subtrees are symetrics.
        """
        # no subtree -> symetric
        if not root:
            return True
        # only a root -> symetric
        if not root.left and not root.right:
            return True
        # subtrees -> check
        if root.left and root.right:
            sub_tree_left = root.left
            sub_tree_right = Solution.traverse(root.right, Solution.invert_node)
            return Solution.is_same_tree(sub_tree_left, sub_tree_right)
        # only left or right sub-tree -> not symetric
        else:
            return False

    @staticmethod
    def traverse(
        root: TreeNode | None,
        node_action: tp.Callable[[TreeNode], TreeNode] | None
    ) -> TreeNode:
        """Traverses the tree depth first starting at <root> and applies 
        <node_action(node)> on each node and returns the resulting tree.
        """
        stack: list[TreeNode] = [root]
        visited: set[TreeNode] = set()

        while stack:
            node: TreeNode = stack.pop()
            if node not in visited:
                if node.left:
                    stack.append(node.left)
                if node.right:
                    stack.append(node.right)
                if node_action:
                    node = node_action(node)
                visited.add(node)
        return root

    @staticmethod
    def is_same_tree(tree_1: TreeNode | None, tree_2: TreeNode | None ) -> bool:
        """Tells whether both trees are the same or not."""

        if not tree_1 and not tree_2:
            return True
        if not tree_1 or not tree_2:
            return False

        stack: list[TreeNode] = [(tree_1, tree_2)]

        while stack:
            node_1, node_2 = stack.pop()
            if not Solution.is_same_node(node_1, node_2):
                return False
            if node_1:
                stack.append((node_1.left, node_2.left))
                stack.append((node_1.right, node_2.right))
        return True

        
    @staticmethod
    def is_same_node(node_1: TreeNode | None, node_2: TreeNode | None) -> bool:
        """Tells whether both nodes are the same or not."""
        if not node_1 and not node_2:
            return True
        if not node_1 or not node_2:
            return False
        return node_1.val == node_2.val
    
    @staticmethod
    def invert_node(node: TreeNode) -> TreeNode:
        """Inverts the children in place and returns the node"""
        node.right, node.left = node.left, node.right
        return node

    @staticmethod
    def print_node(node: TreeNode) -> TreeNode:
        """Prints the node and returns it"""
        print(node)
        return node

if __name__ == "__main__":
    
    # node_15 = TreeNode(15, None, None)
    # node_7 = TreeNode(7, None, None)
    # node_20 = TreeNode(20, node_15, node_7)
    # node_14 = TreeNode(14, None, None)
    # node_13 = TreeNode(13, node_14, None)
    # node_12 = TreeNode(12, node_13, None)
    # node_9 = TreeNode(9, None, node_12)

    # node_9  = TreeNode(9, None, None)
    # node_20 = TreeNode(9, None, None)
    root    =  TreeNode(1, None, None)

    # Solution.traverse(root, Solution.print_node)
    print(Solution().isSymmetric(root))