#include "binaryTree.h"
#include "expressionTree.h"
#include "linkedStack.h"
#include <iostream>
using namespace std;

void clear() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pause() {
    cout << "\nPress ENTER to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int main() {
    bool menu = true;
    int option;
    string expression = "";
    Tree<string> tree; 
    bootTree(tree);
    
    while (menu) {
        clear();
        cout << endl << endl;
        cout << "+========== Expression Tree ==========+" << endl;
        cout << "| |=| 1  -  Enter expression          |" << endl;
        cout << "| |=| 2  -  Show expression entered   |" << endl;
        cout << "| |=| 3  -  Build expression tree     |" << endl;
        cout << "| |=| 4  -  Solve expression tree     |" << endl;
        cout << "| ----------------------------------- |" << endl;
        cout << "| |=| 5  -  Reset expression tree     |" << endl;
        cout << "| |=| 6  -  Exit                      |" << endl;
        cout << "+================ MENU ===============+" << endl;
        cin >> option;
        
        switch (option) {
        case 1:
            clear();
            cout << "The program supports the use of decimal numbers, the operations + - * / and the proper use of parentheses.\n";
            cout << "Enter the expression:" << endl;
            cin.ignore();
            getline(cin, expression);
            processExpression (expression);
            pause();
            break;
        case 2:
            clear();
            if (expression.empty())
                cout << "There is no expression entered.\n";
            else
                cout << "Entered expression:\n" << expression;
            pause();
            break;
        case 3:
            clear();
            try {
                buildExpressionTree(tree, expression);
                printTree(tree);
            } catch (const underflow_error &e) {
                cout << "Error: incorrectly formed expression.\n";
            }
            pause();
            break;
        case 4:
            clear();
            if (tree.root != NULL)
                cout << "The result of the entered expression is: " << solveExpressionTree(tree.root) << endl;
            else
                cout << "The expression tree is empty.\n";
            pause();
            break;
        case 5:
            clear();
            bootTree(tree);
            cout << "Expression tree reset.\n";
            pause();
            break;
        case 6:
            clear();
            menu = 0;
            destroyTree(tree.root);
            break;
        default:
            clear();
            cout << "Invalid option";
            pause();
            break;
        }
    }
    return 0;
}