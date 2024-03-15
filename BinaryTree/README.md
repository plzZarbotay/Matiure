# Priority Task: The values of the leaf of a binary tree with the minimum depth were determined.
![Matiure Logo](/BinaryTree/data/tree.png)
C program was utilized to construct and process an ordered binary tree containing nodes of type int. The structure was defined using struct Tree.

The main functions for working with trees were implemented as universal procedures or functions. After the tree was created, its processing was performed through a text menu with the following actions:

[<<Open_Code>>](https://github.com/plzZarbotay/Matiure/blob/master/BinaryTree/main.c)

- Adding a new node (for a binary tree, the position of the new node was determined according to the requirement to maintain order; for a general tree, the parent of the added node was specified. The added node became the youngest child).
- Textual visualization of the tree (the value of each node was output on a separate line, with an indent proportional to the depth of the node, in the order of seniority of the nodes).
- Deleting a node (the binary tree was rebuilt according to the requirement to maintain integrity and order; for a general tree, the entire subtree originating from the deleted node was removed. Proper memory deallocation was provided).
- Calculating the value of a certain function of the tree (integer or logical), according to the variant number.

