# AVL Tree

In this Java programming project, an AVL tree was implemented with a GUI window to display the tree. 

## Background

An AVL tree is a balanced binary search tree where for each node in the tree, the heights of the left and right subtrees differ by at most one. For each node, there is a small red number displayed. This number is called the **balance factor**: height of the left subtree minus the height of the right subtree. After insertion, the deepest (furthest from root) node on the path from the insertion point to the root with a non-zero balance factor is called the **pivot**. After an insertion, the balance factors must be updated. If the balance factor of the pivot is 2 or -2, a rotation is need to rebalance the tree.

### Rotations
  **LL**: an insertion into the left subtree of the left child of the pivot node
  
  **RL**: an insertion into the right subtree of the left child of the pivot node
  
  **LR**: an insertion into the left subtree of the right child of the pivot node
  
  **RR**: an insertion into the right subtree of the right child of the pivot node

![AVL Tree](https://github.com/mbcolson/Academic-Programming-Projects/blob/master/AVL_Tree/AVL_Tree_Screenshot.png)
