#include <iostream>
#include <limits>

using namespace std;

union FloatIntUnion {
        float f;
        unsigned int i;
    };


/*************************************************************************************************
 * @brief Выводит число в виде 32-битного двоичного представления
 * @param num Число типа unsigned int
 *************************************************************************************************/
void printBinary(unsigned int num) {
    for (int i = ((sizeof(unsigned int) * 8) - 1); i >= 0; i--) {
        unsigned int mask = 1 << i;
        cout << ((num & mask) ? '1' : '0');
    }
    cout << endl;
}

/*************************************************************************************************
 * @brief Выводит число типа float в виде 32-битного двоичного представления
 * @param num Число типа float
 *************************************************************************************************/
void printBinary(float num) {
    FloatIntUnion u;
    u.f = num;

    for (int i = ((sizeof(float) * 8) - 1); i >= 0; i--) {
        unsigned int mask = 1 << i;
        cout << ((u.i & mask) ? '1' : '0');
    }
    cout << endl;
}

/*************************************************************************************************
 * @brief Выполняет зеркальную перестановку битов в группе
 * @param num Число типа unsigned int
 * @param k Количество бит в группе
 * @param l Номер младшего бита в группе
 * @return Число после перестановки
 *************************************************************************************************/
unsigned int reverseBitsInGroup(unsigned int num, int k, int l) {
    unsigned int group = (num >> l) & ((1 << k) - 1); // Извлекаем группу битов
    unsigned int reversedGroup = 0;


    // Выполняем реверс группы битов
    for (int i = 0; i < k; i++) {
        if (group & (1 << i)) {
            reversedGroup |= (1 << (k - 1 - i));
        }
    }

    // Очищаем старую группу битов в числе и вставляем новую
    num &= ~(((1 << k) - 1) << l); // Очищаем группу
    num |= (reversedGroup << l);   // Вставляем реверсированную группу

    return num;
}

int main() {
    unsigned int uIntNum;
    float floatNum;
    int k, l;

    // Ввод unsigned int числа
    cout << "Enter an unsigned int number: ";
    while (!(cin >> uIntNum)) {
        cout << "Invalid input. Please enter an unsigned int: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Ввод float числа
    cout << "Enter a float number: ";
    while (!(cin >> floatNum)) {
        cout << "Invalid input. Please enter a float number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }


    // Вывод исходных значений в двоичной форме и десятичной формах
    cout << "\nOriginal binary representation of unsigned int: ";
    printBinary(uIntNum);
    cout << "Original decimal representation of unsigned int: " << uIntNum << endl;

    cout << "Original binary representation of float: ";
    printBinary(floatNum);
    cout << "Original decimal representation of float: " << floatNum << endl;
    cout << endl;

    // Ввод параметров для зеркальной перестановки
    cout << "Enter the number of bits in the group (k): ";
    while (!(cin >> k) || k <= 0 || k > 32) {
        cout << "Invalid input. Please enter a valid number of bits (1-32): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Enter the position of the least significant bit in the group (l): ";
    while (!(cin >> l) || l < 0 || l > (32 - k)) {
        cout << "Invalid input. Please enter a valid bit position (0-" << (32 - k) << "): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }


    // Перестановка битов в unsigned int числе
    unsigned int modifiedUInt = reverseBitsInGroup(uIntNum, k, l);

    // Перестановка битов в float числе (работаем с его битовым представлением)
    FloatIntUnion u;
    u.f = floatNum;
    u.i = reverseBitsInGroup(u.i, k, l);
    float modifiedFloat = u.f;

    // Вывод модифицированных значений в двоичной форме и десятичной форме
    cout << "\nModified binary representation of unsigned int: ";
    printBinary(modifiedUInt);
    cout << "Modified decimal representation of unsigned int: " << modifiedUInt << endl;

    cout << "Modified binary representation of float: ";
    printBinary(modifiedFloat);
    cout << "Modified decimal representation of float: " << modifiedFloat << endl;

    return 0;
}
