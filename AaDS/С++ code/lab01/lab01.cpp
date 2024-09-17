#include <iostream>
#include <bitset>
#include <chrono>

using namespace std;

using Clock = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::time_point<Clock>;
TimePoint start_time, end_time;

const int MAX_DIGITS = 10; // Работаем с десятичными цифрами (0-9)
const int REPEAT_COUNT = 1000000; // Количество повторений для тестирования производительности

/**
 * @brief Начинает отсчет времени.
 */
void start_timer() {
    start_time = Clock::now();
}

/**************************************************************************************************
 * @brief Завершает отсчет времени и выводит длительность операции.
 * @param operation Название операции.
 * @param repetitions Количество повторений для усреднения времени.
 *************************************************************************************************/
void end_timer(const string &operation, int repetitions) {
    end_time = Clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
    cout << operation << " took " << duration / repetitions << " nanoseconds per iteration." << endl;
}

// Структура для односвязного списка
struct Set {
    char el;      ///< Элемент списка.
    Set* next;   ///< Указатель на следующий элемент.

    /**********************************************************************************************
     * @brief Конструктор узла списка.
     * @param e Значение элемента.
     * @param n Указатель на следующий элемент (по умолчанию nullptr).
     *********************************************************************************************/
    Set(char e, Set* n = nullptr) : el(e), next(n) { }

    /**********************************************************************************************
     * @brief Деструктор узла списка. Рекурсивно удаляет следующий элемент.
     *********************************************************************************************/
    ~Set() {
        delete next;
    }
};

/**************************************************************************************************
 * @brief Создает массив из ввода пользователя.
 * @param arr Массив для хранения цифр.
 * @param size Размер массива.
 *************************************************************************************************/
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

/**************************************************************************************************
 * @brief Создает массив случайных цифр.
 * @param arr Массив для хранения цифр.
 * @param size Размер массива.
 *************************************************************************************************/
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

/**************************************************************************************************
 * @brief Преобразует массив в односвязный список.
 * @param arr Массив для преобразования.
 * @param size Размер массива.
 * @return Указатель на голову списка.
 *************************************************************************************************/
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

/**************************************************************************************************
 * @brief Проверяет, содержит ли список указанный элемент.
 * @param head Указатель на голову списка.
 * @param el Элемент для проверки.
 * @return true, если элемент найден; false, если нет.
 *************************************************************************************************/
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

/**************************************************************************************************
 * @brief Преобразует массив в битсеттер.
 * @param arr Массив для преобразования.
 * @param size Размер массива.
 * @return Битсеттер, представляющий элементы массива.
 *************************************************************************************************/
typedef bitset<MAX_DIGITS> bs;
bs convertArrayToBitset(const int arr[], int size) {
    bs bset;
    for (int i = 0; i < size; i++) {
        bset.set(arr[i]);
    }
    return bset;
}

/**************************************************************************************************
 * @brief Преобразует массив в машинное слово.
 * @param arr Массив для преобразования.
 * @param size Размер массива.
 * @return Машинное слово, представляющее элементы массива.
 *************************************************************************************************/
unsigned short convertArrayToWord(const int arr[], int size) {
    unsigned short word = 0;
    for (int i = 0; i < size; i++) {
        word |= (1 << arr[i]);
    }
    return word;
}

/**************************************************************************************************
 * @brief Пересекает четыре массива.
 * @param A, B, C, D Массивы для пересечения.
 * @param sizeA, sizeB, sizeC, sizeD Размеры массивов.
 * @param result Массив для хранения результата пересечения.
 * @param resultSize Размер результата.
 *************************************************************************************************/
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

/**************************************************************************************************
 * @brief Пересекает четыре односвязных списка.
 * @param A, B, C, D Указатели на головы списков.
 * @return Указатель на голову списка с результатом пересечения.
 *************************************************************************************************/
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

/**************************************************************************************************
 * @brief Пересекает четыре битсета.
 * @param A, B, C, D Битсеты для пересечения.
 * @return Результат пересечения битсетов.
 *************************************************************************************************/
