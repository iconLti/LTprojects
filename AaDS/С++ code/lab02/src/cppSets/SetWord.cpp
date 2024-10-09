#include "../hFiles/SetArray.h"
#include "../hFiles/SetWord.h"

namespace WordSet {
    int Set::tagCounter = 0;  // Инициализация статического счётчика

    // Конструктор
    Set::Set() : elements(0), tag(++tagCounter) {
        std::cout << "Set " << tag << "W created (constructor called)." << std::endl;
    }

    // Деструктор
    Set::~Set() {
        std::cout << "Set " << tag << "W destroyed (destructor called)." << std::endl;
    }

    // Проверка наличия элемента в множестве
    bool Set::elCheck(int el) const {
        return elements & (1 << el);
    }

    // Добавление элемента в множество
    void Set::add(int el) {
        elements |= (1 << el);
        if (tag != 5) {
            std::cout << "Element " << el << " added to Set " << tag << "W." << std::endl;
        }
    }

    // Конвертация массива в WordSet
    void Set::convertArrayToWordSet(const ArraySet::Set& set) {
        const int* elements = set.getElements();
        int size = set.getSize();
        for (int i = 0; i < size; i++) {
            add(elements[i]);
        }
    }

    // Очистка множества
    void Set::clear() {
        elements = 0;  // Устанавливаем все биты в 0
    }

    // Вывод элементов множества
    void Set::outputWordSet() const {
        int cnt = 0;
        std::cout << "Set " << tag << "W elements: ";
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

    // Получение битовой маски элементов
    unsigned short Set::getElements() const { 
        return elements; 
    }
}
