# red-black-tree-c
A complete C implementation of Red-Black Trees featuring insertion, deletion, rebalancing rotations, and level-order tree visualization.

---

## 📌 Overview & Properties

A Red-Black Tree is a self-balancing binary search tree that guarantees $O(\log n)$ time complexity for search, insertion, and deletion operations by maintaining the following invariants:
1. **Node Color:** Every node is either `RED` or `BLACK`.
2. **Root Property:** The root is always `BLACK`.
3. **Leaf Property:** Every leaf (`NIL` sentinel) is `BLACK`.
4. **Red Property:** If a node is `RED`, both its children are `BLACK` (no two consecutive red nodes on any path).
5. **Black Height:** Every path from a given node to any of its descendant `NIL` leaves contains the same number of black nodes.

---

## ⚙️ Features
- **Sentinel `NIL` Representation:** Robust edge-case handling using sentinel `NIL` nodes for leaves and parent bounds.
- **Tree Balancing Rotations:** Left and Right tree rotations (`LEFT_ROTATE`, `RIGHT_ROTATE`).
- **Insertion with Fixup:** Standard BST insertion followed by color flips and rotations to restore RBT invariants.
- **Deletion with Fixup:** Deletion using node transplantation (`RB_TRANSPLANT`) and double-black resolution (`RB_DELETE_FIXUP`).
- **Tree Visualization:** Level-by-level array mapping (`PrintTree`) and structured traversal (`TT`) displaying node keys, colors, and parent/child relationships.
- **Interactive CLI:** Terminal-driven menu for interactive testing and demonstration.

---

## 🛠️️ Build & Run

### Prerequisites
- GCC / Clang compiler
- Standard C libraries (`stdio.h`, `stdlib.h`, `math.h`)

### Compilation
Compile the source using `gcc` (link the math library with `-lm`):
```bash
gcc -Wall -Wextra -O2 src/red_black_tree.c -lm -o rbt
