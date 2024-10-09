#include "../hFiles/SetArray.h"
#include "../hFiles/SetList.h"
#include "../hFiles/SetWord.h"
#include "../hFiles/SetBitArray.h"
#include "../hFiles/Intersection.h"

#include <iostream>

namespace ArraySet {
    void intersection(const Set& set1, const Set& set2, const Set& set3, 
                      const Set& set4, Set& result) {
        for (int i = 0; i < set1.getSize(); i++) {
            if (set2.elCheck(set1.getElements()[i])) {
                if (set3.elCheck(set1.getElements()[i])) {
                    if (set4.elCheck(set1.getElements()[i])) {
                        result.add(set1.getElements()[i]);
                    }
                }
            }
        }
    }
}

namespace ListSet {
    void intersection(const Set& set1, const Set& set2, const Set& set3, 
                      const Set& set4, Set& result) {
        Node* current = set1.getHead();
        while (current != nullptr) {
            if (set2.contains(current->el) &&
                set3.contains(current->el) &&
                set4.contains(current->el)) {
                    result.add(current->el);
                }
            current = current->next;
        }
    }
}

namespace BitSet {
    void intersection(const Set& set1, const Set& set2, const Set& set3, 
                      const Set& set4, Set& result) {
        std::bitset<10> inter = set1.getElements() & set2.getElements() & set3.getElements() & set4.getElements();
        for (int i = 0; i < 10; i++) {
            if (inter.test(i)) {  // Проверяем, есть ли пересечение
                result.add(i);
            }
        }
    }
}

namespace WordSet {
    void intersection(const Set& set1, const Set& set2, const Set& set3, 
                      const Set& set4, Set& result) {
        unsigned int inter = set1.getElements() & set2.getElements() & set3.getElements() & set4.getElements();
        for (int i = 0; i < 10; i++) {
            if (inter & (1 << i)) {
                result.add(i);
            }
        }
    }
}
