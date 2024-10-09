#pragma once

namespace ArraySet {
    class Set;
    void intersection(const Set& set1, const Set& set2, const Set& set3, 
                      const Set& set4, Set& result);
}

namespace ListSet {
    class Set;
    void intersection(const Set& set1, const Set& set2, const Set& set3, 
                      const Set& set4, Set& result);
}

namespace BitSet {
    class Set;
    void intersection(const Set& set1, const Set& set2, const Set& set3, 
                      const Set& set4, Set& result);
}

namespace WordSet {
    class Set;
    void intersection(const Set& set1, const Set& set2, const Set& set3, 
                      const Set& set4, Set& result);
}