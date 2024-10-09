#include "hFiles/SetArray.h"
#include "hFiles/SetList.h"
#include "hFiles/SetBitArray.h"
#include "hFiles/SetWord.h"
#include "hFiles/Intersection.h"

#include <iostream>
#include <chrono>

// g++ main.cpp cppSets\SetArray.cpp cppSets\Intersection.cpp cppSets\SetWord.cpp cppSets\SetList.cpp cppSets\SetBitArray.cpp  -o main.exe

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
    
    {while (true) {

        srand(time(nullptr));

        if (ArraySet::Set::tagCounter != 0) {
            std::cout << "\nNew sets:" << std::endl;
        }
        ArraySet::Set::tagCounter = 0;

        // 1. Всегда создается
        // 2. Не всегда пересекается
        // 3. Не всегда формирует другие множетсва
        ArraySet::Set Aa, Ab, Ac, Ad, Ae; 

        std::cout << "\nChoose input method (1 - manual, 2 - auto-generate): ";
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

        std::cout << "Aa: ";
        Aa.outputArray();
        std::cout << "Ab: ";
        Ab.outputArray();
        std::cout << "Ac: ";
        Ac.outputArray();
        std::cout << "Ad: ";
        Ad.outputArray();

        std::cout << std::endl;
        
        std::string interRep = "";
        do {
            std::cout << "\nChoose intersection method (1 - array, 2 - list, 3 - bit, 4 - word): ";
            inputChoice = 0;
            std::cin >> inputChoice;

            if (inputChoice == 1) {
                Aa.intersectionStart();
                Ab.intersectionStart();
                Ac.intersectionStart();
                Ad.intersectionStart();
                start_timer();
                for (int i = 0; i < REPEAT_COUNT; i++) {
                    ArraySet::intersection(Aa, Ab, Ac, Ad, Ae);
                    Ae.clear();
                }
                end_timer("Array intersection", REPEAT_COUNT);
                ArraySet::intersection(Aa, Ab, Ac, Ad, Ae);

                std::cout << "Array intersection: ";
                Ae.outputArray();

            } else if (inputChoice == 2) {
                ListSet::Set La, Lb, Lc, Ld, Le;

                La.convertArrayToList(Aa);
                Lb.convertArrayToList(Ab);
                Lc.convertArrayToList(Ac);
                Ld.convertArrayToList(Ad);

                std::cout << "La: ";
                La.outputList();
                std::cout << "Lb: ";
                Lb.outputList();
                std::cout << "Lc: ";
                Lc.outputList();
                std::cout << "Ld: ";
                Ld.outputList();

                std::cout << std::endl;
                start_timer();
                for (int i = 0; i < REPEAT_COUNT; i++) {
                    ListSet::intersection(La, Lb, Lc, Ld, Le);
                    Le.clear();
                }
                end_timer("List intersection", REPEAT_COUNT);
                ListSet::intersection(La, Lb, Lc, Ld, Le);

                std::cout << "List intersection: ";
                Le.outputList();

            } else if (inputChoice == 3) {
                BitSet::Set Ba, Bb, Bc, Bd, Be;

                Ba.convertArrayToBitSet(Aa);
                Bb.convertArrayToBitSet(Ab);
                Bc.convertArrayToBitSet(Ac);
                Bd.convertArrayToBitSet(Ad);

                std::cout << "Ba: ";
                Ba.outputBitSet();
                std::cout << "Bb: ";
                Bb.outputBitSet();
                std::cout << "Bc: ";
                Bc.outputBitSet();
                std::cout << "Bd: ";
                Bd.outputBitSet();

                std::cout << std::endl;

                start_timer();
                for (int i = 0; i < REPEAT_COUNT; i++) { 
                    BitSet::intersection(Ba, Bb, Bc, Bd, Be);
                    Be.clear();
                }
                end_timer("BitSet intersection", REPEAT_COUNT);
                BitSet::intersection(Ba, Bb, Bc, Bd, Be);

                std::cout << "Bit intersection: ";
                Be.outputBitSet();

            } else if (inputChoice == 4) {
                WordSet::Set Wa, Wb, Wc, Wd, We;
        
                Wa.convertArrayToWordSet(Aa);
                Wb.convertArrayToWordSet(Ab);
                Wc.convertArrayToWordSet(Ac);
                Wd.convertArrayToWordSet(Ad);
                
                std::cout << "Wa: ";
                Wa.outputWordSet();
                std::cout << "Wb: ";
                Wb.outputWordSet();
                std::cout << "Wc: ";
                Wc.outputWordSet();
                std::cout << "Wd: ";
                Wd.outputWordSet();

                
                start_timer();
                for (int i = 0; i < REPEAT_COUNT; i++) { 
                    WordSet::intersection(Wa, Wb, Wc, Wd, We);
                    We.clear();
                }
                end_timer("WordSet intersection", REPEAT_COUNT);
                WordSet::intersection(Wa, Wb, Wc, Wd, We);
                
                std::cout << "Word intersection: ";
                We.outputWordSet();

            } else { std::cout << "invalid number || try again\n" << std::endl; }
            std::cout << "Enter 'stop' to end the intersection (any button to continue) >> ";
            std::cin >> interRep;
        } while (interRep != "stop");
        
     
        
        // end of programm logic
        std::cout << "\n\n";
        std::string input = "";
        std::cout << "Enter '!end' to finish the program >> ";
        std::cin >> input;
        if (input == "!end") {
            std::cout << "See you next time :^" << std::endl;
            std::cout << "All sets are about to be destroyed." << std::endl;
            break;
        }
        system("cls");
        std::cout << "Old sets:" << std::endl;
        
        
    }}

    
    system("pause");
    return 0;
}