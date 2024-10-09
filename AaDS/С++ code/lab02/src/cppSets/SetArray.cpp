#include "../hFiles/SetArray.h"

namespace ArraySet {
    int Set::tagCounter = 0; // Инициализация статического счётчика

    // Конструктор
    Set::Set() : size(0), tag(++tagCounter) {
        std::cout << "Set " << tag << "A created (constructor called)." << std::endl;
    }

    // Деструктор
    Set::~Set() {
        std::cout << "Set " << tag << "A destroyed (destructor called)." << std::endl;
    }

    // Empty
    void Set::intersectionStart() {
        std::cout << "Entersection of " << tag << "A is about to start" << std::endl;
    }
    // void Set::intersectionEnd() {
    //     std::cout << "Entersection of" << tag << "A is about to end"<< std::endl;
    // }

    ////////////////////// creation //////////////////////
    bool Set::elCheck(int el) const {
        for (int i = 0; i < size; i++) {
            if (elements[i] == el) {
                return true;
            }
        }
        return false;
    }

    void Set::add(int el) {
        if (size < MAX_ELEMENTS) {
            if (!elCheck(el)) {
                elements[size++] = el;
                if (tag != 5) {
                    std::cout << "Element " << el << " added to Set " << tag << "A." << std::endl;
                }
            }
        }
    }

    void Set::createArrayFromInput() {
        char input;
        std::cout << "Enter set elements (0-9), finish input with 'x': ";
        while (std::cin >> input && input != 'x') {
            if (isdigit(input)) {
                int digit = input - '0';
                if (size < MAX_ELEMENTS) {
                    add(digit);
                } else {
                    std::cout << "Maximum set size reached!" << std::endl;
                    break;
                }
            } else {
                std::cout << "Invalid input! Enter a number between 0 and 9." << std::endl;
            }
        }
    }

    void Set::createArrayRandom() {
        int iterationSize = rand() % 10;
        while (size < iterationSize) {
            int digit = rand() % 10;
            add(digit);
        }
    }

    void Set::clear() {
        for (int i = 0; i < size; i++) {
            elements[i] = 0;
        }
        size = 0;   
    }

    ////////////////////// output and get methods //////////////////////
    void Set::outputArray() const {
        if (size == 0) {
            std::cout << "Set " << tag << "A is empty." << std::endl;
            return;
        }
        std::cout << "Set " << tag << "A elements: ";
        for (int i = 0; i < size; i++) {
            std::cout << elements[i] << " ";
        }
        std::cout << std::endl;
    }

    const int* Set::getElements() const { return elements; }
    int Set::getSize() const { return size; }
}
