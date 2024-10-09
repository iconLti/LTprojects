#pragma once
#include "SetArray.h"
#include <iostream>

namespace ListSet {

    struct Node {
        char el;
        Node* next;

        Node(char e, Node* n = nullptr);

        void* operator new(size_t size);
        void operator delete(void* ptr);
    };

    class Set {
    private:
        Node* head; // хранит адрес первого элемента для каждого объекта
        Node* tail;
    public:
        // Новый статический счётчик тегов
        static int tagCounter;
        int tag; // Уникальный тег для каждого множества
        
        Set();
        ~Set();

        bool contains(char el) const;
        void add(char el);
        void convertArrayToList(const ArraySet::Set& set);
        void clear();
        void outputList() const;

        Node* getHead() const;
    };
}
