#include "include\Tree.h"
#include <ctime>
#include <cstring>

Tree::Tree(char nm, char mnm, int mxr)
    : num(nm), maxnum(mnm), maxrow(mxr), offset(40), root(nullptr), SCREEN(new char*[maxrow]) {
    for (int i = 0; i < maxrow; i++)
        SCREEN[i] = new char[80];
} 

Tree::~Tree() {
    for (int i = 0; i < maxrow; i++)
        delete[] SCREEN[i];
    delete[] SCREEN;
    delete root;
}

void Tree::clrscr() {
    for (int i = 0; i < maxrow; i++)
        memset(SCREEN[i], '_', 80); // заполнение массива символами
}

Node* Tree::MakeNode(int depth, bool isRandom) {
    Node *v = nullptr;
    int Y;

    if (isRandom) {
        Y = (depth < rand() % 6 + 1) && (num <= 'z');
    } else {
        std::cout << "Node (" << num << ',' << depth << ")1/0: ";
        std::cin >> Y;
    }

    if (Y) {
        v = new Node;
        v->lft = MakeNode(depth + 1, isRandom);
        v->rgt = MakeNode(depth + 1, isRandom);
        v->d = num++;
    }
    return v;
}

void Tree::OutTree() {
    clrscr();
    OutNodes(root, 1, offset);
    for (int i = 0; i < maxrow; i++) {
        SCREEN[i][79] = 0;
        std::cout << '\n' << SCREEN[i];
    }
    std::cout << '\n';
}

void Tree::OutNodes(Node *v, int r, int c) {
    if (r && c && (c < 80)){
        SCREEN[r - 1][c - 1] = v->d;
    }
    if (r < maxrow) {
        if (v->lft) OutNodes(v->lft, r + 1, c - (offset >> r));
        if (v->rgt) OutNodes(v->rgt, r + 1, c + (offset >> r));
    }
}

void Tree::InOrderTraversel(Node *v) {
    if (v) {
        InOrderTraversel(v->lft);
        std::cout << v->d << ' ';
        InOrderTraversel(v->rgt);
    }
}

int Tree::countTwoChildren(Node *v) {
    if (!v) return 0;
    int count = 0;
    if ((!v->lft && !v->rgt) || (v->lft && !v->rgt) || (!v->lft && v->rgt)) {
        count = 1;
    }
    return countTwoChildren(v->lft) + count + countTwoChildren(v->rgt);
}

int Tree::CountNodesWithLessThenTwoChildren() {
    return countTwoChildren(root);
}

void Tree::OutIOT() {
    InOrderTraversel(root);
}

void Tree::MakeTree(bool isRandom) {
    root = MakeNode(0, isRandom);
}

bool Tree::exist() {
    return root != nullptr;
}
