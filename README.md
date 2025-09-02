# Expression-Tree
Expression Tree - Project for Data Structures - 2024/1

This project implements an Expression Tree, a specialized binary tree used to represent and evaluate mathematical expressions. It supports parsing infix expressions with parentheses and standard arithmetic operators, automatically building the corresponding binary tree and enabling its evaluation and visualization.

The project’s main purpose is to serve as educational material for combining multiple data structures (binary trees, stacks, and string parsing) into a single application. It is also reusable as a base for academic projects requiring expression parsing or evaluation.

**Contents**
- binaryTree.h – Definition of a generic binary tree and node structure
- linkedStack.h – Implementation of a generic stack using linked nodes
- expressionTree.h – Expression tree construction, evaluation, and visualization functions
- main.cpp – Menu-driven program for interactive testing

**Features**
- Parsing of infix mathematical expressions (e.g., (3+5)*2-8/4)
- Automatic construction of the corresponding expression tree
- Handling of parentheses, decimal numbers, and operator precedence
- Implicit operator handling:
  - 2(3+4) is treated as 2*(3+4)
  - (-5+3) is treated as (0-5+3)
  - Simplification of sequences such as --, +-, etc.
- Tree visualization in matrix form for debugging and educational purposes
- Evaluation of the full expression tree with support for +, -, *, /
- Error handling for malformed expressions and division by zero

**Usage**
1. Compile the program with a C++ compiler:
    - g++ main.cpp -o expression-tree
2. Run the program:
    - ./expression-tree
3. Use the interactive menu to:
    - Enter an expression
    - View the entered expression
    - Build and print the expression tree
    - Solve the expression and display its result
    - Reset the tree or exit

**Notes**
- The tree is internally implemented as a generic binary tree (Tree<T>), but expression handling assumes T = string.
- The stack implementation (LinkedS_TList) is generic and reusable in other contexts.
- Operator precedence follows standard arithmetic rules:
- *, / have higher precedence than +, -
- The visual printing function is designed for understanding tree structure, not formatted output.
- Division by zero does not stop the program but prints an error message.
