#include <iostream>
#include <bitset>
using namespace std;

const int MAX_DIGITS = 10; // Работаем с десятичными цифрами (0-9)

typedef bitset<MAX_DIGITS> BitSet; // Определение типа для битсета

// Структура для односвязного списка
struct Set {
    char el;
    Set* next;

    Set(char e, Set* n = nullptr) : el(e), next(n) {}

    ~Set() {
        delete next;
    }
};

// Проверка на наличие элемента в односвязном списке
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

// Создание множества через ввод и сохранение в массиве bool
void createArrayFromInput(bool arr[]) {
    char input;
    cout << "Enter set digits (0-9), finish with 'x': ";
    while (cin >> input && input != 'x') {
        if (isdigit(input)) {
            arr[input - '0'] = true; // Устанавливаем true для введённой цифры
        }
    }
}

// Преобразование массива bool в односвязный список
Set* convertArrayToSet(const bool arr[]) {
    Set* head = nullptr;
    Set* tail = nullptr;

    for (int i = 0; i < MAX_DIGITS; ++i) {
        if (arr[i]) {
            Set* newNode = new Set(i + '0');  // Преобразуем индекс в символ цифры
            if (head == nullptr) {
                head = newNode;
            } else {
                tail->next = newNode;
            }
            tail = newNode;
        }
    }
    return head;
}

// Преобразование массива bool в битсет
BitSet convertArrayToBitset(const bool arr[]) {
    BitSet bset;
    for (int i = 0; i < MAX_DIGITS; ++i) {
        bset[i] = arr[i];
    }
    return bset;
}

// Преобразование массива bool в машинное слово
unsigned int convertArrayToWord(const bool arr[]) {
    unsigned int word = 0;
    for (int i = 0; i < MAX_DIGITS; ++i) {
        if (arr[i]) {
            word |= (1 << i);
        }
    }
    return word;
}

// Вывод односвязного списка
void outputSet(Set* head) {
    Set* current = head;
    while (current != nullptr) {
        cout << current->el << " ";
        current = current->next;
    }
    cout << endl;
}

// Пересечение односвязных списков
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

// Пересечение массивов bool
void intersectArrays(const bool A[], const bool B[], const bool C[], const bool D[], bool result[]) {
    for (int i = 0; i < MAX_DIGITS; ++i) {
        result[i] = A[i] && B[i] && C[i] && D[i];
    }
}

// Вывод массива bool
void outputArray(const bool arr[]) {
    for (int i = 0; i < MAX_DIGITS; ++i) {
        if (arr[i]) {
            cout << i << " ";
        }
    }
    cout << endl;
}

// Пересечение битсетов
BitSet intersectBitsets(BitSet A, BitSet B, BitSet C, BitSet D) {
    return A & B & C & D;
}

// Пересечение машинных слов
unsigned int intersectWords(unsigned int A, unsigned int B, unsigned int C, unsigned int D) {
    return A & B & C & D;
}

// Вывод битсета
void outputBitset(BitSet bset) {
    for (int i = 0; i < MAX_DIGITS; ++i) {
        if (bset[i]) {
            cout << i << " ";
        }
    }
    cout << endl;
}

// Вывод машинного слова
void outputWord(unsigned int word) {
    for (int i = 0; i < MAX_DIGITS; ++i) {
        if (word & (1 << i)) {
            cout << i << " ";
        }
    }
    cout << endl;
}

int main() {
    bool A[MAX_DIGITS] = {false}, B[MAX_DIGITS] = {false}, C[MAX_DIGITS] = {false}, D[MAX_DIGITS] = {false};

    // Ввод множеств
    cout << "Create set A:" << endl;
    createArrayFromInput(A);
    cout << "Create set B:" << endl;
    createArrayFromInput(B);
    cout << "Create set C:" << endl;
    createArrayFromInput(C);
    cout << "Create set D:" << endl;
    createArrayFromInput(D);

    // Преобразование в односвязные списки
    Set* setA = convertArrayToSet(A);
    Set* setB = convertArrayToSet(B);
    Set* setC = convertArrayToSet(C);
    Set* setD = convertArrayToSet(D);

    // Преобразование в битсеты
    BitSet bitsetA = convertArrayToBitset(A);
    BitSet bitsetB = convertArrayToBitset(B);
    BitSet bitsetC = convertArrayToBitset(C);
    BitSet bitsetD = convertArrayToBitset(D);

    // Преобразование в машинные слова
    unsigned int wordA = convertArrayToWord(A);
    unsigned int wordB = convertArrayToWord(B);
    unsigned int wordC = convertArrayToWord(C);
    unsigned int wordD = convertArrayToWord(D);

    // Пересечение односвязных списков
    Set* setE = intersectSets(setA, setB, setC, setD);
    cout << "\nSet E (Intersection of Lists): "; 
    if (setE != nullptr) {
        outputSet(setE);
    } else {
        cout << "Empty set.." << endl;
    }

    // Пересечение массивов bool
    bool resultArray[MAX_DIGITS] = {false};
    intersectArrays(A, B, C, D, resultArray);
    cout << "\nSet E (Intersection of Arrays): "; outputArray(resultArray);

    // Пересечение битсетов
    BitSet resultBitset = intersectBitsets(bitsetA, bitsetB, bitsetC, bitsetD);
    cout << "\nSet E (Intersection of Bitsets): "; outputBitset(resultBitset);

    // Пересечение машинных слов
    unsigned int resultWord = intersectWords(wordA, wordB, wordC, wordD);
    cout << "\nSet E (Intersection of Words): "; outputWord(resultWord);

    // Освобождение памяти, выделенной под односвязные списки
    delete setA;
    delete setB;
    delete setC;
    delete setD;
    delete setE;

    return 0;
}
