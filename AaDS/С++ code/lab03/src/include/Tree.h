#ifndef TREE_H
#define TREE_H

#include "Node.h" // Включаем Node, так как Tree использует его
#include <iostream>

class Tree {
    Node *root;  // указатель на корень дерева
    char num, maxnum; // счетчики тегов
    int maxrow, offset; // максимальная глубина, смещение корня
    char **SCREEN; // память для отображения дерева

    void clrscr(); // очистка рабочей памяти
    Node* MakeNode(int depth, bool isRandom); // создание поддерева
    void OutNodes(Node *v, int r, int c); // отображение поддерева
    int countTwoChildren(Node *v); // подсчет вершин с <= 2 потомками
    void InOrderTraversel(Node *v); // явный внутренний обход

public:
    Tree() = delete;
    Tree(char num, char maxnum, int maxrow); // конструктор
    ~Tree(); // деструктор
    Tree(const Tree&) = delete; // запрещённый конструктор копирования
    Tree& operator=(const Tree&) = delete; // запрещённый оператор присваивания

    void MakeTree(bool isRandom); // создание дерева
    bool exist(); // проверка дерева
    void OutTree(); // отображение дерева
    int CountNodesWithLessThenTwoChildren(); // подсчет вершин с < 2 потомками
    void OutIOT(); // вывод дерева in-order
};

#endif // TREE_H
