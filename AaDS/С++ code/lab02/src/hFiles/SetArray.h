#pragma once
#include <iostream>

namespace ArraySet {
    class Set {
    private:
        static const int MAX_ELEMENTS = 10;
        int elements[MAX_ELEMENTS]; // сам массив
        int size; // кол-во элементов в множестве

        
    public:
        // Новый статический счётчик тегов
        static int tagCounter;
        int tag; // Уникальный тег для каждого множества
        
        // Конструктор
        Set();

        // Деструктор
        ~Set();

        // Empty
        void intersectionStart();
        // void intersectionEnd();

        ////////////////////// creation //////////////////////
        bool elCheck(int el) const;
        void add(int el);
        void createArrayFromInput();
        void createArrayRandom();
        void clear();

        ////////////////////// output and get methods //////////////////////
        void outputArray() const;
        const int* getElements() const;
        int getSize() const;
    };
}