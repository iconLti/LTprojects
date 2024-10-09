#pragma once
#include <iostream>

namespace ArraySet {
    class Set {
    private:
        static const int MAX_ELEMENTS = 10;
        int elements[MAX_ELEMENTS]; // сам массив
        int size; // кол-во элементов в множестве 
    public:
        Set() : size(0) {};


        ////////////////////// creation //////////////////////
        bool elCheck(int el) const {
            for (int i = 0; i < size; i++) {
                if (elements[i] == el) {
                    return true;
                }
            }
            return false;
        }

        void add(int el) {
            if (size < MAX_ELEMENTS) {
                if (!elCheck(el)) { 
                    elements[size++] = el; 
                }
            }
        }

        void createArrayFromInput() {
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

        void createArrayRandom() {
            char input;
            int iterationSize = rand() % 10;
            while (size < iterationSize) {
                int digit = rand() % 10;
                add(digit);
            }
        }

        void clear() {
            for (int i = 0; i < size; i++) {
                elements[i] = 0;
            }
            size = 0;
        }


        ////////////////////// output and get methods //////////////////////
        void outputArray() const {
            if (size == 0) {
                std::cout << "Set is empty." << std::endl;
                return;
            }
            for (int i = 0; i < size; i++) {
                std::cout << elements[i] << " ";
            }
            std::cout << std::endl;
        }
        // const после имени метода
        // означает, что метод не изменяет состояние объекта, для которого он вызывается
        const int* getElements() const { return elements; }
        int getSize() const { return size; }
 
    };
    
}