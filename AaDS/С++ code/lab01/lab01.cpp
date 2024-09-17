#include <iostream>
#include <bitset>
#include <chrono>

using namespace std;

using Clock = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::time_point<Clock>;
TimePoint start_time, end_time;

const int MAX_DIGITS = 10; // Работаем с десятичными цифрами (0-9)
const int REPEAT_COUNT = 1000000;

void start_timer() {
    start_time = Clock::now();
}
void end_timer(const string &operation, int repetitions) {
    end_time = Clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
    cout << operation << " took " << duration / repetitions << " nanoseconds per iteration." << endl;
}

// Структура для односвязного списка
struct Set {
  char el;
  Set* next;

  Set(char e, Set* n = nullptr) : el(e), next(n) { }
 
  ~Set() {
    delete next;
  }
};


void createArrayFromInput(int arr[], int &size) {
    char input;
    bool seen[MAX_DIGITS] = {false}; // Массив для отслеживания уже добавленных цифр
    cout << "Enter set digits (0-9), finish with 'x': ";
    while (cin >> input && input != 'x') {
        if (isdigit(input)) {
            int digit = input - '0';
            // Проверка на уникальность
            if (!seen[digit]) {
                arr[size++] = digit;
                seen[digit] = true; // Отмечаем, что цифра уже была введена
            }
        }
    }
}
void createArrayRandom(int arr[], int &size) {
    bool seen[MAX_DIGITS] = {false};
    size = 0;
    while (size < MAX_DIGITS) {
        int digit = rand() % 10;
        if (!seen[digit]) {
            arr[size++] = digit;
            seen[digit] = true;
        }
    }
}


