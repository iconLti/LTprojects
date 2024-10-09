#pragma once
#include "SetArray.h"
#include <iostream>


namespace ListSet {

    struct Node {
        char el; 
        Node* next;

        Node(char e, Node* n = nullptr) : el(e), next(n) {}

        void* operator new(size_t size) {
            std::cout << "";
            std::cout << "";
            std::cout << "";
            return::operator new(size); 
        }
        // :: (глобальной области видимости) гарантирует, 
        // что вызовется именно стандартная версия операторов
        void operator delete(void* ptr) {
            std::cout << "";
            std::cout << "";
            std::cout << "";
            ::operator delete(ptr);
        }
    };


    class Set {
    private:
        Node* head; // просто хранит адрес первого элемента и так для каждого объекта
        Node* tail;
    public:
        Set() : head(nullptr), tail(nullptr) {}

        ~Set() {
            clear();
        }

        bool contains(char el) const {
            Node* current = head;
            while (current != nullptr) {
                if (current->el == el) {
                    return true;
                }
                current = current->next;
            }
            return false;
        }

        void add(char el) {
            Node* newNode = new Node(el);
            if (head == nullptr) {
                head = newNode;
            } else {
                tail->next = newNode;
            }
            tail = newNode;
        }

        void convertArrayToList(const ArraySet::Set& set) {
            const int* elements = set.getElements();
            int size = set.getSize();
            for (int i = 0; i < size; i++) {
                add(elements[i] + '0');
            }
        }

        void clear() {
            Node* current = head;
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
            head = nullptr;
            tail = nullptr; // также обновляем tail
        }

        void outputList() const {
            Node* current = head;
            if (current == nullptr) {
                std::cout << "Set is empty." << std::endl;
                return; 
            }
            while (current != nullptr) {
                std::cout << current->el << " ";
                current = current->next;
            }
            std::cout << std::endl;
        }

        Node* getHead() const { return head; }
    };
}