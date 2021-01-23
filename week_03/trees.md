# Trees in C++

## Basic terms

- **Root node:** the topmost node in the tree hierarchy. The root node doesn’t have a parent node;
- **Leaf node:** the bottom most node in a tree hierarchy. Leaf nodes are the nodes that do not have any child nodes. They are also known as external nodes;
- **Subtree:** represents various descendants of a node when the root is not null. A tree usually consists of a root node and one or more subtrees;
- **Parent node:** any node except the root node that has a child node and an edge upward towards the parent;
- **Ancestor node:** any predecessor node on a path from the root to that node. Note that the root does not have any ancestors;
- **Key:** the value of a node;
- **Level:** the generation of a node. A root node is always at level 1. Child nodes of the root are at level 2, grandchildren of the root are at level 3 and so on. In general, each node is at a level higher than its parent;
- **Path:** a sequence of consecutive edges;
- **Degree:** indicates the number of children that a node has;

## Types of trees in C++

### General tree (N-ary tree)

The general tree is the basic representation of a tree. It has a node and one or more child nodes. The top-level node i.e. the root node is present at level 1 and all the other nodes may be present at various levels. Each node can have arbitrary number of children.

```
// Represents a node of an n-ary tree
struct Node
{
    int key;
    vector<Node*> child;
};
```

**Example tasks:**

- Given a n-ary tree, count the number of nodes which have more children than their parents.
- Tree dictionary.
- Find the depth of the tree.

  > maxDepth()
  >
  > 1.  If tree is empty then return 0
  > 2.  Else
  >     (a) Get the max depth of left subtree recursively i.e.,
  >     call maxDepth( tree->left-subtree)
  >
  >     (b) Get the max depth of right subtree recursively i.e.,
  >     call maxDepth( tree->right-subtree)
  >
  >     (c) Get the max of max depths of left and right
  >     subtrees and add 1 to it for the current node.
  >     max_depth = max(max dept of left subtree,  
  >      max depth of right subtree) + 1
  >
  >     (d) Return max_depth


### Binary trees
- Properties:

1. The maximum number of nodes at level ‘l’ of a binary tree is 2^l. 

Here level is the number of nodes on the path from the root to the node (including root and node). Level of the root is 0. 

This can be proved by induction. 

For root, l = 0, number of nodes = 20 = 1 

Assume that the maximum number of nodes on level ‘l’ is 2^l 

Since in Binary tree every node has at most 2 children, next level would have twice nodes, i.e. 2 * 2^l 

2. The Maximum number of nodes in a binary tree of height ‘h’ is 2^h – 1. 

Here the height of a tree is the maximum number of nodes on the root to leaf path. Height of a tree with a single node is considered as 1. 

This result can be derived from point 2 above. A tree has maximum nodes if all levels have maximum nodes. So maximum number of nodes in a binary tree of height h is 1 + 2 + 4 + .. + 2h-1. This is a simple geometric series with h terms and sum of this series is 2^h – 1. 

In some books, the height of the root is considered as 0. In this convention, the above formula becomes 2^h+1 – 1 

3. In a Binary Tree with N nodes, minimum possible height or the minimum number of levels is? Log2(N+1) ?   
This can be directly derived from point 2 above. If we consider the convention where the height of a leaf node is considered as 0, then above formula for minimum possible height becomes? Log2(N+1) ? – 1 

4. A Binary Tree with L leaves has at least? Log2L? + 1   levels 
A Binary tree has the maximum number of leaves (and a minimum number of levels) when all levels are fully filled. Let all leaves be at level l, then below is true for the number of leaves L. 
