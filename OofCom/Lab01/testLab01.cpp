#include <iostream>
#include <bitset>
#include <limits>

using namespace std;


/**************************************************************************************************
 * @brief Отображает число типа unsigned int в двоичной форме.
 * 
 * Функция использует объект std::bitset для вывода 32-битного представления числа.
 * 
 * @param num Число типа unsigned int для отображения.
 ************************************************************************************************/
void printBinary(unsigned int num) {
    bitset<32> bits(num);
    cout << "Binary representation of unsigned int: " << bits << endl;
}


/**************************************************************************************************
 * @brief Отображает число типа float в двоичной форме.
 * 
 * Для преобразования числа float в его двоичное представление используется union,
 * позволяющий работать с числом как с типом unsigned int.
 * 
 * @param num Число типа float для отображения.
*************************************************************************************************/
void printBinary(float num) {
    union {
        float f;
        unsigned int i;
    } u;
    u.f = num;
    bitset<32> bits(u.i);
    cout << "Binary representation of float: " << bits << endl;
}


/**************************************************************************************************
 * @brief Зеркально переставляет группу рядом стоящих разрядов числа.
 * 
 * Функция принимает число, начальную позицию и количество битов, которые необходимо перевернуть.
 * Она извлекает биты, зеркально их переставляет, и вставляет обратно в исходное число.
 * 
 * @param num Число типа unsigned int, в котором нужно переставить биты.
 * @param start Позиция (начиная с 0) младшего бита группы, которую нужно переставить.
 * @param count Количество битов, которые необходимо перевернуть.
 * 
 * @return unsigned int Новое число с зеркально переставленной группой битов.
*************************************************************************************************/
unsigned int reverseBits(unsigned int num, int start, int count) {
    // Создаем маску для выделения нужной группы битов
    unsigned int mask = ((1 << count) - 1) << start;
    
    // Извлекаем биты из числа, используя маску
    unsigned int group = (num & mask) >> start;
    
    // Переменная для хранения перевернутой группы битов
    unsigned int reversedGroup = 0;

    // Зеркально переставляем биты в группе
    for (int i = 0; i < count; ++i) {
        // Извлекаем бит на позиции i и вставляем его на соответствующую зеркальную позицию
        reversedGroup |= ((group >> i) & 1) << (count - i - 1);
    }

    // Очищаем старую группу битов в исходном числе
    num &= ~mask;
    
    // Вставляем перевернутую группу битов обратно в исходное число
    num |= (reversedGroup << start);
    
    // Возвращаем результат с переставленными битами
    return num;
}


/**************************************************************************************************
 * @brief Основная функция программы.
 * 
 * Программа запрашивает у пользователя ввод числа типа unsigned int и float, 
 * отображает их в двоичном виде,
 * затем запрашивает начальную позицию и количество битов для зеркальной перестановки и выводит
 * результат в двоичном формате.
 * 
 * @return int Возвращает 0 в случае успешного выполнения программы.
*************************************************************************************************/
int main() {
    unsigned int uIntNum;
    float floatNum;
    
    // Ввод данных для unsigned int с проверкой корректности
    cout << "Enter an unsigned int number: ";
    while (!(cin >> uIntNum)) {
        cout << "Invalid input. Please enter an unsigned int: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Ввод данных для float с проверкой корректности
    cout << "Enter a float number: ";
    while (!(cin >> floatNum)) {
        cout << "Invalid input. Please enter a float number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Вывод чисел в двоичной форме
    printBinary(uIntNum);
    printBinary(floatNum);
    
    // Ввод параметров для зеркальной перестановки разрядов с проверкой на корректность
    int start, count;
    do {
        cout << "Enter the starting bit position (0-31) for unsigned int: ";
        cin >> start;
        cout << "Enter the number of bits to reverse: ";
        cin >> count;
    } while (start < 0 || start > 31 || count <= 0 || (start + count) > 32);

    // Зеркальная перестановка битов и вывод результата
    unsigned int reversedUInt = reverseBits(uIntNum, start, count);
    cout << "Original unsigned int: " << bitset<32>(uIntNum) << endl;
    cout << "Reversed unsigned int: " << bitset<32>(reversedUInt) << endl;

    return 0;
}
