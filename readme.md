# P1-COP3530-EG
This was a project in COP3530 Data Structures and Algorithms at University of Florida. The assignment as to create a Binary Search Tree AVL Variant. The project requirements are listed below:

# Gator AVL Tree Project

## Overview
Binary Search Trees (BST) provide an efficient way to store and retrieve sorted data. However, standard BST performance degrades significantly if the tree becomes unbalanced. To guarantee logarithmic time complexity across operations, self-balancing trees like **AVL Trees** are used.

An AVL tree maintains balance by ensuring that for every node, the height difference between its left and right subtrees (the **balance factor**) does not exceed $\pm 1$. Whenever an insertion or deletion causes a node's balance factor to reach $+2$ or $-2$, standardized tree rotations (Left, Right, Left-Right, Right-Left) are performed.

In this project, you will implement a custom AVL Tree data structure to organize University of Florida student accounts indexed by their 8-digit **GatorID**.

---

## Core Responsibilities
- Design and encapsulate a custom AVL Tree class (properly separating public and private member methods).
- Implement standard operations: insertion, search, deletion, and traversals.
- Parse command-line input and strictly validate all commands and data formats.
- Execute corresponding operations and produce formatted outputs to standard output (`std::cout`).

---

## Command Interface & Functionality

| Command | Arguments | Description & Output Requirements |
| :--- | :--- | :--- |
| `insert` | `"<NAME>"` `<ID>` | Adds a student node into the tree. Automatically balances via rotations. Prints `successful` on success, or `unsuccessful` if the ID is a duplicate or fails validation. |
| `remove` | `<ID>` | Removes the node matching `<ID>`. Replaces a two-child node with its **inorder successor**. Prints `successful` on success, or `unsuccessful` if not found. *(Self-balancing on deletion is optional; test cases guarantee post-deletion balance).* |
| `search` | `<ID>` | Searches for the student by GatorID. Prints the associated `NAME` if found, or `unsuccessful`. |
| `search` | `"<NAME>"` | Searches for student(s) with `<NAME>`. Prints matching GatorIDs (each on a new line in **preorder traversal order**), or `unsuccessful` if not found. |
| `printInorder` | *None* | Prints a comma-separated list of student names following an **inorder** traversal. |
| `printPreorder` | *None* | Prints a comma-separated list of student names following a **preorder** traversal. |
| `printPostorder` | *None* | Prints a comma-separated list of student names following a **postorder** traversal. |
| `printLevelCount` | *None* | Prints the total number of levels in the tree (prints `0` if empty). |
| `removeInorder` | `<N>` | Removes the $N$-th node in an inorder traversal ($0$-indexed). Prints `successful` on success, or `unsuccessful` if index $N$ is invalid. |

---

## Data Validation & Constraints

### Validation Rules
Any input violating the following criteria must immediately print `unsuccessful` and proceed to the next command:
- **GatorID (UFID):** Must be strictly an **8-digit numerical string** (e.g., `12345678`) and unique within the tree.
- **Name:** Must be enclosed in double quotes (e.g., `"First Last"`) and contain only alphabetic characters (`a-z`, `A-Z`) and whitespace.
- **Commands:** Any misspelled or unrecognized command must print `unsuccessful`.

### Testing Limits
- $1 \le \text{Number of Commands} \le 1000$
- $6 \le \text{Length of a Command} \le 1000$
- Commands run strictly on a single line and contain no newline characters (`\n`) except at the line's termination.

---

## Technical Specifications
- **Language Standard:** C++14.
- **Ordering Key:** The tree must be sorted strictly by numerical **GatorID** (not by name) from least to greatest:
  - Left subtree: keys $<$ node key
  - Right subtree: keys $>$ node key
- **Rotations:** You must implement all four standard AVL rotations:
  - Left Rotation (LL)
  - Right Rotation (RR)
  - Left-Right Rotation (LR)
  - Right-Left Rotation (RL)

---

## Example Usage

### Input
The first line contains an integer $N$ denoting the number of commands to execute.

```text
8
insert "Brandon" 45679999
insert "Brian" 35459999
insert "Briana" 87879999
insert "Bella" 95469999
printInorder
remove 45679999
removeInorder 2
printInorder
