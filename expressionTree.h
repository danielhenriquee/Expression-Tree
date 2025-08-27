#ifndef EXPRESSION_TREE_H_INCLUDED
#define EXPRESSION_TREE_H_INCLUDED

#include "binaryTree.h"
#include "linkedStack.h"
#include <cctype>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

// Defines the priority of the operator (priorize higher number)
int opPriority(char op) { 
    if (op == '+' || op == '-') // If + - priority = 1
        return 1;
    if (op == '*' || op == '/') // If * / priority = 2
        return 2;
    return 0; // If op is not an operator priority = 0 
};

// Connects an operator with two operands in a subtree and then push it back to stack
template <typename T>
void opSubtree(char op, Stack<TreeNode<T>*> &operands) { 
    TreeNode<T> *right = pop(operands); // Pop the right operand off the stack
    TreeNode<T> *left = pop(operands); // Pop the left operand off the stack
    TreeNode<T> *node = new TreeNode<T>; // Create a new node for the operator
    node->data = op;
    node->left = left; // Set the left child (left operand)
    node->right = right; // Set the right child (right operand)

    // The node consists of the operator and its childs are the operands
    // Eventually, an operator node will get as childs the others operators with their childs operands 
    push(operands, node); // Push the new subtree back to the operands stack
}

// Build expression tree
template <typename T>
TreeNode<T> buildExpressionTree(Tree<T> &tree, string expression) {
    Stack<TreeNode<T>*> operands, operators; // Stack of generic binary trees
    bootStack(operands); // Stack for operands
    bootStack(operators); // Stack for operators

    int i = 0; // Index to traverse the expression
    while (i < expression.length()) { 
        if (isspace(expression[i])) // Skip whitespaces
            i++;

        if (isdigit(expression[i])) { // If the character is a digit
            string num;
            while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')) // Check if is a decimal number
                num += expression[i++]; // Save number

            TreeNode<T> *newNode = new TreeNode<T>; 
            newNode->data = num; // Set number
            push(operands, newNode); // Push number to the operands stack

        } else if (expression[i] == '(') { // If the character is '('
            TreeNode<T> *newNode = new TreeNode<T>; 
            newNode->data = "("; // Set "("
            push(operators, newNode); // Push '(' to the operators stack
            i++;

        } else if (expression[i] == ')') { // If the character is ')', process the operators stack until '('
            while (!isEmpty(operators) && top(operators)->data != "(")
                opSubtree(pop(operators)->data[0], operands);

            pop(operators); // Pop the '('
            i++;

        } else { // The character is an operator
            char op = expression[i];
            while (!isEmpty(operators) && opPriority(top(operators)->data[0]) >= opPriority(op)) // While there are operators on the stack with higher or equal priority
                opSubtree(pop(operators)->data[0], operands); // Create operation sub-tree

            TreeNode<T> *newNode = new TreeNode<T>; 
            newNode->data = op; // Set operator
            push(operators, newNode); // Push operator to the operators stack
            i++; 
        }
    }

    // The node consists of the operator and its childs are the operands
    // Eventually, an operator node will get as childs the others operators with their childs operands 
    while (!isEmpty(operators)) // While operators stack not empty
         opSubtree(pop(operators)->data[0], operands);

    tree.root = pop(operands); // Set root of expression tree
    return *tree.root;
}

// Solve expression tree
template <typename T>
float solveExpressionTree(TreeNode<T> *root) {
    if (root->left == NULL && root->right == NULL) // Check if it is a leaf, ff the current node is a leaf, it must be a number
        return stof(root->data); // Convert string to float and return

    float leftSide = solveExpressionTree(root->left); // Solve left side
    float rightSide = solveExpressionTree(root->right); // Solve right side

    if (root->data == "+")
        return leftSide + rightSide; // Addition
    else if (root->data == "-")
        return leftSide - rightSide; // Subtraction
    else if (root->data == "*")
        return leftSide * rightSide; // Multiplication
    else {
        if (rightSide == 0) 
            cout << "\nErro: Houve uma divisão por zero.\n"; // Check for division by zero
        return leftSide / rightSide; // Division
    }
}

// Insert expression's implicit operands/operators
void processExpression(string &expression) {
    for (int i = 0; i < expression.length(); i++) {
        // Insert implicit '*' before '(' if preceding character is a digit
        if (expression[i] == '(' && i > 0 && isdigit(expression[i - 1])) {
            expression.insert(i, "*");
            i++;  // Skip the inserted '*'
        }

        // Insert implicit '0' after '(' if next character is '+' or '-'
        if (expression[i] == '(' && (expression[i+1] == '+' || expression[i+1] == '-')) {
            expression.insert(i+1, "0");
            i++;  // Skip the inserted '0'
        }
    }
}

// Get tree's height
template <typename T>
int getHeight(TreeNode<T> *root) {
    if (root == NULL)
        return 0;

    // Recursively get the height of the left and right subtrees, and add 1 for the current node
    return 1 + max(getHeight(root->left), getHeight(root->right)); // Return the heighter side of the subtree
}

// Get tree's columns
int getColumn(int height) {
    if (height == 1)
        return 1;

    // Recursively get the number of columns required based on the height of the tree
    return 1 + getColumn(height - 1) + getColumn(height - 1); // Height -1 because starts at the top and recursively go to the bottom level by level
}

// Auxiliar function to print tree // Fill all the matrix positions with their respectively data
template <typename T>
void AuxPrintTree(string **M, TreeNode<T> *root, int column, int level, int height) {
    if (root == NULL)
        return;

    // Set the current node's data in the respectively matrix position
    M[level][column] = root->data;

    // Recursively set the left and right children in their respectively matrix position
    // Parameter for columns ensures the spacing between columns is reduced by half at each level
    // Example: height = 4, then pow(2, 2) = 4, which means at the second level, the offset is 4 columns from the center
    // At the next level, height = 3, so, the offset is pow(2, 1) = 2 columns, and so on.
    AuxPrintTree(M, root->left, column - pow(2, height - 2), level + 1, height - 1); 
    AuxPrintTree(M, root->right, column + pow(2, height - 2), level + 1, height - 1);
}

// Function to print the tree in  a matrix format
template <typename T>
void printTree(Tree<T> tree) {
    int height = getHeight(tree.root); // Calculate the height of the tree
    int column = getColumn(height); // Calculate the number of columns required for the tree
    T **M = new T*[height]; // Create a dynamic matrix to represent the tree

    // Initialize all positions with a blank space
    for (int i = 0; i < height; i++) {
        M[i] = new T[column];
        for (int j = 0; j < column; j++)
            M[i][j] = " "; 
    }

    // column / 2 : starts at the center column, -1 to left side and +1 to right side
    // level = 0 : starts at root, +1 to go down through levels of the tree
    // height = remaining subtree's height, starts as tree's height
    AuxPrintTree(M, tree.root, column / 2, 0, height); // Fill the matrix with the correspondent data

    // Print matrix
    for (int i = 0; i < height; i++) { 
        for (int j = 0; j < column; j++)
            cout << setw(3) << M[i][j]; // Tab and print current node
        cout << endl;
    }

    // Delete matrix
    for (int i = 0; i < height; i++)
        delete[] M[i];
    delete[] M;
}

#endif // EXPRESSION_TREE_H_INCLUDED
