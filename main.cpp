#include "binaryTree.h"
#include "expressionTree.h"
#include "linkedStack.h"
#include <iostream>
using namespace std;

int main() {
    bool menu = true;
    int resp;
    string expression = "";
    Tree<string> tree; 
    bootTree(tree);
    
    while (menu) {
        cout << endl << endl;
        cout << "+===========Árvore de Expressão===========+" << endl;
        cout << "| |=| 1  -  Inserir expressão             |" << endl;
        cout << "| |=| 2  -  Mostrar expressão             |" << endl;
        cout << "| |=| 3  -  Construir árvore de expressão |" << endl;
        cout << "| |=| 4  -  Resolver árvore de expressão  |" << endl;
        cout << "| --------------------------------------- |" << endl;
        cout << "| |=| 5  -  Reiniciar                     |" << endl;
        cout << "| |=| 6  -  Sair                          |" << endl;
        cout << "+==================MENU===================+" << endl;
        cin >> resp;
        
        switch (resp) {
        case 1:
            // system("CLS");
            cout << "\033c";
            cout << "O programa suporta o uso de números decimais, as operações + - * / e o uso de parênteses.\n";
            cout << "Insira a expressão:" << endl;
            cin >> expression;
            processExpression (expression);
            break;
        case 2:
            // system("CLS");
            cout << "\033c";
            if (expression.empty())
                cout << "Não há expressão inserida.\n";
            else
                cout << "Expressão inserida:\n" << expression;
            break;
        case 3:
            // system("CLS");
            cout << "\033c";
            buildExpressionTree(tree, expression);
            printTree(tree);
            break;
        case 4:
            // system("CLS");
            cout << "\033c";
            if (tree.root != NULL)
                cout << "O resultado da expressão inserida é: " << solveExpressionTree(tree.root) << endl;
            else
                cout << "A árvore de expressão está vazia.\n";
            break;
        case 5:
            // system("CLS");
            cout << "\033c";
            bootTree(tree);
            break;
        case 6:
            cout << "\033c";
            menu = 0;
            break;
        default:
            // system("CLS");
            cout << "\033c";
            cout << "Opção inválida";
            // system("pause");
            break;
        }
    }
    // system("CLS");
    cout << "\033c";
  return 0;
}
