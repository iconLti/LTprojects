#pragma once
#include "SetArray.h"


namespace WordSet {
    class Set {
    private:
        unsigned short elements;
    public:
        Set() : elements(0) {}

        bool elCheck(int el) const {
            return elements & (1 << el);
        }

        void add(int el) {
            elements |= (1 << el);
        }

        void convertArrayToWordSet(const ArraySet::Set& set) {
            const int* elements = set.getElements();
            int size = set.getSize();
            for (int i = 0; i < size; i++) {
                add(elements[i]);
            }
        }

        void clear() {
            elements = 0;  // Устанавливаем все биты в 0
        }

        void outputWordSet() const {
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

        unsigned short getElements() const { return elements; }

    };
}