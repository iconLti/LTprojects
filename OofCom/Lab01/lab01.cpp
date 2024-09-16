#include <iostream>
#include <limits>

using namespace std;

// В начале отчета:
// 1. описание длины полей P & M float & double
// 2. принцип хранения отрицательных значений float & double


/*************************************************************************************************
 * @brief Выводит число в виде 32-битного двоичного представления
 * @param num Число типа unsigned int
 *************************************************************************************************/
void printBinary(unsigned int num) {
    // Цикл от 31 до 0 (по позициям битов)
    for (int i = (sizeof(unsigned int) * 8); i > 0; i--) {
        unsigned int musk = 1 << i; // Создаём маску для проверки конкретного бита
        cout << ((num & musk) ? '1' : '0'); // Выводим 1, если бит установлен, иначе 0
    }
    cout << endl;
}

/*************************************************************************************************
 * @brief Выводит число типа float в виде 32-битного двоичного представления
 * @param num Число типа float
 *************************************************************************************************/
void printBinary(float num) {
    // Используем union для работы с float как с unsigned int
    union {
        float f;
        unsigned int i;
    } u;
    u.f = num; // Сохраняем число float в union

    // Цикл для вывода 32 бит числа float как unsigned int
    for (int i = 31; i >= 0; i--) {
        unsigned int mask = 1 << i; // Маска для проверки конкретного бита
        cout << ((u.i & mask) ? '1' : '0'); // Выводим 1, если бит установлен, иначе 0
    }

    cout << endl;
}


int main() {
    unsigned int uIntNum;
    float floatNum;

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

    
    // Вывод в двоичной форме и десятичной форме:
    cout << "Binary representation of unsigned int: ";
    printBinary(uIntNum);
    cout << "Decimal representation of unsigned int: ";
    cout << uIntNum << endl;

    cout << "Binary representation of float: ";
    printBinary(floatNum);
    cout << "Decimal representation of float: ";
    cout << floatNum << endl;


    return 0;
}