Set* convertArrayToSet(const int arr[], int size) {
    Set* head = nullptr;
    Set* tail = nullptr;

    for (int i = 0; i < size; i++) {
        Set* newNode = new Set(arr[i] + '0');
        if (head == nullptr) {
            head = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
    }
    return head;
}
bool contains(Set* head, char el) {
    Set* current = head;
    while (current != nullptr) {
        if (current->el == el) {
            return true;
        }
        current = current->next;
    }
    return false;
}

typedef bitset<MAX_DIGITS> bs;
bs convertArrayToBitset(const int arr[], int size) {
    bs bset;
    for (int i = 0; i < size; i++) {
        bset.set(arr[i]);
    }
    return bset;
}

unsigned short convertArrayToWord(const int arr[], int size) {
    unsigned short word = 0;
    for (int i = 0; i < size; i++) {
        word |= (1 << arr[i]);
    }
    return word;
}


void intersectArrays(const int A[], int sizeA, const int B[], int sizeB,
                     const int C[], int sizeC, const int D[], int sizeD,
                     int result[], int& resultSize) {
    for (int i = 0; i < sizeA; i++) {
        int el = A[i];
        bool foundInB = false, foundInC = false, foundInD = false;

        for (int j = 0; j < sizeB; j++) if (B[j] == el) foundInB = true;
        for (int j = 0; j < sizeC; j++) if (C[j] == el) foundInC = true;
        for (int j = 0; j < sizeD; j++) if (D[j] == el) foundInD = true;

        if (foundInB && foundInC && foundInD) result[resultSize++] = el;
    }
}

Set* intersectSets(Set* A, Set* B, Set* C, Set* D) {
    Set* resultHead = nullptr;
    Set* resultTail = nullptr;

    Set* current = A;

    while (current != nullptr) {
        char el = current->el;

        if (contains(B, el) && contains(C, el) && contains(D, el)) {
            Set* newNode = new Set(el);

            if (resultHead == nullptr) {
                resultHead = newNode;
            } else {
                resultTail->next = newNode;
            }

            resultTail = newNode;
        }

        current = current->next;
    }
    return resultHead;
}

bs intersectBitsets(bs A, bs B, bs C, bs D) {
    return A & B & C & D;
}

unsigned int intersectWord(unsigned int A, unsigned int B, 
                              unsigned int C, unsigned int D) {
    return A & B & C & D;
}


void outputArray(const int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void outputSet(Set* head) {
    while (head != nullptr) {
        cout << head->el << " ";
        head = head->next;
    }
    cout << endl;
}

void outputBitset(bs bset) {
    for (int i = 0; i < MAX_DIGITS; i++) if (bset.test(i)) cout << i << " ";
    cout << endl;
}

void outputWord(unsigned int word) {
    for (int i = 0; i < MAX_DIGITS; i++) if (word & (1 << i)) cout << i << " ";
    cout << endl;
}




int main() {
    srand(time(0));

    // Множества для работы
    int A[MAX_DIGITS], B[MAX_DIGITS], C[MAX_DIGITS], D[MAX_DIGITS];
    int sizeA = 0, sizeB = 0, sizeC = 0, sizeD = 0;


    cout << "Choose input method (1 - manual, 2 - auto-generate): ";
    int inputChoice;
    cin >> inputChoice;

    if (inputChoice == 1) {
        cout << "Create set A:" << endl;
        createArrayFromInput(A, sizeA);
        cout << "Create set B:" << endl;
        createArrayFromInput(B, sizeB);
        cout << "Create set C:" << endl;
        createArrayFromInput(C, sizeC);
        cout << "Create set D:" << endl;
        createArrayFromInput(D, sizeD);
    } else {
        createArrayRandom(A, sizeA);
        createArrayRandom(B, sizeB);
        createArrayRandom(C, sizeC);
        createArrayRandom(D, sizeD);
        cout << "Generated sets: " << endl;
        cout << "A: "; outputArray(A, sizeA);
        cout << "B: "; outputArray(B, sizeB);
        cout << "C: "; outputArray(C, sizeC);
        cout << "D: "; outputArray(D, sizeD);
    }

    cout << endl;
    cout << endl;

    cout << "set as array A: ";
    outputArray(A, sizeA);
    cout << "set as array B: ";
    outputArray(B, sizeB);
    cout << "set as array C: ";
    outputArray(C, sizeC);
    cout << "set as array D: ";
    outputArray(D, sizeD);

    // Пересечение массивов и замер времени
    int resultArray[MAX_DIGITS], resultSize = 0;
    start_timer();
    for (int i  = 0; i < REPEAT_COUNT; i++) {
        intersectArrays(A, sizeA, B, sizeB, C, sizeC, D, sizeD, resultArray, resultSize);
        resultSize = 0;
    }
    end_timer("Array intersection", REPEAT_COUNT);

    cout << endl;

    // Пересечение односвязных списков и замер времени
    Set* setA = convertArrayToSet(A, sizeA);
    Set* setB = convertArrayToSet(B, sizeB);
    Set* setC = convertArrayToSet(C, sizeC);
    Set* setD = convertArrayToSet(D, sizeD);

    cout << "set as list A: ";
    outputSet(setA);
    cout << "set as list B: ";
    outputSet(setB);
    cout << "set as list C: ";
    outputSet(setC);
    cout << "set as list D: ";
    outputSet(setD);
    
    start_timer();
    for (int i = 0; i < REPEAT_COUNT; i++) {
    Set* resultSet = intersectSets(setA, setB, setC, setD);
    delete resultSet; // Очищаем память
    }
    end_timer("List intersection", REPEAT_COUNT);

    cout << endl;

    // Пересечение битсетов и замер времени
    bs bitsetA = convertArrayToBitset(A, sizeA);
    bs bitsetB = convertArrayToBitset(B, sizeB);
    bs bitsetC = convertArrayToBitset(C, sizeC);
    bs bitsetD = convertArrayToBitset(D, sizeD);

    cout << "set as arrayOfBits A: ";
    outputBitset(bitsetA);
    cout << "set as arrayOfBits B: ";
    outputBitset(bitsetB);
    cout << "set as arrayOfBits C: ";
    outputBitset(bitsetC);
    cout << "set as arrayOfBits D: ";
    outputBitset(bitsetD);

    start_timer();
    for (int i  = 0; i < REPEAT_COUNT; i++) {
        bitset<MAX_DIGITS> resultBitset = intersectBitsets(bitsetA, bitsetB, bitsetC, bitsetD);
    }
    end_timer("BitSet intersection", REPEAT_COUNT);

    cout << endl;

    // Пересечение машинных слов и замер времени
    unsigned int wordA = convertArrayToWord(A, sizeA);
    unsigned int wordB = convertArrayToWord(B, sizeB);
    unsigned int wordC = convertArrayToWord(C, sizeC);
    unsigned int wordD = convertArrayToWord(D, sizeD);

    cout << "set as word A: ";
    outputWord(wordA);
    cout << "set as word B: ";
    outputWord(wordB);
    cout << "set as word C: ";
    outputWord(wordC);
    cout << "set as word D: ";
    outputWord(wordD);

    start_timer();
    for (int i  = 0; i < REPEAT_COUNT; i++) {
        unsigned int resultWord = intersectWord(wordA, wordB, wordC, wordD);
    }
    end_timer("Word intersection", REPEAT_COUNT);

    cout << endl;
    cout << endl;
    
    return 0;
}