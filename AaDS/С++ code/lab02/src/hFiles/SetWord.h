#pragma once
#include "SetArray.h"


namespace WordSet {
    class Set {
    private:
        unsigned short elements;
    public:
        // Новый статический счётчик тегов
        static int tagCounter;
        int tag; // Уникальный тег для каждого множества

        Set();
        ~Set();
        bool elCheck(int el) const;
        void add(int el);
        void convertArrayToWordSet(const ArraySet::Set& set);
        void clear();
        void outputWordSet() const;
        unsigned short getElements() const;

    };
}