#include "hFiles/SetArray.h"
#include "hFiles/SetList.h"
#include "hFiles/SetBitArray.h"
#include "hFiles/SetWord.h"
#include "hFiles/Intersection.h"

#include <iostream>
#include <chrono>

using Clock = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::time_point<Clock>;
TimePoint start_time, end_time;

const int REPEAT_COUNT = 100000; // Количество повторений для тестирования производительности

void start_timer() {
    start_time = Clock::now();
}

void end_timer(const std::string &operation, int repetitions) {
    end_time = Clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
    std::cout << operation << " took " << duration / repetitions << " nanoseconds per iteration." << std::endl;
}

int main() {
    srand(time(nullptr));

    ArraySet::Set Aa, Ab, Ac, Ad, Ae;
    ListSet::Set La, Lb, Lc, Ld, Le;
    BitSet::Set Ba, Bb, Bc, Bd, Be;
    WordSet::Set Wa, Wb, Wc, Wd, We;

    std::cout << "Choose input method (1 - manual, 2 - auto-generate): ";
    int inputChoice;
    std::cin >> inputChoice;

    if (inputChoice == 1) {
        Aa.createArrayFromInput();
        Ab.createArrayFromInput();
        Ac.createArrayFromInput();
        Ad.createArrayFromInput();
    } else {
        Aa.createArrayRandom();
        Ab.createArrayRandom();
        Ac.createArrayRandom();
        Ad.createArrayRandom();
    }

    La.convertArrayToList(Aa);
    Lb.convertArrayToList(Ab);
    Lc.convertArrayToList(Ac);
    Ld.convertArrayToList(Ad);

    Ba.convertArrayToBitSet(Aa);
    Bb.convertArrayToBitSet(Ab);
    Bc.convertArrayToBitSet(Ac);
    Bd.convertArrayToBitSet(Ad);

    Wa.convertArrayToWordSet(Aa);
    Wb.convertArrayToWordSet(Ab);
    Wc.convertArrayToWordSet(Ac);
    Wd.convertArrayToWordSet(Ad);
    


    std::cout << "Aa: ";
    Aa.outputArray();
    std::cout << "Ab: ";
    Ab.outputArray();
    std::cout << "Ac: ";
    Ac.outputArray();
    std::cout << "Ad: ";
    Ad.outputArray();

    std::cout << std::endl;

    std::cout << "La: ";
    La.outputList();
    std::cout << "Lb: ";
    Lb.outputList();
    std::cout << "Lc: ";
    Lc.outputList();
    std::cout << "Ld: ";
    Ld.outputList();

    std::cout << std::endl;

    std::cout << "Ba: ";
    Ba.outputBitSet();
    std::cout << "Bb: ";
    Bb.outputBitSet();
    std::cout << "Bc: ";
    Bc.outputBitSet();
    std::cout << "Bd: ";
    Bd.outputBitSet();

    std::cout << std::endl;

    std::cout << "Wa: ";
    Wa.outputWordSet();
    std::cout << "Wb: ";
    Wb.outputWordSet();
    std::cout << "Wc: ";
    Wc.outputWordSet();
    std::cout << "Wd: ";
    Wd.outputWordSet();

    std::cout << std::endl;
    std::cout << std::endl;

    start_timer();
    for (int i = 0; i < REPEAT_COUNT; i++) {
        ArraySet::intersection(Aa, Ab, Ac, Ad, Ae);
        Ae.clear();
    }
    end_timer("Array intersection", REPEAT_COUNT);
    ArraySet::intersection(Aa, Ab, Ac, Ad, Ae);
    
    start_timer();
    for (int i = 0; i < REPEAT_COUNT; i++) {
        ListSet::intersection(La, Lb, Lc, Ld, Le);
        Le.clear();
    }
    end_timer("List intersection", REPEAT_COUNT);
    ListSet::intersection(La, Lb, Lc, Ld, Le);

    start_timer();
    for (int i = 0; i < REPEAT_COUNT; i++) { 
        BitSet::intersection(Ba, Bb, Bc, Bd, Be);
        Be.clear();
    }
    end_timer("BitSet intersection", REPEAT_COUNT);
    BitSet::intersection(Ba, Bb, Bc, Bd, Be);
    
    start_timer();
    for (int i = 0; i < REPEAT_COUNT; i++) { 
        WordSet::intersection(Wa, Wb, Wc, Wd, We);
        We.clear();
    }
    end_timer("WordSet intersection", REPEAT_COUNT);
    WordSet::intersection(Wa, Wb, Wc, Wd, We);

    std::cout << "Array intersection: ";
    Ae.outputArray();
    std::cout << "List intersection: ";
    Le.outputList();
    std::cout << "Bit intersection: ";
    Be.outputBitSet();
    std::cout << "Word intersection: ";
    We.outputWordSet();


    return 0;
}