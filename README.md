<div align="center">

# 🌌 Advanced Data Structures & Algorithms (ADSA) Lab
### M.Tech 1st Semester | NIT Jamshedpur
**Course Codes:** CS4105 / CS4116 / CS4125 / CS4135

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Java](https://img.shields.io/badge/Java-ED8B00?style=for-the-badge&logo=openjdk&logoColor=white)
![Algorithms](https://img.shields.io/badge/Focus-Optimization-ff69b4?style=for-the-badge)

*A comprehensive repository for ADSA lab assignments, strictly adhering to C programming for algorithmic efficiency and advanced data structure implementations.*

</div>

---

## ⚠️ Lab Instructions & Guidelines
* **Language Constraint:** Use strictly the C programming language for all problem sets. No other languages (C++, Python, Java, etc.) are permitted, except for the Project in Set 10 which requires Java or a web framework.
* **Robustness:** Programs must execute without errors across all possible input values and must handle illegal inputs gracefully without terminating via runtime errors.
* **I/O Efficiency:** Large datasets (such as a 3x4 or larger size matrix) must be read from text files to edit input values efficiently for multiple runs.

## 📅 Weekly Assignment Sets

| Set | Domain | Topics Covered |
| :--- | :--- | :--- |
| **Set 1** | Stack Applications | Infix to postfix conversion and arithmetic expression evaluation via command-line arguments. |
| **Set 2** | Sorting Algorithms | Implementation of 12 distinct sorting algorithms (including Address Calculation and Radix Exchange). Implementation of top-down (stack-based) and bottom-up (nested loops) non-recursive Merge Sort. |
| **Set 3** | Queues & Stacks | Circular queues using arrays and linked lists. Implementation of a queue via two stacks and a stack via two queues (testing costly push/pop and enqueue/dequeue operations). |
| **Set 4** | Advanced Trees | Non-recursive binary tree preorder traversal. Implementation of AVL, Red-Black, B-Trees, and B+ Trees (Note: strictly implement B+ Tree leaf nodes to contain exactly $k$ record pointers). |
| **Set 5** | Graph Algorithms I | Dijkstra's, Prim's, and Kruskal's algorithms. DFS with edge classification (tree, back, forward, cross) and cycle detection (identifying largest and smallest cycles). |
| **Set 6** | Algorithmic Paradigms I | Bellman-Ford and Floyd-Warshall (DP) for shortest paths. 0/1 Knapsack (DP & Backtracking). N-Queens (Backtracking) and 15-Puzzle (Branch and Bound). |
| **Set 7** | Algorithmic Paradigms II | Coin changing (Greedy), Job sequencing with deadlines, and Graph coloring (Backtracking). Identification of SCCs, BCCs, articulation points, bridges, and Topological sort. TSP implementation with runtime profiling graphs for up to 100 nodes. |
| **Set 8** | NP-Hard Problems | Algorithms to determine cliques of size m, Hamiltonian cycles, and bipartite graph properties. |
| **Set 9** | Strings & Geometry | Rabin-Karp, KMP, and Boyer-Moore string matching algorithms. Graham Scan or Jarvis March for finding a convex hull. |
| **Set 10** | Capstone Project | **JEES System:** A Java GUI or Web-based software to process JEE main results, handling unique category-based roll numbers and merit serial generation based on strict tie-breaking rules. |

## 📂 Suggested Repository Structure

```text
📦 ADSA_Lab_MTech
 ┣ 📂 Set_01_Stack_Apps
 ┣ 📂 Set_02_Sorting
 ┣ 📂 Set_03_Queues_Stacks
 ┣ 📂 Set_04_Advanced_Trees
 ┣ 📂 Set_05_Graphs_1
 ┣ 📂 Set_06_Paradigms_1
 ┣ 📂 Set_07_Paradigms_2
 ┣ 📂 Set_08_NP_Hard
 ┣ 📂 Set_09_Strings_Geometry
 ┣ 📂 Set_10_JEES_Project
 ┣ 📂 test_cases
 ┗ 📜 README.md