bs intersectBitsets(bs A, bs B, bs C, bs D) {
    return A & B & C & D;
}

/**************************************************************************************************
 * @brief Пересекает четыре машинных слова.
 * @param A, B, C, D Машинные слова для пересечения.
 * @return Результат пересечения машинных слов.
 *************************************************************************************************/
unsigned int intersectWord(unsigned int A, unsigned int B, 
                              unsigned int C, unsigned int D) {
    return A & B & C & D;
}

/**************************************************************************************************
 * @brief Выводит массив на экран.
 * @param arr Массив для вывода.
 * @param size Размер массива.
 *************************************************************************************************/
void outputArray(const int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

/**************************************************************************************************
 * @brief Выводит односвязный список на экран.
 * @param head Указатель на голову списка.
 *************************************************************************************************/
void outputSet(Set* head) {
    while (head != nullptr) {
        cout << head->el << " ";
        head = head->next;
    }
    cout << endl;
}

/**************************************************************************************************
 * @brief Выводит битсеттер на экран.
 * @param bset Битсеттер для вывода.
 *************************************************************************************************/
void outputBitset(bs bset) {
    for (int i = 0; i < MAX_DIGITS; i++) if (bset.test(i)) cout << i << " ";
    cout << endl;
}

/**************************************************************************************************
 * @brief Выводит машинное слово на экран.
 * @param word Машинное слово для вывода.
 *************************************************************************************************/
void outputWord(unsigned int word) {
    for (int i = 0; i < MAX_DIGITS; i++) if (word & (1 << i)) cout << i << " ";
    cout << endl;
}

int main() {
    srand(time(0));

    // Массивы для работы
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

    // Вывод массивов
    cout << "set as array A: ";
    outputArray(A, sizeA);
    cout << "set as array B: ";
    outputArray(B, sizeB);
    cout << "set as array C: ";
    outputArray(C, sizeC);
    cout << "set as array D: ";
    outputArray(D, sizeD);

    // Пересечение массивов и вывод результатов
    int resultArray[MAX_DIGITS], resultSize = 0;
    start_timer();
    for (int i = 0; i < REPEAT_COUNT; i++) {
        intersectArrays(A, sizeA, B, sizeB, C, sizeC, D, sizeD, resultArray, resultSize);
        resultSize = 0;
    }
    end_timer("Array intersection", REPEAT_COUNT);

    // Вывод результата пересечения массивов
    intersectArrays(A, sizeA, B, sizeB, C, sizeC, D, sizeD, resultArray, resultSize);
    cout << "Array intersection result: ";
    outputArray(resultArray, resultSize);

    cout << endl;

    // Пересечение односвязных списков и вывод результатов
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

    // Вывод результата пересечения списков
    Set* resultSet = intersectSets(setA, setB, setC, setD);
    cout << "List intersection result: ";
    outputSet(resultSet);
    delete resultSet; // Очистка результата

    cout << endl;

    // Пересечение битсетов и вывод результатов
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
    for (int i = 0; i < REPEAT_COUNT; i++) {
        bitset<MAX_DIGITS> resultBitset = intersectBitsets(bitsetA, bitsetB, bitsetC, bitsetD);
    }
    end_timer("BitSet intersection", REPEAT_COUNT);

    // Вывод результата пересечения битсетов
    bs resultBitset = intersectBitsets(bitsetA, bitsetB, bitsetC, bitsetD);
    cout << "BitSet intersection result: ";
    outputBitset(resultBitset);

    cout << endl;

    // Пересечение машинных слов и вывод результатов
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
    for (int i = 0; i < REPEAT_COUNT; i++) {
        unsigned int resultWord = intersectWord(wordA, wordB, wordC, wordD);
    }
    end_timer("Word intersection", REPEAT_COUNT);

    // Вывод результата пересечения машинных слов
    unsigned int resultWord = intersectWord(wordA, wordB, wordC, wordD);
    cout << "Word intersection result: ";
    outputWord(resultWord);

    cout << endl;
    cout << endl;
    
    cout << "Press Enter to exit...";
    cin.get();
    cin.get();
    
    return 0;
}
