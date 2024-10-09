#include "../hFiles/SetList.h"
#include <iostream>
#include <cstdlib>  // Для std::malloc и std::free

namespace ListSet {
    int Set::tagCounter = 0;  // Инициализация статического счётчика

    // Конструктор узла
    Node::Node(char e, Node* n) : el(e), next(n) {}

    // Перегрузка оператора new
    void* Node::operator new(size_t size) {
        std::cout << "";
        std::cout << "";
        std::cout << "";
        return ::operator new(size);  // Вызов стандартного оператора new
    }

    // Перегрузка оператора delete
    void Node::operator delete(void* ptr) {
        std::cout << "";
        std::cout << "";
        std::cout << "";
        ::operator delete(ptr);  // Вызов стандартного оператора delete
    }

    // Конструктор множества
    Set::Set() : head(nullptr), tail(nullptr), tag(++tagCounter) {
        std::cout << "Set " << tag << "L created (constructor called)." << std::endl;
    }

    // Деструктор множества
    Set::~Set() {
        clear();  // Очистка списка при уничтожении
        std::cout << "Set " << tag << "L destroyed (destructor called)." << std::endl;
    }

    // Проверка наличия элемента в множестве
    bool Set::contains(char el) const {
        Node* current = head;
        while (current != nullptr) {
            if (current->el == el) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Добавление элемента в множество
    void Set::add(char el) {
        Node* newNode = new Node(el);  // Создание нового узла
        if (head == nullptr) {
            head = newNode;  // Если список пустой, голова указывает на новый узел
        } else {
            tail->next = newNode;  // Если не пустой, хвост указывает на новый узел
        }
        tail = newNode;  // Обновляем указатель хвоста
        if (tag != 5) {
            std::cout << "Element " << el << " added to Set " << tag << "L." << std::endl;
        }
    }

    // Конвертация массива в список
    void Set::convertArrayToList(const ArraySet::Set& set) {
        const int* elements = set.getElements();
        int size = set.getSize();
        for (int i = 0; i < size; i++) {
            add(elements[i] + '0');  // Конвертируем int в символ
        }
    }

    // Очистка множества
    void Set::clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;  // Удаляем каждый узел
        }
        head = nullptr;  // Сбрасываем голову и хвост
        tail = nullptr;
    }

    // Вывод множества
    void Set::outputList() const {
        Node* current = head;
        if (current == nullptr) {
            std::cout << "Set " << tag << "L is empty." << std::endl;
            return;
        }
        std::cout << "Set " << tag << "L elements: ";
        while (current != nullptr) {
            std::cout << current->el << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    // Возвращает указатель на голову списка
    Node* Set::getHead() const { return head; }
}
