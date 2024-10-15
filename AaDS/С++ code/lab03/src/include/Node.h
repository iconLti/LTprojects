#ifndef NODE_H
#define NODE_H

// Класс «узел дерева»
class Node {
    char d;        // тег узла
    Node *lft;     // левый потомок
    Node *rgt;     // правый потомок
public:
    Node(); // конструктор
    ~Node(); // деструктор

    friend class Tree; // Класс Tree может иметь доступ к приватным полям Node
};

#endif // NODE_H
