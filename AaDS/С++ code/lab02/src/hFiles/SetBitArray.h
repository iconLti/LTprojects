#pragma once
#include "SetArray.h"

#include <bitset>
#include <iostream>

namespace BitSet {
    class Set {
    private:
        std::bitset<10> elements;  // Используем битсет для хранения элементов
    public:
        Set() : elements(0) {}

        bool elCheck(int el) const {
            return elements.test(el);  // Проверяем наличие элемента
        }

        void add(int el) {
            elements.set(el);  // Добавляем элемент
        }

        void convertArrayToBitSet(const ArraySet::Set& set) {
            const int* elementsA = set.getElements();
            int size = set.getSize();
            for (int i = 0; i < size; i++) {
                add(elementsA[i]);
            }
        }

        void clear() {
            elements.reset();  // Сбрасываем все биты
        }

        void outputBitSet() const {
            int cnt = 0;
            for (int i = 0; i < 10; i++) {
                if (elCheck(i)) {
                    std::cout << i << " ";
                    cnt++;
                }
            }
            if (!cnt) {
                std::cout << "Set is empty.";
            }
            std::cout << std::endl;
        }

        std::bitset<10> getElements() const { return elements; }

    };
}
