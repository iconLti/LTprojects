#include "../hFiles/SetBitArray.h"

namespace BitSet {
    int Set::tagCounter = 0;  // Инициализация статического счётчика

    Set::Set() : elements(0), tag(++tagCounter) {
        std::cout << "Set " << tag << "B created (constructor called)." << std::endl;
    }

    Set::~Set() {
        clear();
        std::cout << "Set " << tag << "B destroyed (destructor called)." << std::endl;
    }

    bool Set::elCheck(int el) const {
        return elements.test(el);
    }

    void Set::add(int el) {
        elements.set(el);
        if (tag != 5) {
            std::cout << "Element " << el << " added to Set " << tag << "B." << std::endl;
        } 
    }

    void Set::convertArrayToBitSet(const ArraySet::Set& set) {
        const int* elementsA = set.getElements();
        int size = set.getSize();
        for (int i = 0; i < size; i++) {
            add(elementsA[i]);
        }
    }

    void Set::clear() {
        elements.reset();
    }

    void Set::outputBitSet() const {
        int cnt = 0;
        std::cout << "Set " << tag << "B elements: ";
        for (int i = 0; i < 10; i++) {
            if (elCheck(i)) {
                std::cout << i << " ";
                cnt++;
            }
        }
        if (!cnt) {
            std::cout << "Set " << tag << "B is empty.";
        }
        std::cout << std::endl;
    }

    std::bitset<10> Set::getElements() const { return elements; }
}
