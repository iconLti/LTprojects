#include <iostream>
#include <bitset>
using namespace std;

// Константы для работы с десятичными цифрами
const int MAX_DIGITS = 10;

// Структура для односвязного списка
struct Set {
    char el;        // Character (digit)
    Set* next;      // Pointer to the next element

    Set(char e, Set* n = nullptr) : el(e), next(n) { }

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

// Функция создания множества через массив
void createArrayFromInput(bool arr[]) {
    char input;
    cout << "Enter set digits (0-9), finish with 'x': ";
    while (cin >> input && input != 'x') {
        if (isdigit(input)) {
            arr[input - '0'] = true;  // Преобразование символа в индекс
        }
    }
}

// Преобразование массива в односвязный список
Set* convertArrayToSet(bool arr[]) {
    Set* head = nullptr;
    Set* tail = nullptr;

    for (int i = 0; i < MAX_DIGITS; ++i) {
        if (arr[i]) {
            Set* newNode = new Set(i + '0');  // Преобразуем индекс обратно в символ
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

// Вывод односвязного списка
void outputSet(Set* head) {
    Set* current = head;
    while (current != nullptr) {
        cout << current->el << " ";
        current = current->next;
    }
    cout << endl;
}

// Интерсекция множеств для односвязного списка
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

// Пересечение массивов
void intersectArrays(bool A[], bool B[], bool C[], bool D[], bool result[]) {
    for (int i = 0; i < MAX_DIGITS; ++i) {
        result[i] = A[i] && B[i] && C[i] && D[i];
    }
}

// Вывод массива
void outputArray(bool arr[]) {
    for (int i = 0; i < MAX_DIGITS; ++i) {
        if (arr[i]) {
            cout << i << " ";
        }
    }
    cout << endl;
}

// Пересечение для битовых массивов
void intersectBitsets(bool A[], bool B[], bool C[], bool D[], bool result[]) {
    for (int i = 0; i < MAX_DIGITS; ++i) {
        result[i] = A[i] && B[i] && C[i] && D[i];
    }
}

// Интерсекция для машинного слова
unsigned int intersectWord(unsigned int A, unsigned int B, unsigned int C, unsigned int D) {
    return A & B & C & D;
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
    // Массивы для работы с множествами
    bool A[MAX_DIGITS] = {false}, B[MAX_DIGITS] = {false}, C[MAX_DIGITS] = {false}, D[MAX_DIGITS] = {false};

    // Создание множеств через ввод
    cout << "Create set A:" << endl;
    createArrayFromInput(A);

    cout << "Create set B:" << endl;
    createArrayFromInput(B);

    cout << "Create set C:" << endl;
    createArrayFromInput(C);

    cout << "Create set D:" << endl;
    createArrayFromInput(D);

    // Преобразование массивов в односвязные списки
    Set* setA = convertArrayToSet(A);
    Set* setB = convertArrayToSet(B);
    Set* setC = convertArrayToSet(C);
    Set* setD = convertArrayToSet(D);

    // Вывод списков
    cout << "\nSet A (List): "; outputSet(setA);
    cout << "Set B (List): "; outputSet(setB);
    cout << "Set C (List): "; outputSet(setC);
    cout << "Set D (List): "; outputSet(setD);

    // Пересечение списков
    Set* setE = intersectSets(setA, setB, setC, setD);
    cout << "\nSet E (Intersection of Lists): "; 
    if (setE != nullptr) {
        outputSet(setE);
    } else {
        cout << "Empty set.." << endl;
    }

    // Пересечение массивов
    bool resultArray[MAX_DIGITS] = {false};
    intersectArrays(A, B, C, D, resultArray);
    cout << "\nSet E (Intersection of Arrays): "; outputArray(resultArray);

    // Пересечение для битовых массивов
    bool resultBits[MAX_DIGITS] = {false};
    intersectBitsets(A, B, C, D, resultBits);
    cout << "\nSet E (Intersection of Bitsets): "; outputArray(resultBits);

    // Работа с машинным словом
    unsigned int wordA = 0, wordB = 0, wordC = 0, wordD = 0;

    // Преобразование массивов в машинные слова
    for (int i = 0; i < MAX_DIGITS; ++i) {
        if (A[i]) wordA |= (1 << i);
        if (B[i]) wordB |= (1 << i);
        if (C[i]) wordC |= (1 << i);
        if (D[i]) wordD |= (1 << i);
    }

    // Пересечение машинных слов
    unsigned int wordE = intersectWord(wordA, wordB, wordC, wordD);
    cout << "\nSet E (Intersection of Words): "; outputWord(wordE);

    // Очистка памяти
    delete setA;
    delete setB;
    delete setC;
    delete setD;
    delete setE;

    return 0;
}
