#include "include/Tree.h"
#include <cstdlib>
#include <ctime>

int main() {
    // Проверка конструкторов по умолчанию должна вызывать ошибку --> по сути они не нужны;
    // Tree t1; // Ошибка: конструктор по умолчанию запрещен;

    // Проверка конструктора копирования — должна вызвать ошибку
    Tree t2('a', 'z', 8); // Корректное создание дерева
    // Tree t3 = t2; // Ошибка: конструктор копирования запрещён

    // Проверка оператора присваивания — должна вызвать ошибку
    Tree t4('b', 'y', 7); // Корректное создание другого дерева
    // t4 = t2; // Ошибка: оператор присваивания запрещён
    
    
    Tree Tr('a', 'z', 8); // основное дерево для главного задания
    // srand(27); // для тестов, чтобы увидеть разницу
    srand(time(nullptr));

    int choice;
    std::cout << "Choose the method to create the tree:\n";
    std::cout << "1. Random creation\n";
    std::cout << "2. Input from keyboard\n";
    std::cout << "Your choice: ";
    std::cin >> choice;

    if (choice == 1) {
        Tr.MakeTree(true);
    } else if (choice == 2) {
        Tr.MakeTree(false);
    } else {
        std::cout << "Invalid choice!" << std::endl;
        return 1;
    }

    if (Tr.exist()) {
        Tr.OutTree();
        std::cout << std::endl;
        std::cout << "InOrderTraversa: ";
        Tr.OutIOT();
        std::cout << std::endl;
        int count = Tr.CountNodesWithLessThenTwoChildren();
        std::cout << "\nNumber of nodes with no more than two children: " << count << std::endl;
    } else {
        std::cout << "The tree is empty!" << std::endl;
    }

    std::cout << "\n=== End ===" << std::endl;

    system("pause");
    return 0;
}
