#pragma once
#include "SetArray.h"
#include <bitset>
#include <iostream>

namespace BitSet {
    class Set {
    private:
        std::bitset<10> elements;  // Битсет для хранения элементов
    public:
        // Новый статический счётчик тегов
        static int tagCounter;
        int tag; // Уникальный тег для каждого множества

        Set();
        ~Set();

        bool elCheck(int el) const;
        void add(int el);
        void convertArrayToBitSet(const ArraySet::Set& set);
        void clear();
        void outputBitSet() const;

        std::bitset<10> getElements() const;
    };
}
