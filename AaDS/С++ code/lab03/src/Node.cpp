#include "include/Node.h"

// Конструктор по умолчанию инициализирует указатели как nullptr
Node::Node() : lft(nullptr), rgt(nullptr) {}

// Деструктор удаляет потомков
Node::~Node() {
    if (lft) delete lft;
    if (rgt) delete rgt;
}
